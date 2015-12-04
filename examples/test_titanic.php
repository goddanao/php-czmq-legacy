<?php

require_once __DIR__ . "/../vendor/autoload.php";

use Spork\Fork;
use Spork\ProcessManager;


class MyTitanicStorageHandler implements \Majordomo\ITitanicStorage {

    public function read($what, $uuid) {
        ZSys::info(__METHOD__ . " ($what) - $uuid - by php");
        return new ZMsg();
    }

    public function store($what, $uuid, \ZMsg $msg) {
        ZSys::info(__METHOD__ . " ($what) - $uuid - by php");
    }

    public function close($uuid) {
        ZSys::info(__METHOD__ . " - $uuid - by php");
    }

    public function status($uuid) {
        ZSys::info(__METHOD__ . " - $uuid - by php");
        return "200";
    }

    public function process() {
        ZSys::info(__METHOD__ . " by php");
    }

    public function test() {
        ZSys::info(" TEST by php");
    }

}

$manager = new ProcessManager();
$manager->zombieOkay();

$broker_endpoint = 'ipc:///tmp/mdpbroker.dtest';

# Run Broker
$manager->fork(function() use($broker_endpoint) {
    $broker = new Majordomo\Broker($broker_endpoint, false);
    $zloop = new ZLoop();
    $zloop->start();
});

# Run 1 Worker
for($i = 0; $i < 1; $i++) {
    $manager->fork(function () use ($broker_endpoint, $i) {
        $worker = new Majordomo\Worker('myworker', $broker_endpoint, function ($req) use ($i) {
            ZSys::info("Worker got requests!!!!!!");
//            $usec = rand(1000, 500000);
//            usleep($usec);
            return "OK";
        });
        $worker->run();
    });
}

//# Run 1 Titanic Instance
for($i = 0; $i < 1; $i++) {
    $manager->fork(function () use ($broker_endpoint, $i) {
        $handler = new MyTitanicStorageHandler();
        $titanic = new Majordomo\Titanic($broker_endpoint);
        $titanic->run();
    });
}


$loop   = new ZLoop();
$loop->add_timer(10000, function($timer_id, \ZLoop $loop){
    $loop->stop();
});

$requests = [];

$loop->add_timer(1, function($timer_id, $loop) use ($broker_endpoint, $manager, &$requests) {
    for($i = 0; $i < 1; $i++) {
        usleep(5000);
        $requests[] = $manager->fork(function() use($i, $broker_endpoint) {
            $client = new Majordomo\Client($broker_endpoint);
            $msg = new ZMsg();
            $msg->append_string("myworker");
            $msg->append_string("requestId - " . $i);
            $result = $client->call('titanic.request', $msg);
            $tid = $result[1];
            ZSys::info("Got Response: $tid");


            sleep(1);
            ZSys::info("Calling Titanic REPLY: $tid");
            $result = $client->call('titanic.reply', $tid);
            ZSys::info("Called Titanic REPLY: $tid ");
            // if($result[1] === "OK") {
                ZSys::info("Calling titanic.close $tid");
                $result = $client->call('titanic.close', $tid);
                ZSys::info("Got Response from close: $result");
            // }


        });
    }
});

$loop->start();

$manager->killAll();