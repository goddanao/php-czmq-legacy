<?php

use Spork\Fork;
use Spork\ProcessManager;

class MajordomoV2Test extends \PHPUnit_Framework_TestCase {

    public static function tearDownAfterClass() {
        exec("rm -rf ./.titanic");
    }

    function test_mdpbroker() {

        $manager = new ProcessManager();
        $manager->zombieOkay(true);

        $broker_endpoint = 'ipc:///tmp/mdpbroker.dtest';

        # Run Broker
        $manager->fork(function() use($broker_endpoint) {
            $broker = new Majordomo\Broker($broker_endpoint, false);
            $zloop = new ZLoop();
            $zloop->start();
        });

        # Run Titanic
        $manager->fork(function() use($broker_endpoint) {
            $titanic = new Majordomo\Titanic($broker_endpoint);
            $titanic->run();
        });

        # Run 5 Workers
        for($i = 0; $i < 1; $i++) {
            $manager->fork(function () use ($broker_endpoint, $i) {
                $worker = new Majordomo\Worker('myworker', $broker_endpoint, function ($req) use ($i) {
                    // $usec = rand(1000, 500000);
                    // usleep($usec);
                    return "OK";
                });
                $worker->run();
            });
        }

        $loop   = new ZLoop();

        $loop->add_timer(7000, function($timer_id, \ZLoop $loop){
            $loop->stop();
        });

        $requests = [];

        // test mdp
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

        // test mdp + titanic
        $loop->add_timer(3000, function($timer_id, $loop) use ($broker_endpoint, $manager) {
            $requests[] = $manager->fork(function() use($i, $broker_endpoint) {

                $client = new Majordomo\Client($broker_endpoint);
                $requestPayload = "requestId - " . $i;
                $msg = new ZMsg();
                $msg->append_string('myworker');
                $msg->append_string($requestPayload);

                $result = $client->call('titanic.request', $msg);

                $success = ($result && $result[0] == "200");
                if($success) {
                    $tid = $result[1];
                    sleep(3); // wait for titanic to route
                    $result = $client->call("titanic.reply", $tid);
                    $success = ($result[0] == "200" && $result[1] == $tid && $result[2] == "OK");
                    $result = $client->call("titanic.close", $tid);
                    $success = $success && ($result[0] == "200" && $result[1] == $tid);
                }
                return $success ? "OK" : "KO";
            });
        });

        $loop->start();

        $res = true;
        foreach($requests as $client) {
            $client->receive();
            $res = $res && ($client->getResult() == "OK");
        }

        $manager->killAll();

        $this->assertTrue($res);
    }

}