<?php

class ZReactorTest extends \PHPUnit_Framework_TestCase {

    private $reactor;
    private $sock_push;
    private $sock_pull;

    protected function setUp()
    {
        $endpoint = "ipc:///tmp/push_pull";
        $this->reactor = new ZReactor();
        $this->reactor->set_verbose(false);
        $this->sock_pull = new ZSocket(ZSys::SOCKET_PULL);
        $this->sock_pull->bind($endpoint);
        $this->sock_push = new ZSocket(ZSys::SOCKET_PUSH);
        $this->sock_push->connect($endpoint);
    }

    public function test_create() {
        $reactor = new ZReactor();
        $this->assertNotNull($reactor);
    }

    public function test_add_socket() { // ZSocket , ZActor , ZHandle
        $this->reactor->add($this->sock_pull, function() {}); // default POLL_IN
        $this->reactor->add($this->sock_push, function() {}); // , ZSys::POLL_OUT);
        $this->assertTrue($this->reactor->has($this->sock_push) && $this->reactor->has($this->sock_pull));
    }

    public function test_remove_socket() { // ZSocket , ZActor , ZHandle
        $this->reactor->add($this->sock_push, function() {}, ZSys::POLL_OUT);
        $res = $this->reactor->has($this->sock_push);
        $this->reactor->remove($this->sock_push);
        $this->assertTrue($res && !$this->reactor->has($this->sock_push));
    }

    public function test_loop_no_events() {
        $this->reactor->add($this->sock_pull, function() {}); // default POLL_IN
        $res = $this->reactor->poll(100);
        $this->assertFalse($res);
    }

    public function test_loop_events() {
        $this->reactor->add($this->sock_push, function() {}, ZSys::POLL_OUT);
        $this->reactor->add($this->sock_pull, function() {}); // default POLL_IN
        $this->sock_push->send_picture('s', 'hello!');
        // usleep(100);
        $res = $this->reactor->poll(100);
        $this->assertTrue($res);
    }

    public function test_has_events_in() {
        $called = false;
        $this->reactor->add($this->sock_pull, function() use (&$called) {
            $called = true;
        }); // default POLL_IN

        $this->sock_push->send_picture('s', 'hello!');
        // usleep(100);
        $res   = $this->reactor->poll(100);
        $res_i = $this->reactor->has_input($this->sock_pull);
        $res_o = $this->reactor->has_output($this->sock_push);
        $this->assertTrue($res &&  $res_i && !$res_o && $called);
    }

    public function test_has_events_out() {
        $called = false;

        $this->reactor->add($this->sock_push, function() use (&$called) {
            $called = true;
        }, ZSys::POLL_OUT);

        $this->sock_push->send_picture('s', 'hello!');
        // usleep(100);
        $res   = $this->reactor->poll(100);
        $res_i = $this->reactor->has_input($this->sock_pull);
        $res_o = $this->reactor->has_output($this->sock_push);
        $this->assertTrue($res &&  !$res_i && $res_o && $called);
    }

}