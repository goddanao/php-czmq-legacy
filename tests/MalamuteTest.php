<?php

use Spork\Fork;
use Spork\ProcessManager;

class MalamuteTest extends \PHPUnit_Framework_TestCase {

    const BROKER_ENDPOINT = "tcp://127.0.0.1:9999";

//    public function test_get_client() {
//
//        $broker = new Malamute\Broker(true);
//        $broker->bind(MalamuteTest::BROKER_ENDPOINT);
//
//        $worker = new Malamute\Worker();
//        $this->assertNotNull($worker);
//        $c = $worker->get_client();
//        $this->assertNotNull($c);
//        $this->assertInstanceOf("Malamute\\Client", $c);
//
//        $consumer = new Malamute\Consumer();
//        $this->assertNotNull($consumer);
//        $c = $consumer->get_client();
//        $this->assertNotNull($c);
//        $this->assertInstanceOf("Malamute\\Client", $c);
//
//        $producer = new Malamute\Producer();
//        $this->assertNotNull($producer);
//        $c = $producer->get_client();
//        $this->assertNotNull($c);
//        $this->assertInstanceOf("Malamute\\Client", $c);
//    }


    public function test_producer_consumer() {

        $manager = new ProcessManager();

        $msg_count = 50;

        # Start a Stream Producer
        $manager->fork(function() use ($msg_count) {
            sleep(2);
            $processed = 0;
            $worker = new Malamute\Producer(MalamuteTest::BROKER_ENDPOINT, "my_stream");
            $worker->run("mysubject", function() use(&$processed, $msg_count) {
                $processed++;
                $usec = rand(0, 1000);
                usleep($usec);
                return ($processed <= $msg_count) ? "mydata" : false;
            });
        });

        # Start a Stream Consumer
        $client = $manager->fork(function() use ($msg_count) {
            sleep(3);
            $processed = 0;
            $worker = new Malamute\Consumer(MalamuteTest::BROKER_ENDPOINT, "my_stream");
            $worker->run("mysubject", function($msg, $me) use(&$processed, $msg_count) {
                $processed++;
                return ($processed < $msg_count) ? true : false;
            });

            return ($msg_count == $processed) ? "OK" : "KO";
        });

        $broker = new Malamute\Broker(true);
        $broker->bind(self::BROKER_ENDPOINT);

        sleep(8);

        $client->receive();
        $result = $client->getResult();
        $manager->killAll();
        $this->assertEquals($result,"OK");
        $manager = null;

    }

//    public function test_queued_service()
//    {
//        $manager = new ProcessManager();
//
//        $w = $manager->fork(function() use ($endpoint) {
//            $done = false;
//            $worker = new Malamute\Worker($endpoint, "my_mailbox_worker");
//            $worker->run(function($req, $headers) use(&$done) {
//                $done = true;
//                return false;
//            });
//
//            return $done ? "OK" : "KO";
//        });
//
//        # Start Client (Send Work to MailBox)
//        $manager->fork(function() use ($endpoint) {
//            $service_client = new Malamute\Client($endpoint);
//            $service_client->connect();
//            $service_client->send_mailbox('my_mailbox_worker', json_encode(['gino' => 'pino' . $i]), 1000);
//        });
//
//        sleep(8);
//
//        $w->receive();
//        $result = $w->getResult();
//        $manager->killAll();
//        $this->assertEquals($result,"OK");
//        $manager = null;
//
//    }
//
//    public function test_pooled_service()
//    {
//        $manager = new ProcessManager();
//
//        # Start Service Workers
//        for($i = 0; $i < 5; $i++)
//            $forks[] = $manager->fork(function() use($i, $endpoint) {
//                $processed = 0;
//                $worker   = new Malamute\Worker($endpoint, "my_worker", "mywork*");
//                $worker->run(function($req, $me) use($i, &$processed) {
//                    $processed++;
//                    $usec = rand(0, 1000);
//                    usleep($usec);
//                    return "mydata";
//                });
//            });
//
//
//        # Start Clients (Send Work to Services)
//        for($i = 0; $i < 10; $i++)
//            $clients[] = $manager->fork(function() use($i, $endpoint) {
//                $service_client = new Malamute\Client($endpoint, 'client_' . $i);
//                $service_client->connect();
//                $service_client->send_service('my_worker', 'mywork', json_encode(['gino' => 'pino']), 30000);
//                $rcv = $service_client->recv();
//                return $rcv == "mydata" ? "OK" : "KO";
//            });
//
//        sleep(8);
//
//
//        $res = true;
//        foreach($clients as $client){
//            $client->receive();
//            $res = $res && ($client->getResult() == "OK");
//        }
//
//        $manager->killAll();
//
//        $this->assertTrue($res);
//
//    }

}