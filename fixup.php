<?php


$file = __DIR__;
$file .= (file_exists($file . "/backup") ? "/vendor" : "");
$file .= "/czmq/src/zsock_option.c";

$src = file_get_contents($file);
$src = preg_replace('%(#include "../include/czmq.h")%sim', "\$1\r\n#undef ZMQ_IPV6\r\n#undef ZMQ_ZAP_DOMAIN\r\n", $src);
unlink($file);
file_put_contents($file, $src);

