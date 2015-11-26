<?php

class ZFrameTest extends \PHPUnit_Framework_TestCase {

    public function test_create() {
        $frame = new ZFrame();
        $this->assertNotNull($frame);
    }

//    public function test_pack_unpack() {
//        $frame = new ZFrame();
//        $frame->pack("nvc*", 0x1234, 0x5678, 65, 66);
//        // echo "{$frame} -> " . bin2hex($frame) . "\n";
//        $unpacked = $frame->unpack("nvc*");
//        // print_r($unpacked);
//
//    }

}