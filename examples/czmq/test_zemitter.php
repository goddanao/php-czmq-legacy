<?php

$emitter = new ZEmitter();

$cb1 = function($params) {
    echo "here: $params[0], $params[1], $params[2]\n";
};

$cb2 = function($params) {
    echo "there: $params[0], $params[1], $params[2]\n";
};

$cbonce = function($params) {
    echo "once: $params[0], $params[1], $params[2]\n";
};



// $emitter->on("message", $cb1);

// $emitter->on("message", $cb2);

$emitter->once("message", $cbonce);
print_r($emitter->listeners("message"));

$emitter->emit("message", ["param1", "param2", "param3"]);

print_r($emitter->listeners("message"));

$emitter->emit("message", ["param1", "param2", "param3"]);


//$emitter->removeListener("message", $cb1);
//
//print_r($emitter->listeners("message"));
//
//$emitter->emit("message", ["param1", "param2", "param3"]);
//
//$emitter->removeListener("message", $cb2);
//
//$emitter->emit("message", ["param1", "param2", "param3"]);
//
//print_r($emitter->listeners("message"));