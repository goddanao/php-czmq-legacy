ZSys
===============

ZSys

ZSys is static class holding zeromq system level methods / consts.


* Class name: ZSys
* Namespace: 



Constants
----------


### ENCODER_MSGPACK

    const ENCODER_MSGPACK = "msgpack"





### ENCODER_BSON

    const ENCODER_BSON = "bson"





### ENCODER_ZMQ

    const ENCODER_ZMQ = "zmq"





### ENCODER_DEFAULT

    const ENCODER_DEFAULT = "zmq"





### SOCKET_PUB

    const SOCKET_PUB = "pub"





### SOCKET_SUB

    const SOCKET_SUB = "sub"





### SOCKET_REP

    const SOCKET_REP = "rep"





### SOCKET_REQ

    const SOCKET_REQ = "req"





### SOCKET_DEALER

    const SOCKET_DEALER = "dealer"





### SOCKET_ROUTER

    const SOCKET_ROUTER = "router"





### SOCKET_PUSH

    const SOCKET_PUSH = "push"





### SOCKET_PULL

    const SOCKET_PULL = "pull"





### SOCKET_XPUB

    const SOCKET_XPUB = "xpub"





### SOCKET_XSUB

    const SOCKET_XSUB = "xsub"





### SOCKET_XREP

    const SOCKET_XREP = "xrep"





### SOCKET_XREQ

    const SOCKET_XREQ = "xreq"





### SOCKET_PAIR

    const SOCKET_PAIR = "pair"





### SOCKET_STREAM

    const SOCKET_STREAM = "stream"





### SOCKET_SERVER

    const SOCKET_SERVER = "server"





### SOCKET_CLIENT

    const SOCKET_CLIENT = "client"





### EVENT_CLOSED

    const EVENT_CLOSED = 128





### EVENT_CONNECTED

    const EVENT_CONNECTED = 1





### EVENT_CONNECT_DELAYED

    const EVENT_CONNECT_DELAYED = 2





### EVENT_CONNECT_RETRIED

    const EVENT_CONNECT_RETRIED = 4





### EVENT_LISTENING

    const EVENT_LISTENING = 8





### EVENT_BIND_FAILED

    const EVENT_BIND_FAILED = 16





### EVENT_ACCEPTED

    const EVENT_ACCEPTED = 32





### EVENT_ACCEPT_FAILED

    const EVENT_ACCEPT_FAILED = 64





### EVENT_CLOSE_FAILED

    const EVENT_CLOSE_FAILED = 256





### EVENT_DISCONNECTED

    const EVENT_DISCONNECTED = 512





### EVENT_MONITOR_STOPPED

    const EVENT_MONITOR_STOPPED = 1024





### EVENT_ALL

    const EVENT_ALL = 65535





### POLL_WAIT_FOREVER

    const POLL_WAIT_FOREVER = -1





### POLL_NONE

    const POLL_NONE = 0





### POLL_IN

    const POLL_IN = 1





### POLL_OUT

    const POLL_OUT = 2





### POLL_ERR

    const POLL_ERR = 4





### POLL_PRI

    const POLL_PRI = 8







Methods
-------


### set_default_encoder

    mixed ZSys::set_default_encoder(mixed $type, callable $callback)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $type **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_default_decoder

    mixed ZSys::set_default_decoder(mixed $type, callable $callback)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $type **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_io_threads

    mixed ZSys::set_io_threads(integer $threads)

Configure the number of I/O threads that ZeroMQ will use. A good
rule of thumb is one thread per gigabit of traffic in or out. The
default is 1, sufficient for most applications. If the environment
variable ZSYS_IO_THREADS is defined, that provides the default.

Note that this method is valid only before any socket is created.

* Visibility: **public**
* This method is **static**.


#### Arguments
* $threads **integer**



### set_ipv6

    mixed ZSys::set_ipv6(boolean $enable)

Configure use of IPv6 for new zsock instances. By default sockets accept
and make only IPv4 connections. When you enable IPv6, sockets will accept
and connect to both IPv4 and IPv6 peers. You can override the setting on
each zsock_t instance. The default is IPv4 only (ipv6 set to 0). If the
environment variable ZSYS_IPV6 is defined (as 1 or 0), this provides the
default. Note: has no effect on ZMQ v2.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $enable **boolean**



### set_default_linger

    mixed ZSys::set_default_linger(integer $linger)

Configure the default linger timeout in msecs for new zsock instances.

You can also set this separately on each zsock_t instance. The default
linger time is zero, i.e. any pending messages will be dropped. If the
environment variable ZSYS_LINGER is defined, that provides the default.
Note that process exit will typically be delayed by the linger time.

* Visibility: **public**
* This method is **static**.


#### Arguments
* $linger **integer**



### set_default_sndhwm

    mixed ZSys::set_default_sndhwm(integer $sndhwm)

Configure the default outgoing pipe limit (HWM) for new zsock instances.

You can also set this separately on each zsock_t instance. The default
HWM is 1,000, on all versions of ZeroMQ. If the environment variable
ZSYS_SNDHWM is defined, that provides the default. Note that a value of
zero means no limit, i.e. infinite memory consumption.

* Visibility: **public**
* This method is **static**.


#### Arguments
* $sndhwm **integer**



### set_default_rcvhwm

    mixed ZSys::set_default_rcvhwm(integer $rcvhwm)

Configure the default incoming pipe limit (HWM) for new zsock instances.

You can also set this separately on each zsock_t instance. The default
HWM is 1,000, on all versions of ZeroMQ. If the environment variable
ZSYS_RCVHWM is defined, that provides the default. Note that a value of
zero means no limit, i.e. infinite memory consumption.

* Visibility: **public**
* This method is **static**.


#### Arguments
* $rcvhwm **integer**



### set_pipehwm

    mixed ZSys::set_pipehwm(integer $pipehwm)

Configure the default HWM for zactor internal pipes; this is set on both
ends of the pipe, for outgoing messages only (sndhwm). The default HWM is
1,000, on all versions of ZeroMQ. If the environment var ZSYS_ACTORHWM is
defined, that provides the default. Note that a value of zero means no
limit, i.e. infinite memory consumption.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $pipehwm **integer**



### get_pipehwm

    integer ZSys::get_pipehwm()

Return the HWM for zactor internal pipes.



* Visibility: **public**
* This method is **static**.




### has_curve

    boolean ZSys::has_curve()

Returns true if the underlying libzmq supports CURVE security.



* Visibility: **public**
* This method is **static**.




### get_socket_limit

    integer ZSys::get_socket_limit()

Return maximum number of ZeroMQ sockets that the system will support.



* Visibility: **public**
* This method is **static**.




### set_max_sockets

    mixed ZSys::set_max_sockets(integer $max_sockets)

Configure the number of sockets that ZeroMQ will allow. The default
is 1024. The actual limit depends on the system, and you can query it
by using get_socket_limit (). A value of zero means 'maximum'.

Note that this method is valid only before any socket is created.

* Visibility: **public**
* This method is **static**.


#### Arguments
* $max_sockets **integer**



### hostname

    string ZSys::hostname()

Return current host name, for use in public tcp:// endpoints.



* Visibility: **public**
* This method is **static**.




### set_interface

    mixed ZSys::set_interface(string $interface)

Set network interface name to use for broadcasts, particularly zbeacon.

This lets the interface be configured for test environments where required.
For example, on Mac OS X, zbeacon cannot bind to 255.255.255.255 which is
the default when there is no specified interface. If the environment
variable ZSYS_INTERFACE is set, use that as the default interface name.
Setting the interface to '*' means 'use all available interfaces'.

* Visibility: **public**
* This method is **static**.


#### Arguments
* $interface **string**



### get_interface

    string ZSys::get_interface()

Return network interface to use for broadcasts, or '' if none was set.



* Visibility: **public**
* This method is **static**.




### list_interfaces

    array ZSys::list_interfaces()

Return network interfaces



* Visibility: **public**
* This method is **static**.




### get_available_socket_type

    array ZSys::get_available_socket_type()

Return an array of supported socket types (depends on zmq version installed).



* Visibility: **public**
* This method is **static**.




### set_log_ident

    mixed ZSys::set_log_ident(string $log_ident)

Set log identity, which is a string that prefixes all log messages sent
by this process. The log identity defaults to the environment variable
ZSYS_LOGIDENT, if that is set.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $log_ident **string**



### set_log_endpoint

    mixed ZSys::set_log_endpoint(string $log_endpoint)

Sends log output to a PUB socket bound to the specified endpoint. To
collect such log output, create a SUB socket, subscribe to the traffic
you care about, and connect to the endpoint. Log traffic is sent as a
single string frame, in the same format as when sent to stdout. The
log system supports a single sender; multiple calls to this method will
bind the same sender to multiple endpoints. To disable the sender, call
this method with a null argument.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $log_endpoint **string**



### set_log_system

    mixed ZSys::set_log_system(boolean $enable)

Enable or disable logging to the system facility (syslog on POSIX boxes,
event log on Windows). By default this is enabled.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $enable **boolean**



### libzmq_version

    string ZSys::libzmq_version()

Return ZMQ version



* Visibility: **public**
* This method is **static**.




### libczmq_version

    string ZSys::libczmq_version()

Return CZMQ version



* Visibility: **public**
* This method is **static**.




### libzyre_version

    string ZSys::libzyre_version()

Return Zyre version



* Visibility: **public**
* This method is **static**.




### libmdp_version

    string ZSys::libmdp_version()

Return Majordomo Protocol version



* Visibility: **public**
* This method is **static**.




### libfmq_version

    string ZSys::libfmq_version()

Return FileMq version



* Visibility: **public**
* This method is **static**.




### libmsgpack_version

    string ZSys::libmsgpack_version()

Return MsgPack version



* Visibility: **public**
* This method is **static**.




### libbson_version

    mixed ZSys::libbson_version()



...

* Visibility: **public**
* This method is **static**.




### libmlm_version

    string ZSys::libmlm_version()

Return Malamute version



* Visibility: **public**
* This method is **static**.




### uuid

    string ZSys::uuid()

Generate an UUID and return as 32 bytes string.



* Visibility: **public**
* This method is **static**.




### info

    mixed ZSys::info(string $message)

Log message as Info



* Visibility: **public**
* This method is **static**.


#### Arguments
* $message **string**



### debug

    mixed ZSys::debug(string $message)

Log message as Debug



* Visibility: **public**
* This method is **static**.


#### Arguments
* $message **string**



### warning

    mixed ZSys::warning(string $message)

Log message as Warning



* Visibility: **public**
* This method is **static**.


#### Arguments
* $message **string**



### error

    mixed ZSys::error(string $message)

Log message as Error



* Visibility: **public**
* This method is **static**.


#### Arguments
* $message **string**



### get_ipv6

    boolean ZSys::get_ipv6()

Check if IPV6 is active by default on newly created sockets.



* Visibility: **public**
* This method is **static**.




### get_ipv6_address

    string ZSys::get_ipv6_address()

Return IPv6 address to use for zbeacon reception, or '' if none was set.



* Visibility: **public**
* This method is **static**.




### set_ipv6_address

    mixed ZSys::set_ipv6_address(string $address)

Set IPv6 address to use zbeacon socket, particularly for receiving zbeacon.

This needs to be set IPv6 is enabled as IPv6 can have multiple addresses
on a given interface. If the environment variable ZSYS_IPV6_ADDRESS is set,
use that as the default IPv6 address.

* Visibility: **public**
* This method is **static**.


#### Arguments
* $address **string** - &lt;p&gt;IPV6 address&lt;/p&gt;



### get_ipv6_mcast_address

    string ZSys::get_ipv6_mcast_address()

Return IPv6 multicast address to use for sending zbeacon, or '' if none was set



* Visibility: **public**
* This method is **static**.




### set_ipv6_mcast_address

    mixed ZSys::set_ipv6_mcast_address(string $address)

Set IPv6 milticast address to use for sending zbeacon messages. This needs
to be set if IPv6 is enabled. If the environment variable
ZSYS_IPV6_MCAST_ADDRESS is set, use that as the default IPv6 multicast
address.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $address **string** - &lt;p&gt;IPv6 milticast address&lt;/p&gt;


