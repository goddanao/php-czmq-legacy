ZSocket
===============

ZSocket

...


* Class name: ZSocket
* Namespace: 
* This class implements: [IZSocket](IZSocket.md)






Methods
-------


### \ZSocket::__construct()

```
mixed ZSocket::\ZSocket::__construct()(mixed $socket_type, mixed $endpoint)
```

ZSocket::__construct

...

* Visibility: **public**

#### Arguments

* $socket_type **mixed** - &lt;p&gt;...&lt;/p&gt;
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### \ZSocket::set_verbose()

```
mixed ZSocket::\ZSocket::set_verbose()()
```

ZSocket::set_verbose

...

* Visibility: **public**



### \ZSocket::set_unbounded()

```
mixed ZSocket::\ZSocket::set_unbounded()()
```

ZSocket::set_unbounded

...

* Visibility: **public**



### \ZSocket::bind()

```
mixed ZSocket::\ZSocket::bind()(string $endpoint)
```

ZSocket::bind

Bind a socket to a formatted endpoint. For tcp:// endpoints, supports
ephemeral ports, if you specify the port number as '*'. By default
zsock uses the IANA designated range from C000 (49152) to FFFF (65535).
To override this range, follow the '*' with '[first-last]'. Either or
both first and last may be empty. To bind to a random port within the
range, use '!' in place of '*'.

Examples:
    tcp://127.0.0.1:*           bind to first free port from C000 up
    tcp://127.0.0.1:!           bind to random port from C000 to FFFF
    tcp://127.0.0.1:*[60000-]   bind to first free port from 60000 up
    tcp://127.0.0.1:![-60000]   bind to random port from C000 to 60000
    tcp://127.0.0.1:![55000-55999]
                                bind to random port from 55000 to 55999

* Visibility: **public**

#### Arguments

* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### \ZSocket::unbind()

```
mixed ZSocket::\ZSocket::unbind()(mixed $endpoint)
```

ZSocket::unbind

...

* Visibility: **public**

#### Arguments

* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### \ZSocket::connect()

```
mixed ZSocket::\ZSocket::connect()(mixed $endpoint)
```

ZSocket::connect

...

* Visibility: **public**

#### Arguments

* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### \ZSocket::disconnect()

```
mixed ZSocket::\ZSocket::disconnect()(mixed $endpoint)
```

ZSocket::disconnect

...

* Visibility: **public**

#### Arguments

* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### \ZSocket::attach()

```
mixed ZSocket::\ZSocket::attach()(mixed $endpoints, mixed $serverish)
```

ZSocket::attach

...

* Visibility: **public**

#### Arguments

* $endpoints **mixed** - &lt;p&gt;...&lt;/p&gt;
* $serverish **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### \ZSocket::signal()

```
mixed ZSocket::\ZSocket::signal()(mixed $byte)
```

ZSocket::signal

...

* Visibility: **public**

#### Arguments

* $byte **mixed** - &lt;p&gt;...&lt;/p&gt;



### \ZSocket::wait()

```
mixed ZSocket::\ZSocket::wait()()
```

ZSocket::wait

...

* Visibility: **public**



### \ZSocket::flush()

```
mixed ZSocket::\ZSocket::flush()()
```

ZSocket::flush

...

* Visibility: **public**



### \ZSocket::send_picture()

```
mixed ZSocket::\ZSocket::send_picture()(mixed $picture)
```

ZSocket::send_picture

...

* Visibility: **public**

#### Arguments

* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### \ZSocket::recv_picture()

```
mixed ZSocket::\ZSocket::recv_picture()(mixed $picture)
```

ZSocket::recv_picture

...

* Visibility: **public**

#### Arguments

* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### \ZSocket::send_string()

```
mixed ZSocket::\ZSocket::send_string()(mixed $value)
```

ZSocket::send_string

...

* Visibility: **public**

#### Arguments

* $value **mixed** - &lt;p&gt;...&lt;/p&gt;



### \ZSocket::recv_string()

```
mixed ZSocket::\ZSocket::recv_string()()
```

ZSocket::recv_string

...

* Visibility: **public**



### \ZSocket::send()

```
mixed ZSocket::\ZSocket::send()(mixed $zmsg)
```

ZSocket::send

...

* Visibility: **public**

#### Arguments

* $zmsg **mixed** - &lt;p&gt;...&lt;/p&gt;



### \ZSocket::recv()

```
mixed ZSocket::\ZSocket::recv()()
```

ZSocket::recv

...

* Visibility: **public**



### \ZSocket::pub()

```
mixed ZSocket::\ZSocket::pub()()
```

ZSocket::pub

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::sub()

```
mixed ZSocket::\ZSocket::sub()()
```

ZSocket::sub

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::rep()

```
mixed ZSocket::\ZSocket::rep()()
```

ZSocket::rep

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::req()

```
mixed ZSocket::\ZSocket::req()()
```

ZSocket::req

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::dealer()

```
mixed ZSocket::\ZSocket::dealer()()
```

ZSocket::dealer

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::router()

```
mixed ZSocket::\ZSocket::router()()
```

ZSocket::router

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::push()

```
mixed ZSocket::\ZSocket::push()()
```

ZSocket::push

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::pull()

```
mixed ZSocket::\ZSocket::pull()()
```

ZSocket::pull

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::xpub()

```
mixed ZSocket::\ZSocket::xpub()()
```

ZSocket::xpub

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::xsub()

```
mixed ZSocket::\ZSocket::xsub()()
```

ZSocket::xsub

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::xreq()

```
mixed ZSocket::\ZSocket::xreq()()
```

ZSocket::xreq

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::xrep()

```
mixed ZSocket::\ZSocket::xrep()()
```

ZSocket::xrep

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::stream()

```
mixed ZSocket::\ZSocket::stream()()
```

ZSocket::stream

...

* Visibility: **public**
* This method is **static**.



### \ZSocket::get_options()

```
mixed ZSocket::\ZSocket::get_options()()
```

ZSocket::get_options

...

* Visibility: **public**



### \ZSocket::get_tos()

```
mixed ZSocket::\ZSocket::get_tos()()
```

ZSocket::get_tos

...

* Visibility: **public**



### \ZSocket::get_zap_domain()

```
mixed ZSocket::\ZSocket::get_zap_domain()()
```

ZSocket::get_zap_domain

...

* Visibility: **public**



### \ZSocket::get_mechanism()

```
mixed ZSocket::\ZSocket::get_mechanism()()
```

ZSocket::get_mechanism

...

* Visibility: **public**



### \ZSocket::get_plain_server()

```
mixed ZSocket::\ZSocket::get_plain_server()()
```

ZSocket::get_plain_server

...

* Visibility: **public**



### \ZSocket::get_plain_username()

```
mixed ZSocket::\ZSocket::get_plain_username()()
```

ZSocket::get_plain_username

...

* Visibility: **public**



### \ZSocket::get_plain_password()

```
mixed ZSocket::\ZSocket::get_plain_password()()
```

ZSocket::get_plain_password

...

* Visibility: **public**



### \ZSocket::get_curve_server()

```
mixed ZSocket::\ZSocket::get_curve_server()()
```

ZSocket::get_curve_server

...

* Visibility: **public**



### \ZSocket::get_curve_publickey()

```
mixed ZSocket::\ZSocket::get_curve_publickey()()
```

ZSocket::get_curve_publickey

...

* Visibility: **public**



### \ZSocket::get_curve_secretkey()

```
mixed ZSocket::\ZSocket::get_curve_secretkey()()
```

ZSocket::get_curve_secretkey

...

* Visibility: **public**



### \ZSocket::get_curve_serverkey()

```
mixed ZSocket::\ZSocket::get_curve_serverkey()()
```

ZSocket::get_curve_serverkey

...

* Visibility: **public**



### \ZSocket::get_gssapi_server()

```
mixed ZSocket::\ZSocket::get_gssapi_server()()
```

ZSocket::get_gssapi_server

...

* Visibility: **public**



### \ZSocket::get_gssapi_plaintext()

```
mixed ZSocket::\ZSocket::get_gssapi_plaintext()()
```

ZSocket::get_gssapi_plaintext

...

* Visibility: **public**



### \ZSocket::get_gssapi_principal()

```
mixed ZSocket::\ZSocket::get_gssapi_principal()()
```

ZSocket::get_gssapi_principal

...

* Visibility: **public**



### \ZSocket::get_gssapi_service_principal()

```
mixed ZSocket::\ZSocket::get_gssapi_service_principal()()
```

ZSocket::get_gssapi_service_principal

...

* Visibility: **public**



### \ZSocket::get_ipv6()

```
mixed ZSocket::\ZSocket::get_ipv6()()
```

ZSocket::get_ipv6

...

* Visibility: **public**



### \ZSocket::get_immediate()

```
mixed ZSocket::\ZSocket::get_immediate()()
```

ZSocket::get_immediate

...

* Visibility: **public**



### \ZSocket::get_ipv4only()

```
mixed ZSocket::\ZSocket::get_ipv4only()()
```

ZSocket::get_ipv4only

...

* Visibility: **public**



### \ZSocket::get_type()

```
mixed ZSocket::\ZSocket::get_type()()
```

ZSocket::get_type

...

* Visibility: **public**



### \ZSocket::get_sndhwm()

```
mixed ZSocket::\ZSocket::get_sndhwm()()
```

ZSocket::get_sndhwm

...

* Visibility: **public**



### \ZSocket::get_rcvhwm()

```
mixed ZSocket::\ZSocket::get_rcvhwm()()
```

ZSocket::get_rcvhwm

...

* Visibility: **public**



### \ZSocket::get_affinity()

```
mixed ZSocket::\ZSocket::get_affinity()()
```

ZSocket::get_affinity

...

* Visibility: **public**



### \ZSocket::get_identity()

```
mixed ZSocket::\ZSocket::get_identity()()
```

ZSocket::get_identity

...

* Visibility: **public**



### \ZSocket::get_rate()

```
mixed ZSocket::\ZSocket::get_rate()()
```

ZSocket::get_rate

...

* Visibility: **public**



### \ZSocket::get_recovery_ivl()

```
mixed ZSocket::\ZSocket::get_recovery_ivl()()
```

ZSocket::get_recovery_ivl

...

* Visibility: **public**



### \ZSocket::get_sndbuf()

```
mixed ZSocket::\ZSocket::get_sndbuf()()
```

ZSocket::get_sndbuf

...

* Visibility: **public**



### \ZSocket::get_rcvbuf()

```
mixed ZSocket::\ZSocket::get_rcvbuf()()
```

ZSocket::get_rcvbuf

...

* Visibility: **public**



### \ZSocket::get_linger()

```
mixed ZSocket::\ZSocket::get_linger()()
```

ZSocket::get_linger

...

* Visibility: **public**



### \ZSocket::get_reconnect_ivl()

```
mixed ZSocket::\ZSocket::get_reconnect_ivl()()
```

ZSocket::get_reconnect_ivl

...

* Visibility: **public**



### \ZSocket::get_reconnect_ivl_max()

```
mixed ZSocket::\ZSocket::get_reconnect_ivl_max()()
```

ZSocket::get_reconnect_ivl_max

...

* Visibility: **public**



### \ZSocket::get_backlog()

```
mixed ZSocket::\ZSocket::get_backlog()()
```

ZSocket::get_backlog

...

* Visibility: **public**



### \ZSocket::get_maxmsgsize()

```
mixed ZSocket::\ZSocket::get_maxmsgsize()()
```

ZSocket::get_maxmsgsize

...

* Visibility: **public**



### \ZSocket::get_multicast_hops()

```
mixed ZSocket::\ZSocket::get_multicast_hops()()
```

ZSocket::get_multicast_hops

...

* Visibility: **public**



### \ZSocket::get_rcvtimeo()

```
mixed ZSocket::\ZSocket::get_rcvtimeo()()
```

ZSocket::get_rcvtimeo

...

* Visibility: **public**



### \ZSocket::get_sndtimeo()

```
mixed ZSocket::\ZSocket::get_sndtimeo()()
```

ZSocket::get_sndtimeo

...

* Visibility: **public**



### \ZSocket::get_tcp_keepalive()

```
mixed ZSocket::\ZSocket::get_tcp_keepalive()()
```

ZSocket::get_tcp_keepalive

...

* Visibility: **public**



### \ZSocket::get_tcp_keepalive_idle()

```
mixed ZSocket::\ZSocket::get_tcp_keepalive_idle()()
```

ZSocket::get_tcp_keepalive_idle

...

* Visibility: **public**



### \ZSocket::get_tcp_keepalive_cnt()

```
mixed ZSocket::\ZSocket::get_tcp_keepalive_cnt()()
```

ZSocket::get_tcp_keepalive_cnt

...

* Visibility: **public**



### \ZSocket::get_tcp_keepalive_intvl()

```
mixed ZSocket::\ZSocket::get_tcp_keepalive_intvl()()
```

ZSocket::get_tcp_keepalive_intvl

...

* Visibility: **public**



### \ZSocket::get_tcp_accept_filter()

```
mixed ZSocket::\ZSocket::get_tcp_accept_filter()()
```

ZSocket::get_tcp_accept_filter

...

* Visibility: **public**



### \ZSocket::get_rcvmore()

```
mixed ZSocket::\ZSocket::get_rcvmore()()
```

ZSocket::get_rcvmore

...

* Visibility: **public**



### \ZSocket::get_events()

```
mixed ZSocket::\ZSocket::get_events()()
```

ZSocket::get_events

...

* Visibility: **public**



### \ZSocket::get_last_endpoint()

```
mixed ZSocket::\ZSocket::get_last_endpoint()()
```

ZSocket::get_last_endpoint

...

* Visibility: **public**



### \ZSocket::set_tos()

```
mixed ZSocket::\ZSocket::set_tos()()
```

ZSocket::set_tos

...

* Visibility: **public**



### \ZSocket::set_router_handover()

```
mixed ZSocket::\ZSocket::set_router_handover()()
```

ZSocket::set_router_handover

...

* Visibility: **public**



### \ZSocket::set_router_mandatory()

```
mixed ZSocket::\ZSocket::set_router_mandatory()()
```

ZSocket::set_router_mandatory

...

* Visibility: **public**



### \ZSocket::set_probe_router()

```
mixed ZSocket::\ZSocket::set_probe_router()()
```

ZSocket::set_probe_router

...

* Visibility: **public**



### \ZSocket::set_req_relaxed()

```
mixed ZSocket::\ZSocket::set_req_relaxed()()
```

ZSocket::set_req_relaxed

...

* Visibility: **public**



### \ZSocket::set_req_correlate()

```
mixed ZSocket::\ZSocket::set_req_correlate()()
```

ZSocket::set_req_correlate

...

* Visibility: **public**



### \ZSocket::set_conflate()

```
mixed ZSocket::\ZSocket::set_conflate()()
```

ZSocket::set_conflate

...

* Visibility: **public**



### \ZSocket::set_zap_domain()

```
mixed ZSocket::\ZSocket::set_zap_domain()()
```

ZSocket::set_zap_domain

...

* Visibility: **public**



### \ZSocket::set_plain_server()

```
mixed ZSocket::\ZSocket::set_plain_server()()
```

ZSocket::set_plain_server

...

* Visibility: **public**



### \ZSocket::set_plain_username()

```
mixed ZSocket::\ZSocket::set_plain_username()()
```

ZSocket::set_plain_username

...

* Visibility: **public**



### \ZSocket::set_plain_password()

```
mixed ZSocket::\ZSocket::set_plain_password()()
```

ZSocket::set_plain_password

...

* Visibility: **public**



### \ZSocket::set_curve_server()

```
mixed ZSocket::\ZSocket::set_curve_server()()
```

ZSocket::set_curve_server

...

* Visibility: **public**



### \ZSocket::set_curve_publickey()

```
mixed ZSocket::\ZSocket::set_curve_publickey()()
```

ZSocket::set_curve_publickey

...

* Visibility: **public**



### \ZSocket::set_curve_publickey_bin()

```
mixed ZSocket::\ZSocket::set_curve_publickey_bin()()
```

ZSocket::set_curve_publickey_bin

...

* Visibility: **public**



### \ZSocket::set_curve_secretkey()

```
mixed ZSocket::\ZSocket::set_curve_secretkey()()
```

ZSocket::set_curve_secretkey

...

* Visibility: **public**



### \ZSocket::set_curve_secretkey_bin()

```
mixed ZSocket::\ZSocket::set_curve_secretkey_bin()()
```

ZSocket::set_curve_secretkey_bin

...

* Visibility: **public**



### \ZSocket::set_curve_serverkey()

```
mixed ZSocket::\ZSocket::set_curve_serverkey()()
```

ZSocket::set_curve_serverkey

...

* Visibility: **public**



### \ZSocket::set_curve_serverkey_bin()

```
mixed ZSocket::\ZSocket::set_curve_serverkey_bin()()
```

ZSocket::set_curve_serverkey_bin

...

* Visibility: **public**



### \ZSocket::set_gssapi_server()

```
mixed ZSocket::\ZSocket::set_gssapi_server()()
```

ZSocket::set_gssapi_server

...

* Visibility: **public**



### \ZSocket::set_gssapi_plaintext()

```
mixed ZSocket::\ZSocket::set_gssapi_plaintext()()
```

ZSocket::set_gssapi_plaintext

...

* Visibility: **public**



### \ZSocket::set_gssapi_principal()

```
mixed ZSocket::\ZSocket::set_gssapi_principal()()
```

ZSocket::set_gssapi_principal

...

* Visibility: **public**



### \ZSocket::set_gssapi_service_principal()

```
mixed ZSocket::\ZSocket::set_gssapi_service_principal()()
```

ZSocket::set_gssapi_service_principal

...

* Visibility: **public**



### \ZSocket::set_ipv6()

```
mixed ZSocket::\ZSocket::set_ipv6()()
```

ZSocket::set_ipv6

...

* Visibility: **public**



### \ZSocket::set_immediate()

```
mixed ZSocket::\ZSocket::set_immediate()()
```

ZSocket::set_immediate

...

* Visibility: **public**



### \ZSocket::set_router_raw()

```
mixed ZSocket::\ZSocket::set_router_raw()()
```

ZSocket::set_router_raw

...

* Visibility: **public**



### \ZSocket::set_ipv4only()

```
mixed ZSocket::\ZSocket::set_ipv4only()()
```

ZSocket::set_ipv4only

...

* Visibility: **public**



### \ZSocket::set_delay_attach_on_connect()

```
mixed ZSocket::\ZSocket::set_delay_attach_on_connect()()
```

ZSocket::set_delay_attach_on_connect

...

* Visibility: **public**



### \ZSocket::set_sndhwm()

```
mixed ZSocket::\ZSocket::set_sndhwm()()
```

ZSocket::set_sndhwm

...

* Visibility: **public**



### \ZSocket::set_rcvhwm()

```
mixed ZSocket::\ZSocket::set_rcvhwm()()
```

ZSocket::set_rcvhwm

...

* Visibility: **public**



### \ZSocket::set_affinity()

```
mixed ZSocket::\ZSocket::set_affinity()()
```

ZSocket::set_affinity

...

* Visibility: **public**



### \ZSocket::set_subscribe()

```
mixed ZSocket::\ZSocket::set_subscribe()()
```

ZSocket::set_subscribe

...

* Visibility: **public**



### \ZSocket::set_unsubscribe()

```
mixed ZSocket::\ZSocket::set_unsubscribe()()
```

ZSocket::set_unsubscribe

...

* Visibility: **public**



### \ZSocket::set_identity()

```
mixed ZSocket::\ZSocket::set_identity()()
```

ZSocket::set_identity

...

* Visibility: **public**



### \ZSocket::set_rate()

```
mixed ZSocket::\ZSocket::set_rate()()
```

ZSocket::set_rate

...

* Visibility: **public**



### \ZSocket::set_recovery_ivl()

```
mixed ZSocket::\ZSocket::set_recovery_ivl()()
```

ZSocket::set_recovery_ivl

...

* Visibility: **public**



### \ZSocket::set_sndbuf()

```
mixed ZSocket::\ZSocket::set_sndbuf()()
```

ZSocket::set_sndbuf

...

* Visibility: **public**



### \ZSocket::set_rcvbuf()

```
mixed ZSocket::\ZSocket::set_rcvbuf()()
```

ZSocket::set_rcvbuf

...

* Visibility: **public**



### \ZSocket::set_linger()

```
mixed ZSocket::\ZSocket::set_linger()()
```

ZSocket::set_linger

...

* Visibility: **public**



### \ZSocket::set_reconnect_ivl()

```
mixed ZSocket::\ZSocket::set_reconnect_ivl()()
```

ZSocket::set_reconnect_ivl

...

* Visibility: **public**



### \ZSocket::set_reconnect_ivl_max()

```
mixed ZSocket::\ZSocket::set_reconnect_ivl_max()()
```

ZSocket::set_reconnect_ivl_max

...

* Visibility: **public**



### \ZSocket::set_backlog()

```
mixed ZSocket::\ZSocket::set_backlog()()
```

ZSocket::set_backlog

...

* Visibility: **public**



### \ZSocket::set_maxmsgsize()

```
mixed ZSocket::\ZSocket::set_maxmsgsize()()
```

ZSocket::set_maxmsgsize

...

* Visibility: **public**



### \ZSocket::set_multicast_hops()

```
mixed ZSocket::\ZSocket::set_multicast_hops()()
```

ZSocket::set_multicast_hops

...

* Visibility: **public**



### \ZSocket::set_rcvtimeo()

```
mixed ZSocket::\ZSocket::set_rcvtimeo()()
```

ZSocket::set_rcvtimeo

...

* Visibility: **public**



### \ZSocket::set_sndtimeo()

```
mixed ZSocket::\ZSocket::set_sndtimeo()()
```

ZSocket::set_sndtimeo

...

* Visibility: **public**



### \ZSocket::set_xpub_verbose()

```
mixed ZSocket::\ZSocket::set_xpub_verbose()()
```

ZSocket::set_xpub_verbose

...

* Visibility: **public**



### \ZSocket::set_tcp_keepalive()

```
mixed ZSocket::\ZSocket::set_tcp_keepalive()()
```

ZSocket::set_tcp_keepalive

...

* Visibility: **public**



### \ZSocket::set_tcp_keepalive_idle()

```
mixed ZSocket::\ZSocket::set_tcp_keepalive_idle()()
```

ZSocket::set_tcp_keepalive_idle

...

* Visibility: **public**



### \ZSocket::set_tcp_keepalive_cnt()

```
mixed ZSocket::\ZSocket::set_tcp_keepalive_cnt()()
```

ZSocket::set_tcp_keepalive_cnt

...

* Visibility: **public**



### \ZSocket::set_tcp_keepalive_intvl()

```
mixed ZSocket::\ZSocket::set_tcp_keepalive_intvl()()
```

ZSocket::set_tcp_keepalive_intvl

...

* Visibility: **public**



### \ZSocket::set_tcp_accept_filter()

```
mixed ZSocket::\ZSocket::set_tcp_accept_filter()()
```

ZSocket::set_tcp_accept_filter

...

* Visibility: **public**


