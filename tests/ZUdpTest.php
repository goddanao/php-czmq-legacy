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
        $frame = $udp2->recv();
        $this->assertNotNull($frame);
        $this->assertTrue($frame == "hello");
        $frame = $udp2->recv();
        $this->assertNotNull($frame);
        $this->assertTrue($frame == "world");
    }

}