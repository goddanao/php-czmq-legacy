<?php

use Spork\Fork;
use Spork\ProcessManager;

class ZFileMqTest extends \PHPUnit_Framework_TestCase {

    public function test_filemq()
    {
        $ep = "tcp://127.0.0.1:8859";
        $server_path = realpath(__DIR__ . "/storage/remote");
        $client_path = realpath(__DIR__ . "/storage/local");

        # FileMQ Server
        $server = new \FileMQ\Server();
        $server->load_config(__DIR__ . "/cfg/filemq.cfg");
        $server->bind($ep);
        $server->publish($server_path, "/");

        # FileMQ Client
        $client = new \FileMq\Client($ep, $client_path, 1000);
        $client->subscribe("/");

        sleep(1);

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

        $this->assertTrue($found);

    }
}