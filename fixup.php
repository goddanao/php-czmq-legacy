<?php


$file = __DIR__;
$file .= (file_exists($file . "/backup") ? "/vendor" : "");
$file .= "/czmq/src/zsock_option.c";

$src = file_get_contents($file);
$src = preg_replace('/(void[\s\r\n]+(zsock_set_ipv6|zsock_set_zap_domain).*?{).*?}/sim', "\$1\r\n}", $src);
unlink($file);
file_put_contents($file, $src);

