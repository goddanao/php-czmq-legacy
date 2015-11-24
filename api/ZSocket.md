ZSocket
===============

ZSocket

...


* Class name: ZSocket
* Namespace: 
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed ZSocket::__construct(mixed $socket_type, mixed $endpoint)



...

* Visibility: **public**


#### Arguments
* $socket_type **mixed** - &lt;p&gt;...&lt;/p&gt;
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed ZSocket::set_verbose()



...

* Visibility: **public**




### set_unbounded

    mixed ZSocket::set_unbounded()



...

* Visibility: **public**




### bind

    mixed ZSocket::bind(mixed $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### unbind

    mixed ZSocket::unbind(mixed $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### connect

    mixed ZSocket::connect(mixed $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### disconnect

    mixed ZSocket::disconnect(mixed $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### attach

    mixed ZSocket::attach(mixed $endpoints, mixed $serverish)



...

* Visibility: **public**


#### Arguments
* $endpoints **mixed** - &lt;p&gt;...&lt;/p&gt;
* $serverish **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### signal

    mixed ZSocket::signal(mixed $byte)



...

* Visibility: **public**


#### Arguments
* $byte **mixed** - &lt;p&gt;...&lt;/p&gt;



### wait

    mixed ZSocket::wait()



...

* Visibility: **public**




### flush

    mixed ZSocket::flush()



...

* Visibility: **public**




### get_socket_type

    mixed ZSocket::get_socket_type()



...

* Visibility: **public**




### send

    mixed ZSocket::send()



...

* Visibility: **public**




### recv

    mixed ZSocket::recv()



...

* Visibility: **public**




### send_string

    mixed ZSocket::send_string(mixed $value)



...

* Visibility: **public**


#### Arguments
* $value **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_string

    mixed ZSocket::recv_string()



...

* Visibility: **public**




### send_picture

    mixed ZSocket::send_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_picture

    mixed ZSocket::recv_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### pub

    mixed ZSocket::pub(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### sub

    mixed ZSocket::sub(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### rep

    mixed ZSocket::rep(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### req

    mixed ZSocket::req(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### dealer

    mixed ZSocket::dealer(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### router

    mixed ZSocket::router(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### push

    mixed ZSocket::push(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### pull

    mixed ZSocket::pull(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### xpub

    mixed ZSocket::xpub(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### xsub

    mixed ZSocket::xsub(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### xreq

    mixed ZSocket::xreq(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### xrep

    mixed ZSocket::xrep(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### stream

    mixed ZSocket::stream(mixed $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### get_options

    mixed ZSocket::get_options()



...

* Visibility: **public**




### get_fd

    mixed IZDescriptor::get_fd()



...

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    mixed IZSocket::get_socket()



...

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)




### get_tos

    mixed ZSocket::get_tos()



...

* Visibility: **public**




### get_zap_domain

    mixed ZSocket::get_zap_domain()



...

* Visibility: **public**




### get_mechanism

    mixed ZSocket::get_mechanism()



...

* Visibility: **public**




### get_plain_server

    mixed ZSocket::get_plain_server()



...

* Visibility: **public**




### get_plain_username

    mixed ZSocket::get_plain_username()



...

* Visibility: **public**




### get_plain_password

    mixed ZSocket::get_plain_password()



...

* Visibility: **public**




### get_curve_server

    mixed ZSocket::get_curve_server()



...

* Visibility: **public**




### get_curve_publickey

    mixed ZSocket::get_curve_publickey()



...

* Visibility: **public**




### get_curve_secretkey

    mixed ZSocket::get_curve_secretkey()



...

* Visibility: **public**




### get_curve_serverkey

    mixed ZSocket::get_curve_serverkey()



...

* Visibility: **public**




### get_gssapi_server

    mixed ZSocket::get_gssapi_server()



...

* Visibility: **public**




### get_gssapi_plaintext

    mixed ZSocket::get_gssapi_plaintext()



...

* Visibility: **public**




### get_gssapi_principal

    mixed ZSocket::get_gssapi_principal()



...

* Visibility: **public**




### get_gssapi_service_principal

    mixed ZSocket::get_gssapi_service_principal()



...

* Visibility: **public**




### get_ipv6

    mixed ZSocket::get_ipv6()



...

* Visibility: **public**




### get_immediate

    mixed ZSocket::get_immediate()



...

* Visibility: **public**




### get_ipv4only

    mixed ZSocket::get_ipv4only()



...

* Visibility: **public**




### get_type

    mixed ZSocket::get_type()



...

* Visibility: **public**




### get_sndhwm

    mixed ZSocket::get_sndhwm()



...

* Visibility: **public**




### get_rcvhwm

    mixed ZSocket::get_rcvhwm()



...

* Visibility: **public**




### get_affinity

    mixed ZSocket::get_affinity()



...

* Visibility: **public**




### get_identity

    mixed ZSocket::get_identity()



...

* Visibility: **public**




### get_rate

    mixed ZSocket::get_rate()



...

* Visibility: **public**




### get_recovery_ivl

    mixed ZSocket::get_recovery_ivl()



...

* Visibility: **public**




### get_sndbuf

    mixed ZSocket::get_sndbuf()



...

* Visibility: **public**




### get_rcvbuf

    mixed ZSocket::get_rcvbuf()



...

* Visibility: **public**




### get_linger

    mixed ZSocket::get_linger()



...

* Visibility: **public**




### get_reconnect_ivl

    mixed ZSocket::get_reconnect_ivl()



...

* Visibility: **public**




### get_reconnect_ivl_max

    mixed ZSocket::get_reconnect_ivl_max()



...

* Visibility: **public**




### get_backlog

    mixed ZSocket::get_backlog()



...

* Visibility: **public**




### get_maxmsgsize

    mixed ZSocket::get_maxmsgsize()



...

* Visibility: **public**




### get_multicast_hops

    mixed ZSocket::get_multicast_hops()



...

* Visibility: **public**




### get_rcvtimeo

    mixed ZSocket::get_rcvtimeo()



...

* Visibility: **public**




### get_sndtimeo

    mixed ZSocket::get_sndtimeo()



...

* Visibility: **public**




### get_tcp_keepalive

    mixed ZSocket::get_tcp_keepalive()



...

* Visibility: **public**




### get_tcp_keepalive_idle

    mixed ZSocket::get_tcp_keepalive_idle()



...

* Visibility: **public**




### get_tcp_keepalive_cnt

    mixed ZSocket::get_tcp_keepalive_cnt()



...

* Visibility: **public**




### get_tcp_keepalive_intvl

    mixed ZSocket::get_tcp_keepalive_intvl()



...

* Visibility: **public**




### get_tcp_accept_filter

    mixed ZSocket::get_tcp_accept_filter()



...

* Visibility: **public**




### get_rcvmore

    mixed ZSocket::get_rcvmore()



...

* Visibility: **public**




### get_events

    mixed ZSocket::get_events()



...

* Visibility: **public**




### get_last_endpoint

    mixed ZSocket::get_last_endpoint()



...

* Visibility: **public**




### set_tos

    mixed ZSocket::set_tos()



...

* Visibility: **public**




### set_router_handover

    mixed ZSocket::set_router_handover()



...

* Visibility: **public**




### set_router_mandatory

    mixed ZSocket::set_router_mandatory()



...

* Visibility: **public**




### set_probe_router

    mixed ZSocket::set_probe_router()



...

* Visibility: **public**




### set_req_relaxed

    mixed ZSocket::set_req_relaxed()



...

* Visibility: **public**




### set_req_correlate

    mixed ZSocket::set_req_correlate()



...

* Visibility: **public**




### set_conflate

    mixed ZSocket::set_conflate()



...

* Visibility: **public**




### set_zap_domain

    mixed ZSocket::set_zap_domain()



...

* Visibility: **public**




### set_plain_server

    mixed ZSocket::set_plain_server()



...

* Visibility: **public**




### set_plain_username

    mixed ZSocket::set_plain_username()



...

* Visibility: **public**




### set_plain_password

    mixed ZSocket::set_plain_password()



...

* Visibility: **public**




### set_curve_server

    mixed ZSocket::set_curve_server()



...

* Visibility: **public**




### set_curve_publickey

    mixed ZSocket::set_curve_publickey()



...

* Visibility: **public**




### set_curve_publickey_bin

    mixed ZSocket::set_curve_publickey_bin()



...

* Visibility: **public**




### set_curve_secretkey

    mixed ZSocket::set_curve_secretkey()



...

* Visibility: **public**




### set_curve_secretkey_bin

    mixed ZSocket::set_curve_secretkey_bin()



...

* Visibility: **public**




### set_curve_serverkey

    mixed ZSocket::set_curve_serverkey()



...

* Visibility: **public**




### set_curve_serverkey_bin

    mixed ZSocket::set_curve_serverkey_bin()



...

* Visibility: **public**




### set_gssapi_server

    mixed ZSocket::set_gssapi_server()



...

* Visibility: **public**




### set_gssapi_plaintext

    mixed ZSocket::set_gssapi_plaintext()



...

* Visibility: **public**




### set_gssapi_principal

    mixed ZSocket::set_gssapi_principal()



...

* Visibility: **public**




### set_gssapi_service_principal

    mixed ZSocket::set_gssapi_service_principal()



...

* Visibility: **public**




### set_ipv6

    mixed ZSocket::set_ipv6()



...

* Visibility: **public**




### set_immediate

    mixed ZSocket::set_immediate()



...

* Visibility: **public**




### set_router_raw

    mixed ZSocket::set_router_raw()



...

* Visibility: **public**




### set_ipv4only

    mixed ZSocket::set_ipv4only()



...

* Visibility: **public**




### set_delay_attach_on_connect

    mixed ZSocket::set_delay_attach_on_connect()



...

* Visibility: **public**




### set_sndhwm

    mixed ZSocket::set_sndhwm()



...

* Visibility: **public**




### set_rcvhwm

    mixed ZSocket::set_rcvhwm()



...

* Visibility: **public**




### set_affinity

    mixed ZSocket::set_affinity()



...

* Visibility: **public**




### set_subscribe

    mixed ZSocket::set_subscribe()



...

* Visibility: **public**




### set_unsubscribe

    mixed ZSocket::set_unsubscribe()



...

* Visibility: **public**




### set_identity

    mixed ZSocket::set_identity()



...

* Visibility: **public**




### set_rate

    mixed ZSocket::set_rate()



...

* Visibility: **public**




### set_recovery_ivl

    mixed ZSocket::set_recovery_ivl()



...

* Visibility: **public**




### set_sndbuf

    mixed ZSocket::set_sndbuf()



...

* Visibility: **public**




### set_rcvbuf

    mixed ZSocket::set_rcvbuf()



...

* Visibility: **public**




### set_linger

    mixed ZSocket::set_linger()



...

* Visibility: **public**




### set_reconnect_ivl

    mixed ZSocket::set_reconnect_ivl()



...

* Visibility: **public**




### set_reconnect_ivl_max

    mixed ZSocket::set_reconnect_ivl_max()



...

* Visibility: **public**




### set_backlog

    mixed ZSocket::set_backlog()



...

* Visibility: **public**




### set_maxmsgsize

    mixed ZSocket::set_maxmsgsize()



...

* Visibility: **public**




### set_multicast_hops

    mixed ZSocket::set_multicast_hops()



...

* Visibility: **public**




### set_rcvtimeo

    mixed ZSocket::set_rcvtimeo()



...

* Visibility: **public**




### set_sndtimeo

    mixed ZSocket::set_sndtimeo()



...

* Visibility: **public**




### set_xpub_verbose

    mixed ZSocket::set_xpub_verbose()



...

* Visibility: **public**




### set_tcp_keepalive

    mixed ZSocket::set_tcp_keepalive()



...

* Visibility: **public**




### set_tcp_keepalive_idle

    mixed ZSocket::set_tcp_keepalive_idle()



...

* Visibility: **public**




### set_tcp_keepalive_cnt

    mixed ZSocket::set_tcp_keepalive_cnt()



...

* Visibility: **public**




### set_tcp_keepalive_intvl

    mixed ZSocket::set_tcp_keepalive_intvl()



...

* Visibility: **public**




### set_tcp_accept_filter

    mixed ZSocket::set_tcp_accept_filter()



...

* Visibility: **public**



