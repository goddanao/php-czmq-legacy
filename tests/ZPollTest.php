<?php

class ZPollTest extends \PHPUnit_Framework_TestCase {

    private $poller;
    private $sock_push;
    private $sock_pull;
    private $rep;
    private $req;

    protected function setUp() {
        $endpoint = "ipc:///tmp/push_pull_test";
        $this->sock_pull = ZSocket::pull($endpoint);
        $this->sock_push = ZSocket::push($endpoint);
        $this->rep = ZSocket::rep($endpoint);
        $this->req = ZSocket::req($endpoint);
    }

    public function test_create() {
        $this->poller = new ZPoll();
        $this->assertNotNull($this->poller);
    }

    public function test_add_socket() {
        $this->poller = new ZPoll();
        $this->poller->add($this->sock_push, ZSys::POLL_OUT);
        $this->poller->add($this->sock_pull); // default POLL_IN
        $this->assertTrue($this->poller->has($this->sock_push) && $this->poller->has($this->sock_pull));
    }

    public function test_remove_socket() { // ZSocket , ZActor , ZHandle
        $this->poller = new ZPoll();
        $this->poller->add($this->sock_push, ZSys::POLL_OUT);
        $res = $this->poller->has($this->sock_push);
        $this->poller->remove($this->sock_push);
        $this->assertTrue($res && !$this->poller->has($this->sock_push));
    }

    public function test_loop_no_events() {
        $this->poller = new ZPoll();
        $this->poller->add($this->sock_pull); // default POLL_IN
        $res = $this->poller->poll(500);
        $this->assertFalse($res);
    }

    public function test_loop_events() {
        $this->poller = new ZPoll();
        $this->poller->add($this->sock_push, ZSys::POLL_OUT);
        $this->poller->add($this->sock_pull); // default POLL_IN
        $this->sock_push->send_picture('s', 'hello!');
        $readers = []; $writers = [];
        $res = $this->poller->poll_array($readers, $writers, 500);
        $this->assertTrue($res);
        $this->assertEquals($this->sock_push, $writers[0]);
    }

    public function test_has_events_in() {
        $this->poller = new ZPoll();
        $this->poller->add($this->rep);
        $this->req->send_picture('s', 'hello!');
        $readers = []; $writers = [];
        $res = $this->poller->poll_array($readers, $writers, 500);
        $res_i = $this->poller->has_input($this->rep);
        $this->assertTrue($res, "poll");
        $this->assertTrue($res_i, "has events in");
        $this->assertEquals($this->req, $readers[0]);
    }

    public function test_has_events_out() {
        $this->poller = new ZPoll();
        $this->poller->add($this->sock_push, ZSys::POLL_OUT);
        $this->sock_push->send_picture('s', 'hello!');
        $readers = []; $writers = [];
        $res = $this->poller->poll_array($readers, $writers, 500);
        $res_o = $this->poller->has_output($this->sock_push);
        $this->assertTrue($res, "poll");
        $this->assertTrue($res_o, "has events out");
        $this->assertEquals($this->sock_push, $writers[0]);
    }

}