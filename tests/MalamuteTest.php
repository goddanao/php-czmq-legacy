<?php

use Spork\Fork;
use Spork\ProcessManager;

class MalamuteTest extends \PHPUnit_Framework_TestCase {

    private $broker_endpoint = "tcp://127.0.0.1:9999";  // same as ./cfg/malamute.cfg

//    public function test_producer_consumer_zloop() {
//        $loop = new ZLoop();
//
//        $broker = new Malamute\Broker("mybroker");
//        $broker->load_config(__DIR__ . "/cfg/malamute.cfg");
//
//        # Start a Stream Producer
//        $worker = new Malamute\Producer($this->broker_endpoint, "my_stream");
//
//
//        $msg_count = 50;
//
//
//        $loop->add($worker, function() use(&$processed, $msg_count) {
//            $processed++;
//            $usec = rand(0, 1000);
//            usleep($usec);
//            return ($processed <= $msg_count) ? "mydata" : false;
//        });
//
//
//
//    }

        public function test_producer_consumer() {

        $manager = new ProcessManager();

        $manager->fork(function() {
            $broker = new Malamute\Broker("mybroker");
            $broker->load_config(__DIR__ . "/cfg/malamute.cfg");
            $broker->run();
        });

        $msg_count = 50;

        # Start a Stream Producer
        $manager->fork(function() use ($msg_count) {
            $processed = 0;
            $worker = new Malamute\Producer($this->broker_endpoint, "my_stream");
            $worker->run("mysubject", function() use(&$processed, $msg_count) {
                $processed++;
                $usec = rand(0, 1000);
                usleep($usec);
                return ($processed <= $msg_count) ? "mydata" : false;
            });
        });

        # Start a Stream Consumer
        $client = $manager->fork(function() use ($msg_count) {
            $processed = 0;
            $worker = new Malamute\Consumer($this->broker_endpoint, "my_stream");
            $worker->run("mysubject", function($msg, $headers) use(&$processed, $msg_count) {
                $processed++;
                return ($processed < $msg_count) ? true : false;
            });

            return ($msg_count == $processed) ? "OK" : "KO";
        });

        sleep(5);

        $client->receive();
        $result = $client->getResult();
        $manager->killAll();
        $this->assertEquals($result,"OK");
        $manager = null;

    }

    public function test_queued_service()
    {
        $manager = new ProcessManager();

        $manager->fork(function() {
            $broker = new Malamute\Broker("mybroker");
            $broker->load_config(__DIR__ . "/cfg/malamute.cfg");
            $broker->run();
        });

        $w = $manager->fork(function() {
            $done = false;
            $worker = new Malamute\Worker($this->broker_endpoint, "my_mailbox_worker");
            $worker->run(function($req, $headers) use(&$done) {
                $done = true;
                return false;
            });

            return $done ? "OK" : "KO";
        });

        # Start Client (Send Work to MailBox)
        $manager->fork(function() {
            $service_client = new Malamute\Client($this->broker_endpoint);
            $service_client->connect();
            $service_client->send_mailbox('my_mailbox_worker', json_encode(['gino' => 'pino' . $i]), 1000);
        });

        sleep(5);

        $w->receive();
        $result = $w->getResult();
        $manager->killAll();
        $this->assertEquals($result,"OK");
        $manager = null;

    }

    public function test_pooled_service()
    {
        $manager = new ProcessManager();

        $manager->fork(function() {
            $broker = new Malamute\Broker("mybroker");
            $broker->load_config(__DIR__ . "/cfg/malamute.cfg");
            $broker->run();
        });

        # Start Service Workers
        for($i = 0; $i < 5; $i++)
            $forks[] = $manager->fork(function() use($i) {
                $processed = 0;
                $worker   = new Malamute\Worker($this->broker_endpoint, "my_worker", "mywork*");
                $worker->run(function($req, $headers) use($i, &$processed) {
                    $processed++;
                    $usec = rand(0, 1000);
                    usleep($usec);
                    return "mydata";
                });
            });


        # Start Clients (Send Work to Services)
        for($i = 0; $i < 10; $i++)
            $clients[] = $manager->fork(function() use($i) {
                $service_client = new Malamute\Client($this->broker_endpoint, 'client_' . $i);
                $service_client->connect();
                $service_client->send_service('my_worker', 'mywork', json_encode(['gino' => 'pino']), 30000);
                $rcv = $service_client->recv();
                return $rcv == "mydata" ? "OK" : "KO";
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