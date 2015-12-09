<?php

use Evenement\EventEmitter;
use React\EventLoop\LoopInterface;

class Buffer extends EventEmitter
{
    /**
     * @var ZSocket
     */
    public $socket;

    /**
     * @var bool
     */
    public $closed = false;

    /**
     * @var bool
     */
    public $listening = false;

    /**
     * @var LoopInterface
     */
    protected $loop;

    /**
     * @var resource
     */
    protected $fileDescriptor;

    /**
     * @var callable
     */
    protected $writeListener;

    /**
     * @var array
     */
    protected $messages = array();

    /**
     * @param ZSocket     $socket
     * @param resource      $fileDescriptor
     * @param LoopInterface $loop
     * @param callable      $writeListener
     */
    public function __construct(ZSocket $socket, $fileDescriptor, LoopInterface $loop, callable $writeListener)
    {
        $this->socket = $socket;
        $this->fileDescriptor = $fileDescriptor;
        $this->loop = $loop;
        $this->writeListener = $writeListener;
    }

    /**
     * @param string $message
     */
    public function send($message)
    {
        if ($this->closed) {
            return;
        }

        $this->messages[] = $message;

        if (!$this->listening) {
            $this->listening = true;
            $this->loop->addWriteStream($this->fileDescriptor, $this->writeListener);
        }
    }

    public function end()
    {
        $this->closed = true;

        if (!$this->listening) {
            $this->emit('end');
        }
    }

    public function handleWriteEvent()
    {
        foreach ($this->messages as $i => $message) {
            try {

                $sent = (bool) $this->socket->send($message);

                if ($sent) {
                    unset($this->messages[$i]);

                    if (0 === count($this->messages)) {
                        $this->loop->removeWriteStream($this->fileDescriptor);
                        $this->listening = false;
                        $this->emit('end');
                    }
                }
            } catch (Exception $e) {
                $this->emit('error', array($e));
            }
        }
    }
}