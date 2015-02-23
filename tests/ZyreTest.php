<?php

class ZyreTest extends \PHPUnit_Framework_TestCase {

    public function test_create() {
        $zyre = new Zyre();
        $this->assertNotNull($zyre);
    }

    public function test_get_version() {
        $this->assertNotEmpty(Zyre::get_version());
    }

    public function test_get_set_name() {
        $name = "node_name";
        $zyre = new Zyre($name);
        $this->assertEquals($name, $zyre->get_name());
    }

    public function test_set_endpoint() {
        $n1 = new Zyre("node1");
        $n1->set_header("X-HELLO", "World");
        $this->assertTrue($n1->set_endpoint("inproc://zyre-node1"));
    }

    public function test_set_endpoint_name_already_exists() {
        $n1 = new Zyre("node1");
        $res_ok = $n1->set_endpoint("inproc://zyre-node1");
        $n1->start();
        $n2 = new Zyre("node2");
        $res_fail = $n2->set_endpoint("inproc://zyre-node1");
        $this->assertTrue($res_ok && !$res_fail);
    }

    public function test_start() {
        $n1 = new Zyre("node1");
        $n1->set_header("X-HELLO", "World");
        $n1->set_endpoint("inproc://zyre-node1");
        $n1->gossip_bind("inproc://gossip-hub");
        $this->assertTrue($n1->start());
    }

    public function test_all() {

        ## Start Node 1
        $n1 = new Zyre("node1");
        $n1->set_header("X-HELLO", "World");
        $n1->set_endpoint("inproc://zyre-node1");
        $n1->gossip_bind("inproc://gossip-hub");
        $this->assertTrue($n1->start());

        ## Start Node 2
        $n2 = new Zyre("node2");
        $this->assertFalse($n2->set_endpoint("inproc://zyre-node1"));
        $this->assertTrue($n2->set_endpoint("inproc://zyre-node2"));
        $n2->gossip_connect("inproc://gossip-hub");
        $this->assertTrue($n2->start());

        ## Node 1 <> Node 2
        $this->assertNotEquals($n1->get_uuid(), $n2->get_uuid());

        ## JOIN A COMMON GROUP (GLOBAL) and wait 100 ms to broadcast changes
        $n1->join("GLOBAL");
        $n2->join("GLOBAL");
        usleep(100);

        ## NODE2 AND NODE1 BECOME VISIBLE EACH OTHER
        $this->assertTrue(count($n1->get_peers()) == 1 && count($n2->get_peers()) == 1);

        ## JOIN OWN PRIVATE GROUP and wait 100 ms to broadcast changes
        $n1->join("PRIVATE-NODE1");
        $n2->join("PRIVATE-NODE2");
        usleep(100);

        ## NODE1, NODE2 BOTH HAVE 2 GROUPS (1 in common and 1 private)
        $this->assertTrue(count($n2->get_groups()) == 2 && count($n1->get_groups()) == 2);

        ## READ NODE1 HEADERS FROM NODE2
        $n1_id = $n2->get_peers()[0]['id'];
        $this->assertEquals($n2->get_peer_header($n1_id, "X-HELLO"), "World");

        ## NODE1 SHOUT SOME DATA TO GROUP
        $n1->send_group("GLOBAL", "Hello from node1!");

        ## NODE1 SHOUT SOME DATA TO NODE2
        $n2_id = $n1->get_peers()[0]['id'];
        $n1->send_peer($n2_id, "Private hello from node1!");

        ## NODE2 will recieve all messages (ENTER, JOIN, SHOUT)
        $enter_n1 = $n2->recv();
        $join_global_n1 = $n2->recv();
        $join_private_n1 = $n2->recv();
        $shout_global_n1 = $n2->recv();
        $whisper_n1      = $n2->recv();

        // print_r([$enter_n1, $join_global_n1, $join_private_n1, $shout_global_n1, $whisper_n1]);

        ## NODE2 will recieve all messages (ENTER, JOIN, JOIN, SHOUT, WHISPER)
        $this->assertEquals($enter_n1['command'], 'ENTER');
        $this->assertEquals($enter_n1['headers']['X-HELLO'], 'World');
        $this->assertEquals($join_global_n1['command'], 'JOIN');
        $this->assertEquals($join_global_n1['group'], 'GLOBAL');
        $this->assertEquals($join_private_n1['command'], 'JOIN');
        $this->assertEquals($join_private_n1['group'], "PRIVATE-NODE1");
        $this->assertEquals($shout_global_n1['command'], 'SHOUT');
        $this->assertEquals($shout_global_n1['group'], 'GLOBAL');
        $this->assertEquals($shout_global_n1['data'], "Hello from node1!");
        $this->assertEquals($whisper_n1['command'], 'WHISPER');
        $this->assertEquals($whisper_n1['data'], "Private hello from node1!");

    }




}