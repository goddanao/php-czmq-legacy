<?php

class ZSysTest extends \PHPUnit_Framework_TestCase {

    protected function setUp() {


    }

    public function test_create() {
        $context = ZSys::Context();
        $this->assertNotNull($context);
        $this->assertEquals(get_class($context, "ZContext"));
    }


}