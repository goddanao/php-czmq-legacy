<?php

use Spork\Fork;
use Spork\ProcessManager;

class SuperClosure_Test extends \PHPUnit_Framework_TestCase {

    public function test_encode_decode_json() {
        $msg = new ZMsg();
        $closure = function ($a, $b) {
            echo "hello this is my closure! ($a, $b)\n";
        };
        $msg->append($closure);
        $msg->dump();
    }


}