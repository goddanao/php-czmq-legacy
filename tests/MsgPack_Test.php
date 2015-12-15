<?php

use Spork\Fork;
use Spork\ProcessManager;

class MsgPack_Test extends \PHPUnit_Framework_TestCase {

    public function test_pack_unpack() {
        $arr = [
            "bool"    => true,
            "integer" => 1,
            "float"   => 1.544,
            "string"  => "mystring",
            "array"   => [ "one", "two", "three"],
            "map"     => [
                    "one"   => "other",
                    "two"   => 2342343242343
                ]
            ];
        $res = MsgPack::encode($arr);
        $result = MsgPack::decode($res);
        $this->assertEquals($arr, $result);
    }


}