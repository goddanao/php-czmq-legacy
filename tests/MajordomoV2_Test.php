<?php

use Spork\Fork;
use Spork\ProcessManager;

class MajordomoV2Test extends \PHPUnit_Framework_TestCase {

    function test_mdpbroker() {

        $manager = new ProcessManager();

        $broker_endpoint = 'ipc:///tmp/mdpbroker.dtest';

        # Run Broker
        $manager->fork(function() use($broker_endpoint) {
            $broker = new Majordomo\Broker($broker_endpoint, false);
            $zloop = new ZLoop();
            $zloop->start();
        });

        # Run 5 Workers
        for($i = 0; $i < 5; $i++) {
            $manager->fork(function () use ($broker_endpoint, $i) {
                $worker = new Majordomo\Worker('myworker', $broker_endpoint, function ($req) use ($i) {
                    $usec = rand(1000, 500000);
                    usleep($usec);
                    return "OK";
                });
                $worker->run();
            });
        }

        $loop   = new ZLoop();

        $loop->add_timer(3000, function($timer_id, \ZLoop $loop){
            $loop->stop();
        });

        $requests = [];

        $loop->add_timer(1, function($timer_id, $loop) use ($broker_endpoint, $manager, &$requests) {
            for($i = 0; $i < 10; $i++) {
                usleep(100000);
                $requests[] = $manager->fork(function() use($i, $broker_endpoint) {
                    $client = new Majordomo\Client($broker_endpoint);
                    $requestId = "requestId - " . $i;
                    $result = $client->call('myworker', $requestId);
                    if($result) {
                        return $result->pop_string();
                    }
                });
            }
        });

        $loop->start();

        $res = true;
        foreach($requests as $client){
            $client->receive();
            $res = $res && ($client->getResult() == "OK");
        }

        $manager->killAll();

        $this->assertTrue($res);
    }

}