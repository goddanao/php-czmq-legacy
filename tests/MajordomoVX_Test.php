<?php

use Spork\Fork;
use Spork\ProcessManager;

class MajordomoVXTest extends \PHPUnit_Framework_TestCase {

    function test_mdpbroker() {

        $broker_endpoint = 'ipc:///tmp/mdpbroker.test';
        $manager = new ProcessManager();

        # Start Broker
        $manager->fork(function() use($broker_endpoint) {
            $broker = new Majordomo\VX\Broker();
            $broker->bind($broker_endpoint);
            $zloop = new ZLoop();
            $zloop->add_timer(1000, function () use ($broker) {
                $status = $broker->get_status();
                foreach($status['services'] as $svc_name => $svc)
                    Zsys::info("MDP: STATUS {$svc_name} -> WRKS: {$svc['workers']} REQS: {$svc['requests']} WAIT: {$svc['waiting']} BLACK: {$svc['blacklist']}");
            }, 10);
            $zloop->start();
        });

        # Start Workers
        for($i = 0; $i < 5; $i++)
            $manager->fork(function() use($i, $broker_endpoint) {
                $worker = new Majordomo\VX\Worker($broker_endpoint, 'myworker');
                $processed = 0;
                $worker->run(function ($req) use ($i, &$processed) {
                    $processed++;
                    $usec = rand(($i < 2) ? 1 : 1000, ($i < 2) ? 1000 : 50000);
                    Zsys::info("worker-{$i} - processed: {$processed} -> $req -> sleeping {$usec} ms ...");
                    usleep($usec);
                });
            });

        # Start Clients (Send Work)
        for($i = 0; $i < 50; $i++)
            $clients[] = $manager->fork(function() use($i, $broker_endpoint) {
                $m = new Majordomo\VX\Client($broker_endpoint);
                $requestId = "requestId - " . $i;
                $result = $m->call('myworker', $requestId);
                if($result) {
                    $result_str = $result->pop_string();
                    return $result_str == $requestId ? "OK" : "KO";
                }
                return "KO";
            });

        sleep(5);

        $res = true;
        foreach($clients as $client){
            $client->receive();
            $res = $res && ($client->getResult() == "OK");
        }

        $manager->killAll();

        $this->assertTrue($res);
    }

}