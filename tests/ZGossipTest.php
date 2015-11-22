<?php

class ZGossipTest extends \PHPUnit_Framework_TestCase {


    public function test_create()
    {
        $gossip = new ZGossip();
        $this->assertNotNull($gossip);
    }

    public function test_gossip(){
        $gossip1 = new ZGossip();
        // $gossip1->set_verbose(true);
        $port = $gossip1->bind("tcp://127.0.0.1:*");

        $gossip2 = new ZGossip();
        $gossip2->connect("tcp://127.0.0.1:{$port}");

        $gossip3 = new ZGossip();
        $gossip3->connect("tcp://127.0.0.1:{$port}");

        $gossip1->publish("hello", "world");

        $msg = $gossip2->recv();
        $msg = $msg->pop_picture("sss");
        $this->assertEquals($msg[0], "DELIVER");
        $this->assertEquals($msg[1], "hello");
        $this->assertEquals($msg[2], "world");

        $msg = $gossip3->recv();
        $msg = $msg->pop_picture("sss");
        $this->assertEquals($msg[0], "DELIVER");
        $this->assertEquals($msg[1], "hello");
        $this->assertEquals($msg[2], "world");

    }

}