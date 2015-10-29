<?php

class MajordomoTest extends \PHPUnit_Framework_TestCase {


    private function forkWorker($broker_endpoint, $i) {
        $pid = pcntl_fork();
        if($pid !== 0) return $pid;

        sleep(1);

        $worker = new Majordomo\Worker();
        $processed = 0;
        $worker->run('myworker', $broker_endpoint, function ($rep) use ($i, &$processed) {
            $processed++;
            $sec = rand(1,5);
            Zsys::info("worker id {$i} - processed: {$processed}: need to process ... " . $rep->pop_string() . " sleeping {$sec} seconds ...");
            sleep($sec);
        });
        exit;
    }

    private function forkClient($broker_endpoint) {
        $pid = pcntl_fork();
        if($pid !== 0) return $pid;

        sleep(2);

        $m = new Majordomo\Client($broker_endpoint);
        $m->call('myworker', []);
        exit;
    }

    function test_mdpbroker() {

        $broker_endpoint = 'ipc:///tmp/mdpbroker.test';

        # Star 10 workers
        for ($i = 0; $i < 10; $i++)
            $pids[] = $this->forkWorker($broker_endpoint, $i);

        # Send some work
        for ($i = 0; $i < 100; $i++)
            $pids[] = $this->forkClient($broker_endpoint);

        $broker = new Majordomo\Broker();
        // $broker->set_verbose();
        $broker->bind($broker_endpoint);

        $counter = 5;
        $broker->on_idle(function($broker) { Zsys::info("MDP: IDLE"); });
        $broker->on_tick(function($broker) use (&$counter) {
            if(--$counter == 0) $broker->stop();
            $status = $broker->get_status();
            foreach($status['services'] as $svc_name => $svc)
                Zsys::info("MDP: STATUS {$svc_name} -> WRKS: {$svc['workers']} REQS: {$svc['requests']} WAIT: {$svc['waiting']} BLACK: {$svc['blacklist']}");
        });

        # run the broker
        $broker->run();

        foreach ($pids as $pid)
            exec("kill $pid");

    }
}