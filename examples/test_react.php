<?php

require_once __DIR__ . "/../vendor/autoload.php";

require_once __DIR__ . "/react/Buffer.php";
require_once __DIR__ . "/react/SocketWrapper.php";

$endpoint = "ipc:///tmp/rep";
$rep = new ZSocket(ZSys::SOCKET_REP);
$rep->bind($endpoint);
$req = new ZSocket(ZSys::SOCKET_REQ);
$req->connect($endpoint);

$loop = React\EventLoop\Factory::create();

$wrep = new SocketWrapper($rep, $loop);
$wreq = new SocketWrapper($req, $loop);

$wrep->on('message', function($msg) use ($wrep) {
    echo "REP recieved $msg\n";
    $wrep->send("result - " . $msg);
});

$wreq->on('message', function($msg) use ($wreq) {
    echo "REQ recieved $msg\n";
});

$loop->addTimer(1, function() use($loop, $wreq) {
    $wreq->send('hello! 1');
    $wreq->send('hello! 2');
});
$loop->addTimer(2, function() use($loop, $wreq) {
    $wreq->send('hello! 3');
});
$loop->addTimer(3, function() use($loop, $wreq) {
    $wreq->send('hello! 4');
});

$loop->addTimer(5, function() use($loop) {
    $loop->stop();
});

$loop->run();