<?php

use Spork\Fork;
use Spork\ProcessManager;

class FileMqTest extends \PHPUnit_Framework_TestCase {

    public function test_filemq()
    {
        $ep = "tcp://127.0.0.1:8859";
        $server_path = realpath(__DIR__ . "/storage/remote");
        $client_path = realpath(__DIR__ . "/storage/local");

        $manager = new ProcessManager();
        # $manager->zombieOkay(true);

        # FileMQ Server
        $manager->fork(function() use ($ep, $server_path) {
            $server = new \FileMQ\Server();
            $server->load_config(__DIR__ . "/cfg/filemq.cfg");
            $server->bind($ep);
            $server->publish($server_path, "/");
            $loop = new ZLoop();
            $loop->start();
        });

        # FileMQ Client
        $manager->fork(function() use ($ep, $client_path) {
            $client = new \FileMq\Client($ep, $client_path, 1000);
            $client->subscribe("/");
            $loop = new ZLoop();
            $loop->start();
        });

        $timeout = 10;
        $filename = "test.dat";
        $found = false;

        if(file_exists($server_path . "/" . $filename))
            unlink($server_path . "/" . $filename);
        if(file_exists($client_path . "/" . $filename))
            unlink($client_path . "/" . $filename);

        file_put_contents($server_path . "/" . $filename, "mydata");

        while((--$timeout) && (!$found)) {
            sleep(1);
            $found = file_exists($client_path . "/" . $filename);
        }

        $manager->killAll();

        $this->assertTrue($found);

    }
}