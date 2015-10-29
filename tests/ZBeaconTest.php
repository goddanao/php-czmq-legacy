<?php

class ZBeaconTest extends \PHPUnit_Framework_TestCase {

    public function test_create()
    {
        $speaker = new ZBeacon();
        $this->assertNotNull($speaker);
    }

    public function test_beacon(){

        $speaker  = new ZBeacon();
        //$speaker->set_verbose();
        $speaker_hostname  = $speaker->set_port(9999);
        $this->assertNotEmpty($speaker_hostname);

        $listener = new ZBeacon();
        //$listener->set_verbose();
        $listener_hostname = $listener->set_port(9999);
        $this->assertNotEmpty($listener_hostname);

        $this->assertEquals($speaker_hostname, $listener_hostname);

        ## Subscibe all notifications
        $listener->subscribe("");

        ## Send magic value ...
        $speaker->publish(pack('C2', 0xCA, 0xFE), 100);

        ## Wait a beacon ... (default timeout 500 ms)
        $msg = $listener->recv();
        $this->assertNotNull($msg);

        ## First frame is sender address then message data (as byte stream)
        $result = $msg->pop_picture('sb');

        $sender_hostname = $result[0];
        $this->assertNotEmpty($sender_hostname);
        $this->assertEquals($sender_hostname, $speaker_hostname);

        ## NB Must reindex array cause not using labels in unpack
        $sender_data = array_values(unpack('C2', $result[1]));

        $this->assertTrue($sender_data[0] == 0xCA);
        $this->assertTrue($sender_data[1] == 0xFE);

    }
}