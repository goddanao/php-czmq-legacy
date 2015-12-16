<?php

class ZUdpTest extends \PHPUnit_Framework_TestCase {

    protected function setUp() {
        if (getenv("TRAVIS"))
            $this->markTestSkipped("No broadcast interface usable in TRAVIS-CI");

    }

    public function test_create() {
        $udp = new ZUdp();
        $this->assertNotNull($udp);
    }

    public function test_broadcast() {
        $udp1 = new ZUdp();
        $udp2 = new ZUdp();

        $msg = new ZMsg();
        $msg->append_string("hello");
        $msg->append_string("world");
        $udp1->send($msg);
        $msg = $udp2->recv();
        $this->assertNotNull($msg);
        $sender = $msg->pop_string();
        $this->assertRegExp('/^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/sim', $sender);
        $this->assertEquals($msg->pop_string(), "hello");
        $msg = $udp2->recv();
        $this->assertNotNull($msg);
        $sender = $msg->pop_string();
        $this->assertRegExp('/^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/sim', $sender);
        $this->assertEquals($msg->pop_string(), "world");

        $udp1->send_zipped("hello");
        $msg = $udp2->recv();
        $this->assertNotNull($msg);
        $sender = $msg->pop_string();
        $this->assertRegExp('/^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/sim', $sender);
        $this->assertEquals($msg->pop_zipped(), "hello");

        $udp1->send_msgpack("hello");
        $msg = $udp2->recv();
        $this->assertNotNull($msg);
        $sender = $msg->pop_string();
        $this->assertRegExp('/^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/sim', $sender);
        $this->assertEquals($msg->pop_msgpack(), "hello");

    }

}