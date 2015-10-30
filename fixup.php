<?php


$file = __DIR__;
$file .= (file_exists($file . "/backup") ? "/vendor" : "");
$file .= "/czmq/src/zsock_option.c";

$src = file_get_contents($file);
$src = preg_replace('/(void[\s\r\n]+(zsock_set_ipv6|zsock_set_zap_domain).*?{.*?assert.*?)(assert.*?})/sim', "\$1zsys_info(\"\$2 -rc=%d -zmq_errno=%d -zmq_errmsg=%s\", rc, zmq_errno(), zmq_strerror(zmq_errno()));\r\n    // \$3",, $src);
unlink($file);
file_put_contents($file, $src);

