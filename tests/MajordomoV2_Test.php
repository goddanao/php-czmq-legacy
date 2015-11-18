<?php

use Spork\Fork;
use Spork\ProcessManager;

class MajordomoV2Test extends \PHPUnit_Framework_TestCase {

    function test_mdpbroker() {

        $manager = new ProcessManager();

        $broker_endpoint = 'ipc:///tmp/mdpbroker.dtest';

        # Run Broker
        $manager->fork(function() use($broker_endpoint) {
            $broker = new Majordomo\V2\Broker($broker_endpoint, false);
            $zloop = new ZLoop();
            $zloop->start();
        });

        # Run 5 Workers
        for($i = 0; $i < 5; $i++) {
            $manager->fork(function () use ($broker_endpoint, $i) {
                $worker = new Majordomo\V2\Worker('myworker', $broker_endpoint, function ($req) use ($i) {
                    $usec = rand(1000, 500000);
                    usleep($usec);
                    return "OK";
                });
                $worker->run();
            });
        }

        $loop   = new ZLoop();

        $loop->add_timer(3000, function($timer_id, $loop){
            $loop->stop();
        });

        $requests = [];

        $loop->add_timer(1, function($timer_id, $loop) use ($broker_endpoint, $manager, &$requests) {
            for($i = 0; $i < 10; $i++) {
                usleep(100000);
                $requests[] = $manager->fork(function() use($i, $broker_endpoint) {
                    $client = new Majordomo\V2\Client($broker_endpoint);
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

    /*
    function test_mdpbroker() {

        $broker_endpoint = 'ipc:///tmp/mdpbroker.test';

        $manager = new ProcessManager();

        # Start Broker
        $manager->fork(function() use($broker_endpoint) {
            $broker = new MajordomoBroker();
            // $broker->set_verbose(false);
            $broker->bind($broker_endpoint);
            $broker->on_tick(function($broker) use (&$counter) {
                $status = $broker->get_status();
                foreach($status['services'] as $svc_name => $svc)
                    Zsys::info("MDP: STATUS {$svc_name} -> WRKS: {$svc['workers']} REQS: {$svc['requests']} WAIT: {$svc['waiting']} BLACK: {$svc['blacklist']}");
            });
            $broker->run();
        });

        # Start Workers
        for($i = 0; $i < 5; $i++)
            $manager->fork(function() use($i, $broker_endpoint) {
                $worker = new MajordomoWorker();
                $processed = 0;
                $worker->run('myworker', $broker_endpoint, function ($req) use ($i, &$processed) {
                    $processed++;
                    $usec = rand(500000, 2000000);
                    Zsys::info("worker id {$i} - processed: {$processed}: need to process ... " . $req->pop_string() . " sleeping {$usec} ms ...");
                    usleep($usec);
                });
            });

        # Start Clients (Send Work)
        for($i = 0; $i < 10; $i++)
            $clients[] = $manager->fork(function() use($i, $broker_endpoint) {
                $m = new MajordomoClient($broker_endpoint);
                $requestId = "requestId - " . $i;
                $result = $m->call('myworker', $requestId);
                $result_str = $result->pop_string();
                return $result_str == $requestId ? "OK" : "KO";
            });

        sleep(8);

        $res = true;
        foreach($clients as $client){
            $client->receive();
            $res = $res && ($client->getResult() == "OK");
        }
        $manager->killAll();

        $this->assertTrue($res);

    }
    */
}