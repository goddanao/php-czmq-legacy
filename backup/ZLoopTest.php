<?php

class ZLoopTest extends \PHPUnit_Framework_TestCase {

    public function test_create() {
         $loop = new ZLoop();
         $loop->set_verbose(true);
         $loop = null;
    }
}