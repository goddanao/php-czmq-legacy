<?php

class ZLoopTest extends \PHPUnit_Framework_TestCase
{

    private $loop;
    private $rep;
    private $req;

    protected function setUp()
    {
        $endpoint = "ipc:///tmp/rep";

        $this->loop = new ZLoop();

        $this->rep = new ZSocket(ZSys::SOCKET_REP);
        $this->rep->bind($endpoint);
        $this->req = new ZSocket(ZSys::SOCKET_REQ);
        $this->req->connect($endpoint);

    }

    public function test_create()
    {
        $this->assertNotNull($this->loop);
    }

    public function test_timer() {
        $count = 0;
        $this->loop->add_timer(500, function($timer_id, $zloop) use (&$count) {
            $count++;
            if($count == 2) {
                $zloop->stop();
            }
        }, 5);

        $this->loop->start();

        $this->assertEquals($count, 2);
    }

    public function test_add()
    {

        $return = "";
        $this->loop->add($this->rep, function($socket, $zloop) use (&$return) {
            $msg = $socket->recv();
            $return = $msg->pop_string();
        });

        // Stop after 1 sec
        $this->loop->add_timer(1000, function($timer_id, $zloop) {
           $zloop->stop();
        });

        $this->req->send_string("hello");

        $this->loop->start();

        $this->assertEquals("hello", $return);

    }
}