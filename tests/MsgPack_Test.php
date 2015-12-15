<?php

use Spork\Fork;
use Spork\ProcessManager;

class Buddy {
    public $_name;
    public $_age;

    public function __construct($name, $age) {
        $this->_name = $name;
        $this->_age = $age;
    }
}


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

    public function test_pack_unpack_object() {
        $object = new Buddy("mario", 40);
        $res = MsgPack::encode($object);
        $result = MsgPack::decode($res);
        $this->assertEquals($object, $result);
    }

    public function test_pack_unpack_object_custom() {

        $object = new Buddy("mario", 40);

        $res = MsgPack::encode($object);
        $result = MsgPack::decode($res, function($cn, $props) {
            return new $cn($props['_name'], $props['_age']);
        });
        $this->assertEquals($object, $result);
    }

}