<?php

class ZPollTest extends \PHPUnit_Framework_TestCase {

    private $poller;
    private $sock_push;
    private $sock_pull;

    protected function setUp()
    {
        $endpoint = "ipc:///tmp/push_pull";
        $this->poller = new ZPoll();
        $this->sock_push = new ZSocket(ZSys::SOCKET_PUSH);
        $this->sock_push->connect($endpoint);
        $this->sock_pull = new ZSocket(ZSys::SOCKET_PULL);
        $this->sock_pull->bind($endpoint);
    }

    public function test_create() {
        $poller = new ZPoll();
        $this->assertNotNull($poller);
    }

    public function test_add_socket() { // ZSocket , ZActor , ZHandle
        $this->poller->add($this->sock_push, ZSys::POLL_OUT);
        $this->poller->add($this->sock_pull); // default POLL_IN
        $this->assertTrue($this->poller->has($this->sock_push) && $this->poller->has($this->sock_pull));
    }

    public function test_remove_socket() { // ZSocket , ZActor , ZHandle
        $this->poller->add($this->sock_push, ZSys::POLL_OUT);
        $res = $this->poller->has($this->sock_push);
        $this->poller->remove($this->sock_push);
        $this->assertTrue($res && !$this->poller->has($this->sock_push));
    }

    public function test_loop_no_events() {
        $this->poller->add($this->sock_pull); // default POLL_IN
        $res = $this->poller->poll(100);
        $this->assertFalse($res);
    }

    public function test_loop_events() {
        $this->poller->add($this->sock_push, ZSys::POLL_OUT);
        $this->poller->add($this->sock_pull); // default POLL_IN
        $this->sock_push->send_picture('s', 'hello!');
        $res = $this->poller->poll(100);
        $this->assertTrue($res);
    }

    public function test_has_events_in() {
        $this->poller->add($this->sock_pull); // default POLL_IN
        $this->sock_push->send_picture('s', 'hello!');
        $res   = $this->poller->poll(500);
        $res_i = $this->poller->has_input($this->sock_pull);
        $this->assertTrue($res &&  $res_i);
    }

    public function test_has_events_out() {
        $this->poller->add($this->sock_push, ZSys::POLL_OUT);
        $this->poller->add($this->sock_pull);
        $this->sock_push->send_picture('s', 'hello!');
        $res   = $this->poller->poll(500);
        $res_i = $this->poller->has_input($this->sock_pull);
        $res_o = $this->poller->has_output($this->sock_push);
        $this->assertTrue($res &&  !$res_i && $res_o);
    }

}