<?php

use Evenement\EventEmitter;
use React\EventLoop\LoopInterface;

/**
 * @mixin ZSocket
 */
class SocketWrapper extends EventEmitter
{
    /**
     * @var resource
     */
    public $fileDescriptor;

    /**
     * @var bool
     */
    public $closed = false;

    /**
     * @var ZSocket
     */
    protected $socket;

    /**
     * @var LoopInterface
     */
    protected $loop;

    /**
     * @var Buffer
     */
    protected $buffer;

    /**
     * @param ZSocket     $socket
     * @param LoopInterface $loop
     */
    public function __construct(ZSocket $socket, LoopInterface $loop)
    {
        $this->socket = $socket;
        $this->loop = $loop;

        $this->fileDescriptor = $this->socket->get_fd();

        $this->socket->set_rcvtimeo(0);

        $writeListener = array($this, 'handleEvent');

        $this->buffer = new Buffer($socket, $this->fileDescriptor, $this->loop, $writeListener);

        if($this->isReadableSocketType($socket->get_socket_type())) {
            $this->attachReadListener();
        }
    }

    public function attachReadListener()
    {
        $this->loop->addReadStream($this->fileDescriptor, array($this, 'handleEvent'));
    }

    public function handleEvent()
    {
        while (true) {
            $events = $this->socket->get_events();

            $isPollIn = $events & ZSys::POLL_IN;
            $isPollOut = $events & ZSys::POLL_OUT;

            $hasEvents = $isPollIn || ($isPollOut && $this->buffer->listening);

            if (!$hasEvents) {
                break;
            }

            if ($isPollIn) {
                $this->handleReadEvent();
            }

            if ($isPollOut && $this->buffer->listening) {
                $this->buffer->handleWriteEvent();
            }
        }
    }

    public function handleReadEvent()
    {
        $messages = $this->socket->recv();

        if ($messages !== false) {
            if (count($messages) === 1) {
                $this->emit('message', array($messages));
            }

            $this->emit('messages', array($messages));
        }
    }

    /**
     * @return ZSocket
     */
    public function getWrappedSocket()
    {
        return $this->socket;
    }

    /**
     * @param string $channel
     */
    public function subscribe($channel)
    {
        $this->socket->set_subscribe($channel);
    }

    /**
     * @param string $channel
     */
    public function unsubscribe($channel)
    {
        $this->socket->set_unsubscribe($channel);
    }

    /**
     * @param string $message
     */
    public function send($message)
    {
        $this->buffer->send($message);
    }

    public function close()
    {
        if ($this->closed) {
            return;
        }

        $this->emit('end', array($this));
        $this->loop->removeStream($this->fileDescriptor);
        $this->buffer->removeAllListeners();
        $this->removeAllListeners();
        unset($this->socket);
        $this->closed = true;
    }

    public function end()
    {
        if ($this->closed) {
            return;
        }

        $that = $this;

        $this->buffer->on('end', function () use ($that) {
            $that->close();
        });

        $this->buffer->end();
    }

    /**
     * @param string $method
     * @param array  $parameters
     *
     * @return mixed
     */
    public function __call($method, array $parameters)
    {
        return call_user_func_array(array($this->socket, $method), $parameters);
    }

    /**
     * @param int $type
     *
     * @return bool
     */
    protected function isReadableSocketType($type)
    {
        $readableTypes = array(
            ZSys::SOCKET_PULL,
            ZSys::SOCKET_SUB,
            ZSys::SOCKET_REQ,
            ZSys::SOCKET_REP,
            ZSys::SOCKET_ROUTER,
            ZSys::SOCKET_DEALER,
        );
        return in_array($type, $readableTypes);
    }
}