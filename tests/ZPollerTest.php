<?php

class ZPollerTest extends \PHPUnit_Framework_TestCase {

    private $poller;
    private $rep;
    private $req;

    protected function setUp()
    {
        $endpoint = "ipc:///tmp/rr_poll";

        $this->rep = new ZSocket('rep');
        $this->rep->bind($endpoint);
        $this->req = new ZSocket('req');
        $this->req->connect($endpoint);


        $this->poller = new ZPoller();
    }

    public function test_create() {
        $this->assertNotNull($this->poller);
    }

    public function test_on_idle() {
        $done = false;
        $this->poller->on_idle(function($poller) use (&$done){
            $done = true;
            $poller->stop();
        });
        $this->poller->start();
        $this->assertTrue($done);
    }

    public function test_poll() {
        $success = false;

        $this->poller->on_idle(function($poller){
            $poller->stop();
        });

        $this->poller->add($this->rep);
        $this->req->send_string('hello');

        $rep = $this->rep;
        $this->poller->start(function($socket, $poller) use (&$success, $rep) {
            $success = ($socket == $rep);
            $poller->stop();
        });
        $this->assertTrue($success);
    }

}