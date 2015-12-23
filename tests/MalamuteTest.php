<?php

use Spork\Fork;
use Spork\ProcessManager;

class MalamuteTest extends \PHPUnit_Framework_TestCase {

    protected static $broker_endpoint = "tcp://127.0.0.1:8940";
    protected static $mg;

    protected function setUp() {
        if (!class_exists("\\Malamute\\Broker"))
            $this->markTestSkipped("Malamute test skipped since ZMQ version is lower than 4.2.0");

    }

    public static function setUpBeforeClass() {
        if (!class_exists("\\Malamute\\Broker"))
            return;

        self::$mg = new ProcessManager();
        self::$mg->zombieOkay(true);
        self::$mg->fork(function(){
            Malamute\Broker::run(self::$broker_endpoint);
        });
    }

    public static function tearDownAfterClass() {
        if (!class_exists("\\Malamute\\Broker"))
            return;
        self::$mg->killAll();
    }

    public function test_producer_consumer() {
        $this->markTestSkipped("Still randomly failing ... need to investigate more ...");

        $manager = new ProcessManager();

        $msg_count = 10;

        $endpoint = self::$broker_endpoint;

        # Start a Stream Consumer
        $client[] = $manager->fork(function() use ($msg_count, $endpoint) {
            $processed = 0;
            $worker = new Malamute\Consumer($endpoint);
            $worker->consume("my_stream.mysubject");
            $zloop = new ZLoop();
            $zloop->add($worker, function($me) use (&$processed, $msg_count) {
                $msg = $me->recv();
                $processed++;
            });
            $zloop->add_timer(1500, function($timer_id, $loop) {
                $loop->stop();
            });
            $zloop->start();
            return ($msg_count == $processed) ? "OK" : "KO";
        });

        # Start another Stream Consumer
        $client[] = $manager->fork(function() use ($msg_count, $endpoint) {
            $processed = 0;
            Malamute\Consumer::run($endpoint, "my_stream.mysubject", function($msg, $headers) use (&$processed, $msg_count) {
                $processed++;
                return ($processed < $msg_count) ? true : false;
            });
            return ($msg_count == $processed) ? "OK" : "KO";
        });

        # Start another Stream Producer (ZLoop based)
        $manager->fork(function() use ($msg_count, $endpoint) {
            $processed = 0;
            $worker = new Malamute\Producer($endpoint, "my_stream");
            $zloop = new ZLoop();
            $zloop->add_timer(1, function($timer_id, $loop) use (&$worker, &$processed, $msg_count) {
                $worker->send("myothersubject", "mydata");
                $processed++;
            }, 10);
            $zloop->add_timer(1500, function($timer_id, $loop) {
                $loop->stop();
            });
            $zloop->start();
        });

        $manager->fork(function() use ($msg_count, $endpoint) {
            $processed = 0;
            Malamute\Producer::run($endpoint, "my_stream.mysubject", function() use (&$processed, $msg_count) {
                return ($processed++ < $msg_count) ? "mydata" : false;
            });
        });

        sleep(2);

        foreach($client as $c) {
            $c->receive();
            $result = $c->getResult();
            $this->assertEquals($result,"OK");
        }

        $manager->killAll();

    }

    public function test_queued_service()
    {
        $manager = new ProcessManager();

        $endpoint = self::$broker_endpoint;

        $w = $manager->fork(function() use ($endpoint) {
            $done = "KO";
            Malamute\Worker::run($endpoint, "my_mailbox_worker", function($req, $headers) use(&$done) {
                $done = "OK";
                return false;
            });
            return $done;
        });

        # Start Client (Send Work to MailBox)
        $manager->fork(function() use ($endpoint) {
            $service_client = new Malamute\Client($endpoint);
            $service_client->call('my_mailbox_worker', 'mydata','mydata');
        });

        sleep(2);

        $w->receive();
        $result = $w->getResult();
        $manager->killAll();
        $this->assertTrue($result == "OK");

    }

    public function test_pooled_service() {

        $manager = new ProcessManager();

        $endpoint = self::$broker_endpoint;

        # Start Service Workers
        for($i = 0; $i < 5; $i++)
            $forks[] = $manager->fork(function() use($i, $endpoint) {
                $processed = 0;
                Malamute\Worker::run($endpoint, "my_worker.mywork.*", function($req, $me) use($i, &$processed) {
                    $processed++;
                    $usec = rand(0, 1000);
                    usleep($usec);
                    return "mydata";
                });
            });

        # Start Clients (Send Work to Services)
        for($i = 0; $i < 10; $i++)
        $clients[] = $manager->fork(function() use($endpoint) {
                $service_client = new Malamute\Client($endpoint);
                $rcv = $service_client->call('my_worker.mywork', json_encode(['gino' => 'pino']));
                return $rcv == "mydata" ? "OK" : "KO";
            });

        sleep(2);


        $res = true;
        foreach($clients as $client){
            $client->receive();
            $res = $res && ($client->getResult() == "OK");
        }


        $manager->killAll();

        $this->assertTrue($res);

    }

}