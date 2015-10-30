<?php


$file = __DIR__;
$file .= (file_exists($file . "/backup") ? "/vendor" : "");
$file .= "/czmq/src/zsys.c";

$src = file_get_contents($file);
$src = preg_replace('/zsock_set_ipv6.*?;/sim', "zsys_info(\"ahahah beccato\");\r\nzsock_set_ipv4only (handle, 1);", $src);
unlink($file);
file_put_contents($file, $src);

