<?php

class ZUdpTest extends \PHPUnit_Framework_TestCase {

    public function test_create() {
        $udp = new ZUdp();
        $this->assertNotNull($udp);
    }
}