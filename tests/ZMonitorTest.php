<?php

class ZMonitorTest extends \PHPUnit_Framework_TestCase
{

    public function test_monitor() {
        $ep   = "tcp://127.0.0.1:8899";
        $rep = new ZSocket(ZSys::SOCKET_REP);
        $req = new ZSocket(ZSys::SOCKET_REQ);
        $monitor = new ZMonitor($rep);
        $monitor->listen(ZMonitor::EVT_ALL);
        $monitor->start();

        $events = [];
        $loop = new ZLoop();
        $loop->add($monitor, function($me) use (&$events) {
            $msg = $me->recv();
            $events[] = $msg->pop_string();
        });
        $loop->add_timer(1, function() use ($rep, $req, $ep) {
            $rep->bind($ep);
            $req->connect($ep);

        });
        $loop->add_timer(100, function($timer_id, $loop) use ($req) {
            $loop->stop();
        });
        $loop->start();

        $this->assertEquals(["LISTENING", "ACCEPTED"], $events);
    }

}