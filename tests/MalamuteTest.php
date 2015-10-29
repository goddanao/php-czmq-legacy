<?php

class MalamuteTest extends \PHPUnit_Framework_TestCase {

    public function test_create() {
        $broker_endpoint = "ipc://@/malamute";

//        // Stream Producer
//        $pid = pcntl_fork();
//        if(!$pid) {
//            sleep(2);
//            $stream_producer = new Malamute\Client($broker_endpoint);
//            $stream_producer->connect();
//            $stream_producer->set_producer("mystream");
//            for($i = 0; $i < 10; $i++)
//                $stream_producer->send_stream('tv-listing', 'stocazzo' . $i);
//            exit;
//        }
//        // Stream Consumer
//        $pid = pcntl_fork();
//        if(!$pid) {
//            sleep(1);
//            $stream_consumer = new Malamute\Client($broker_endpoint);
//            $stream_consumer->connect();
//            $stream_consumer->set_consumer("mystream", "tv-listing.*");
//            while(true) {
//                $rcv = $stream_consumer->recv_string();
//                $headers = $stream_consumer->header();
//                ZSys::info("stream consumer - recieved: {$rcv} - " . json_encode($headers));
//            }
//            exit;
//        } else
//            $pids[] = $pid;

        // Worker
        $pid = pcntl_fork();
        if(!$pid) {
            sleep(1);
            $worker   = new Malamute\Client($broker_endpoint);
            $worker->connect();
            $worker->set_worker("myworker", "mywork.*");
            while(true) {
                $rcv = $worker->recv_string();
                $headers = $worker->header();
                ZSys::info("worker - recieved: {$rcv} - " . json_encode($headers));
            }
            exit;
        } else
            $pids[] = $pid;

//        // Worker Consumer
//        $pid = pcntl_fork();
//        if(!$pid) {
//            sleep(2);
//            $worker_consumer = new Malamute\Client($broker_endpoint);
//            $worker_consumer->connect();
//            $worker_consumer->set_consumer("myworker", "mywork.*");
//            for($i = 0; $i < 10; $i++)
//                $worker_consumer->send_service('myworker', 'mywork.stocazzo', null, 0, json_encode(['gino' => 'pino']));
//            exit;
//        }

        // Worker Consumer (Via Mailbox)
        $pid = pcntl_fork();
        if(!$pid) {
            sleep(2);
            $worker_consumer = new Malamute\Client($broker_endpoint);
            $worker_consumer->connect();
            $worker_consumer->set_consumer("myworker", "mywork.*");
            for($i = 0; $i < 10; $i++)
                $worker_consumer->send_mailbox('myworker', 'mywork.stocazzo', null, 0, json_encode(['gino' => 'pino']));
            exit;
        }

        $broker = new Malamute\Broker("mybroker");
        $broker->load_config(__DIR__ . "/cfg/malamute.cfg");
        $broker->run(5000);

        foreach($pids as $p) exec("kill $p");

    }
}