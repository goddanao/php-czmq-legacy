<?php

class ZUdpTest extends \PHPUnit_Framework_TestCase {

    public function test_create() {
        $udp = new ZUdp();
        $this->assertNotNull($udp);
    }

    public function test_broadcast() {
        $udp1 = new ZUdp();
        $udp2 = new ZUdp();

        $msg = new ZMsg();
        $msg->append_string("hello");
        $udp1->send($msg);

        $frame = $udp2->recv();

        $frame->dump();

    }

}