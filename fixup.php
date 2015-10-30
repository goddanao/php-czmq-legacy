<?php


$file = __DIR__;
$file .= (file_exists($file . "/backup") ? "/vendor" : "");
$file .= "/czmq/src/zsock_option.c";

$src = file_get_contents($file);
$src = preg_replace('/(void[\s\r\n]+(zsock_set_ipv6|zsock_set_zap_domain).*?{.*?assert.*?)(assert.*?})/sim', "\$1int errnum = zmq_errno(); zsys_info(\"\$2 (%s -> %s) -rc=%d -zmq_errno=%d -zmq_errmsg=%s\", zsock_type_str(self), zsock_endpoint(self), rc, errnum, zmq_strerror(errnum));\r\n    // \$3", $src);
unlink($file);
file_put_contents($file, $src);
