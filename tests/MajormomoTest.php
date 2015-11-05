<?php

use Spork\Fork;
use Spork\ProcessManager;

class MajordomoTest extends \PHPUnit_Framework_TestCase {

    function test_mdpbroker() {

        $broker_endpoint = 'ipc:///tmp/mdpbroker.test';

        $manager = new ProcessManager();

        # Start Broker
        $manager->fork(function() use($broker_endpoint) {
            $broker = new Majordomo\Broker();
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
                $worker = new Majordomo\Worker();
                $processed = 0;
                $worker->run('myworker', $broker_endpoint, function ($req) use ($i, &$processed) {
                    $processed++;
                    $usec = rand(100000, 500000);
                    Zsys::info("worker id {$i} - processed: {$processed}: need to process ... " . $req->pop_string() . " sleeping {$usec} ms ...");
                    usleep($usec);
                });
            });

        # Start Clients (Send Work)
        for($i = 0; $i < 10; $i++)
            $clients[] = $manager->fork(function() use($i, $broker_endpoint) {
                $m = new Majordomo\Client($broker_endpoint);
                $requestId = "requestId - " . $i;
                $result = $m->call('myworker', $requestId);
                $result_str = $result->pop_string();
                return $result_str == $requestId ? "OK" : "KO";
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