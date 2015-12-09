<?php

$loop = new ZLoop();

//$zyre1 = new Zyre();
//$zyre1->start();
//$zyre2 = new Zyre("node2");
//$zyre2->start();

$udp1 = new ZUdp();
$udp2 = new ZUdp();

$gossip1 = new ZGossip();
$port = $gossip1->bind("tcp://127.0.0.1:*");

$gossip2 = new ZGossip();
$gossip2->connect("tcp://127.0.0.1:{$port}");

$proxy = new ZProxy();
$proxy->set_frontend(ZSys::SOCKET_PULL, "ipc:///tmp/frontend");
$proxy->set_backend(ZSys::SOCKET_PUSH, "ipc:///tmp/backend");

$watcher = new Watcher();
$watcher->watch("/tmp/stoca", Watcher::IN_CREATE);

$loop->add(new ZStdIn(), function($me){
    $msg = $me->recv();
    echo "GOT '$msg' from stdin!\n";
});

$loop->add($watcher, function($me) {
    $msg = $me->recv();
    echo "WATCHER:\n";
    print_r($msg);
});

$loop->add($proxy, function($me) {
    $msg = $me->recv();
    echo "PROXY\n";
    $msg->dump();
});

$loop->add($gossip2, function($me) {
    $msg = $me->recv();
    echo "GOSSIP\n";
    $msg->dump();
});

$loop->add($udp2, function($me) {
    $msg = $me->recv();
    $sender = $msg->pop_string();
    $message = $msg->pop_string();
    echo "$sender -> $message\n";
});

$loop->add_timer(2000, function($timer_id, $loop) {
    $loop->stop();
});
//$loop->add($zyre1, function($me) {
//    $res = $me->recv();
////    echo "ZYRE1:\n";
////    print_r($res);
////    echo "\n";
//}, true);

//$loop->add($zyre2, function($me) {
//    $res = $me->recv();
////    echo "ZYRE2:\n";
////    print_r($res);
////    echo "\n";
//}, true);

//$zyre1->join("PUBLIC");
//$zyre2->join("PUBLIC");

$msg = new ZMsg();
$msg->append_string("hello");
$msg->append_string("world");
$udp1->send($msg);

$gossip1->publish("gossip-hello", "gossip-world");


$loop->start();
