<?php

class ZProxyTest extends \PHPUnit_Framework_TestCase {

    private $proxy;
    private $push;
    private $pull;
    private $capture;

    protected function setUp()
    {
        $this->proxy = new ZProxy();
        $this->proxy->set_frontend(ZSys::SOCKET_PULL, "ipc:///tmp/frontend");
        $this->proxy->set_backend(ZSys::SOCKET_PUSH, "ipc:///tmp/backend");
        $this->proxy->set_capture("ipc:///tmp/capture");

        $this->push = new ZSocket(ZSys::SOCKET_PUSH);
        $this->push->connect("ipc:///tmp/frontend");

        $this->pull = new ZSocket(ZSys::SOCKET_PULL);
        $this->pull->connect("ipc:///tmp/backend");
        $this->pull->set_rcvtimeo(500);

        $this->capture = new ZSocket(ZSys::SOCKET_PULL);
        $this->capture->bind("ipc:///tmp/capture");
        $this->capture->set_rcvtimeo(500);
    }

    public function test_send_recv() {
        $type = "s"; $data = "hello";
        $this->push->send_picture($type, $data);
        $result = $this->pull->recv_picture($type);
        $this->assertEquals($data, $result[0]);
    }

    public function test_send_recv_capture() {

        $type = "s"; $data = "hello";
        $this->push->send_picture($type, $data);
        $result_capture = $this->capture->recv_picture($type);
        $this->assertTrue($data === $result_capture[0]);
    }


    public function test_pause_resume() {

        $this->proxy->pause();

        $this->push->send_string("hello");
        $this->assertNull($this->pull->recv_string());

        $this->proxy->resume();
        $result = $this->pull->recv_string();
        $this->assertEquals("hello", $result);

    }


}