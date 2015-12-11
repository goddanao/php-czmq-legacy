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
            Majordomo\Broker::run($broker_endpoint);
        });

        # Wait for Broker to bind the address
        sleep(1);

        # Run Titanic
        $manager->fork(function() use($broker_endpoint) {
            Majordomo\Titanic::run($broker_endpoint);
        });

        # Run 5 Workers
        for($i = 0; $i < 1; $i++) {
            $manager->fork(function () use ($broker_endpoint, $i) {
                Majordomo\Worker::run('myworker', $broker_endpoint, function ($req) use ($i) {
                    return "OK";
                });
            });
        }

        # Run 5 Workers
        for($i = 0; $i < 1; $i++) {
            $manager->fork(function () use ($broker_endpoint, $i) {
                $loop = new ZLoop();
                $worker = new Majordomo\Worker('myworker', $broker_endpoint);
                $loop->add($worker, function($socket, $zloop) use ($i) {
                    $msg = $socket->recv();
                    if($msg)
                        $socket->send("OK");
                });
                $loop->start();
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
                usleep(150000);
                $requests[] = $manager->fork(function() use($i, $broker_endpoint) {
                    $client = new Majordomo\Client($broker_endpoint);
                    $result = $client->call('myworker', "requestId - $i");
                    if($result) {
                        return $result->pop_string();
                    }
                });
            }
        });

        // test mdp + titanic
        $loop->add_timer(1000, function($timer_id, $loop) use ($broker_endpoint, $manager, &$requests) {
            $requests[] = $manager->fork(function() use($broker_endpoint) {
                $client = new Majordomo\Client($broker_endpoint);
                $result = $client->call('titanic.request', 'myworker', "requestId - $i");

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
            $r = $client->getResult();
            $res = $res && ($r == "OK");
        }

        $manager->killAll();

        $this->assertTrue($res);
    }

}