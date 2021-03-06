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

    protected function setUp()
    {
//        $fun = function($type, $val, $args) {
//            ZSys::info("dentro il default encoder ...");
//        };
//
//      ZSys::set_default_encoder(ZSys::ENCODER_MSGPACK, $fun);

    }

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
        $res = \MsgPack\MsgPack::encode($arr);
        $result = \MsgPack\MsgPack::decode($res);
        $this->assertEquals($arr, $result);
    }
//
//    public function test_pack_unpack_object() {
//        $object = new Buddy("mario", 40);
//        $res = \MsgPack\MsgPack::encode($object);
//        $result = \MsgPack\MsgPack::decode($res);
//        $this->assertEquals($object, $result);
//    }
//
//    public function test_pack_unpack_object_custom() {
//
//        $object = new Buddy("mario", 40);
//
//        $res = \MsgPack\MsgPack::encode($object);
//
//        $result = \MsgPack\MsgPack::decode($res, function($type, $value, $args) {
//            if($type == \MsgPack\MsgPack::MSGPACK_OBJECT_MAP && count($args) == 1) {
//                return new $args[0]($value['_name'], $value['_age']);
//            }
//        });
//        $this->assertEquals($object, $result);
//    }

}