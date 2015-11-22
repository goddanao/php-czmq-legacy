<?php

class ZSysTest extends \PHPUnit_Framework_TestCase {

    public function test_version() {
        $versions['zmq'] = ZSys::libzmq_version();
        $versions['czmq'] = ZSys::libczmq_version();
        $versions['zyre'] = ZSys::libzyre_version();
        $versions['mlm'] = ZSys::libmlm_version();
        foreach($versions as $lib => $version)
            $this->assertNotEmpty($version);
    }

}