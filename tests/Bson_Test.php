<?php

use Spork\Fork;
use Spork\ProcessManager;

class Bson_Test extends \PHPUnit_Framework_TestCase {

    public function test_encode_decode_json() {
        $object = new Buddy("mario", 40);
        $json = json_encode($object, JSON_PRETTY_PRINT);
        $res  = \Bson\Bson::json_to_bson($json);
        $j = \Bson\Bson::bson_to_json($res);
        $this->assertEquals(json_decode($json,true), json_decode($j,true));
    }

    public function test_encode_decode() {
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
        $res = \Bson\Bson::encode($arr);
        $result = \Bson\Bson::decode($res);
        $this->assertEquals($arr, $result);
    }

    public function test_encode_decode_object() {
        $object = new Buddy("mario", 40);
        $object_json = json_decode(json_encode($object), true);
        $res = \Bson\Bson::encode($object);
        $result = \Bson\Bson::decode($res);
        $this->assertEquals($result, $object_json);
    }

//
//    public function test_pack_unpack_object_custom() {
//
//        $object = new Buddy("mario", 40);
//
//        $res = \MsgPack\MsgPack::encode($object);
//        $result = \MsgPack\MsgPack::decode($res, function($cn, $props) {
//            return new $cn($props['_name'], $props['_age']);
//        });
//        $this->assertEquals($object, $result);
//    }

}