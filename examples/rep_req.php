<?php

// Request / Reply

$rep = ZSocket::rep("tcp://127.0.0.1:8849");
$req = ZSocket::req("tcp://127.0.0.1:8849");
$req->send("hello!", "world!", 0, 1, true, 1.5, ['my' => 'world'], [1,2,3,4,5,6]);
$msg = $rep->recv();
$msg->dump();
$options  = $rep->get_options();
print_r($options);

// starting loop
$rep = ZSocket::rep("tcp://127.0.0.1:8850");
$req = ZSocket::req("tcp://127.0.0.1:8850");
$loop = new ZLoop();
$loop->add($rep, function($rep) use ($loop) {
    $msg = $rep->recv();
    // $msg->dump();
    $loop->stop();
});
$req->send("hello!");
$loop->start();