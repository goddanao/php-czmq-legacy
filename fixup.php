<?php


$file = __DIR__;
$file .= (file_exists($file . "/backup") ? "/vendor" : "");
$file .= "/czmq/src/zsock_option.c";

$src = file_get_contents($file);
$src = preg_replace('/(void[\s\r\n]+zsock_set_ipv6.*?)(?:#.*?(?:assert \(rc).*?;.*?})/sim', '\1}', $src);
unlink($file);
file_put_contents($file, $src);

