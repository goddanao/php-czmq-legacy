<?php


$file = __DIR__;
$file .= (file_exists($file . "/backup") ? "/vendor" : "");
$file .= "/czmq/src/zsock_option.c";

$src = file_get_contents($file);
$src = preg_replace('/(void[\s\r\n]+(zsock_set_ipv6|zsock_set_zap_domain).*?{.*?assert.*?)(assert.*?})/sim', "\$1int errnum = zmq_errno(); int major, minor, patch; int cmajor, cminor, cpatch; zsys_version (&cmajor, &cminor, &cpatch); zmq_version (&major, &minor, &patch); zsys_info(\"\$2 (%s -> %s) -zmq=%d.%d.%d -czmq=%d.%d.%d -rc=%d -zmq_errno=%d -zmq_errmsg=%s\", zsys_sockname(zsock_type(self)), zsock_last_endpoint(self), major, minor, patch, cmajor, cminor, cpatch, rc, errnum, zmq_strerror(errnum));\r\n    // \$3", $src);
unlink($file);
file_put_contents($file, $src);
