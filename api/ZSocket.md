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

    mixed ZSocket::__construct($socket_type, $endpoint)

ZSocket::__construct

...

* Visibility: **public**


#### Arguments
* $socket_type **mixed**
* $endpoint **mixed**



### set_verbose

    mixed ZSocket::set_verbose()

ZSocket::set_verbose

...

* Visibility: **public**




### set_unbounded

    mixed ZSocket::set_unbounded()

ZSocket::set_unbounded

...

* Visibility: **public**




### bind

    mixed ZSocket::bind($endpoint)

ZSocket::bind

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**



### unbind

    mixed ZSocket::unbind($endpoint)

ZSocket::unbind

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**



### connect

    mixed ZSocket::connect($endpoint)

ZSocket::connect

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**



### disconnect

    mixed ZSocket::disconnect($endpoint)

ZSocket::disconnect

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**



### attach

    mixed ZSocket::attach($endpoints, $serverish)

ZSocket::attach

...

* Visibility: **public**


#### Arguments
* $endpoints **mixed**
* $serverish **mixed**



### signal

    mixed ZSocket::signal($byte)

ZSocket::signal

...

* Visibility: **public**


#### Arguments
* $byte **mixed**



### wait

    mixed ZSocket::wait()

ZSocket::wait

...

* Visibility: **public**




### flush

    mixed ZSocket::flush()

ZSocket::flush

...

* Visibility: **public**




### send

    mixed ZSocket::send($zmsg)

ZSocket::send

...

* Visibility: **public**


#### Arguments
* $zmsg **mixed**



### recv

    mixed ZSocket::recv()

ZSocket::recv

...

* Visibility: **public**




### send_string

    mixed ZSocket::send_string($value)

ZSocket::send_string

...

* Visibility: **public**


#### Arguments
* $value **mixed**



### recv_string

    mixed ZSocket::recv_string()

ZSocket::recv_string

...

* Visibility: **public**




### send_picture

    mixed ZSocket::send_picture($picture)

ZSocket::send_picture

...

* Visibility: **public**


#### Arguments
* $picture **mixed**



### recv_picture

    mixed ZSocket::recv_picture($picture)

ZSocket::recv_picture

...

* Visibility: **public**


#### Arguments
* $picture **mixed**



### pub

    mixed ZSocket::pub()

ZSocket::pub

...

* Visibility: **public**
* This method is **static**.




### sub

    mixed ZSocket::sub()

ZSocket::sub

...

* Visibility: **public**
* This method is **static**.




### rep

    mixed ZSocket::rep()

ZSocket::rep

...

* Visibility: **public**
* This method is **static**.




### req

    mixed ZSocket::req()

ZSocket::req

...

* Visibility: **public**
* This method is **static**.




### dealer

    mixed ZSocket::dealer()

ZSocket::dealer

...

* Visibility: **public**
* This method is **static**.




### router

    mixed ZSocket::router()

ZSocket::router

...

* Visibility: **public**
* This method is **static**.




### push

    mixed ZSocket::push()

ZSocket::push

...

* Visibility: **public**
* This method is **static**.




### pull

    mixed ZSocket::pull()

ZSocket::pull

...

* Visibility: **public**
* This method is **static**.




### xpub

    mixed ZSocket::xpub()

ZSocket::xpub

...

* Visibility: **public**
* This method is **static**.




### xsub

    mixed ZSocket::xsub()

ZSocket::xsub

...

* Visibility: **public**
* This method is **static**.




### xreq

    mixed ZSocket::xreq()

ZSocket::xreq

...

* Visibility: **public**
* This method is **static**.




### xrep

    mixed ZSocket::xrep()

ZSocket::xrep

...

* Visibility: **public**
* This method is **static**.




### stream

    mixed ZSocket::stream()

ZSocket::stream

...

* Visibility: **public**
* This method is **static**.




### get_options

    mixed ZSocket::get_options()

ZSocket::get_options

...

* Visibility: **public**




### get_fd

    mixed IZDescriptor::get_fd()

IZDescriptor::get_fd

...

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    mixed IZSocket::get_socket()

IZSocket::get_socket

...

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)




### get_tos

    mixed ZSocket::get_tos()

ZSocket::get_tos

...

* Visibility: **public**




### get_zap_domain

    mixed ZSocket::get_zap_domain()

ZSocket::get_zap_domain

...

* Visibility: **public**




### get_mechanism

    mixed ZSocket::get_mechanism()

ZSocket::get_mechanism

...

* Visibility: **public**




### get_plain_server

    mixed ZSocket::get_plain_server()

ZSocket::get_plain_server

...

* Visibility: **public**




### get_plain_username

    mixed ZSocket::get_plain_username()

ZSocket::get_plain_username

...

* Visibility: **public**




### get_plain_password

    mixed ZSocket::get_plain_password()

ZSocket::get_plain_password

...

* Visibility: **public**




### get_curve_server

    mixed ZSocket::get_curve_server()

ZSocket::get_curve_server

...

* Visibility: **public**




### get_curve_publickey

    mixed ZSocket::get_curve_publickey()

ZSocket::get_curve_publickey

...

* Visibility: **public**




### get_curve_secretkey

    mixed ZSocket::get_curve_secretkey()

ZSocket::get_curve_secretkey

...

* Visibility: **public**




### get_curve_serverkey

    mixed ZSocket::get_curve_serverkey()

ZSocket::get_curve_serverkey

...

* Visibility: **public**




### get_gssapi_server

    mixed ZSocket::get_gssapi_server()

ZSocket::get_gssapi_server

...

* Visibility: **public**




### get_gssapi_plaintext

    mixed ZSocket::get_gssapi_plaintext()

ZSocket::get_gssapi_plaintext

...

* Visibility: **public**




### get_gssapi_principal

    mixed ZSocket::get_gssapi_principal()

ZSocket::get_gssapi_principal

...

* Visibility: **public**




### get_gssapi_service_principal

    mixed ZSocket::get_gssapi_service_principal()

ZSocket::get_gssapi_service_principal

...

* Visibility: **public**




### get_ipv6

    mixed ZSocket::get_ipv6()

ZSocket::get_ipv6

...

* Visibility: **public**




### get_immediate

    mixed ZSocket::get_immediate()

ZSocket::get_immediate

...

* Visibility: **public**




### get_ipv4only

    mixed ZSocket::get_ipv4only()

ZSocket::get_ipv4only

...

* Visibility: **public**




### get_type

    mixed ZSocket::get_type()

ZSocket::get_type

...

* Visibility: **public**




### get_sndhwm

    mixed ZSocket::get_sndhwm()

ZSocket::get_sndhwm

...

* Visibility: **public**




### get_rcvhwm

    mixed ZSocket::get_rcvhwm()

ZSocket::get_rcvhwm

...

* Visibility: **public**




### get_affinity

    mixed ZSocket::get_affinity()

ZSocket::get_affinity

...

* Visibility: **public**




### get_identity

    mixed ZSocket::get_identity()

ZSocket::get_identity

...

* Visibility: **public**




### get_rate

    mixed ZSocket::get_rate()

ZSocket::get_rate

...

* Visibility: **public**




### get_recovery_ivl

    mixed ZSocket::get_recovery_ivl()

ZSocket::get_recovery_ivl

...

* Visibility: **public**




### get_sndbuf

    mixed ZSocket::get_sndbuf()

ZSocket::get_sndbuf

...

* Visibility: **public**




### get_rcvbuf

    mixed ZSocket::get_rcvbuf()

ZSocket::get_rcvbuf

...

* Visibility: **public**




### get_linger

    mixed ZSocket::get_linger()

ZSocket::get_linger

...

* Visibility: **public**




### get_reconnect_ivl

    mixed ZSocket::get_reconnect_ivl()

ZSocket::get_reconnect_ivl

...

* Visibility: **public**




### get_reconnect_ivl_max

    mixed ZSocket::get_reconnect_ivl_max()

ZSocket::get_reconnect_ivl_max

...

* Visibility: **public**




### get_backlog

    mixed ZSocket::get_backlog()

ZSocket::get_backlog

...

* Visibility: **public**




### get_maxmsgsize

    mixed ZSocket::get_maxmsgsize()

ZSocket::get_maxmsgsize

...

* Visibility: **public**




### get_multicast_hops

    mixed ZSocket::get_multicast_hops()

ZSocket::get_multicast_hops

...

* Visibility: **public**




### get_rcvtimeo

    mixed ZSocket::get_rcvtimeo()

ZSocket::get_rcvtimeo

...

* Visibility: **public**




### get_sndtimeo

    mixed ZSocket::get_sndtimeo()

ZSocket::get_sndtimeo

...

* Visibility: **public**




### get_tcp_keepalive

    mixed ZSocket::get_tcp_keepalive()

ZSocket::get_tcp_keepalive

...

* Visibility: **public**




### get_tcp_keepalive_idle

    mixed ZSocket::get_tcp_keepalive_idle()

ZSocket::get_tcp_keepalive_idle

...

* Visibility: **public**




### get_tcp_keepalive_cnt

    mixed ZSocket::get_tcp_keepalive_cnt()

ZSocket::get_tcp_keepalive_cnt

...

* Visibility: **public**




### get_tcp_keepalive_intvl

    mixed ZSocket::get_tcp_keepalive_intvl()

ZSocket::get_tcp_keepalive_intvl

...

* Visibility: **public**




### get_tcp_accept_filter

    mixed ZSocket::get_tcp_accept_filter()

ZSocket::get_tcp_accept_filter

...

* Visibility: **public**




### get_rcvmore

    mixed ZSocket::get_rcvmore()

ZSocket::get_rcvmore

...

* Visibility: **public**




### get_events

    mixed ZSocket::get_events()

ZSocket::get_events

...

* Visibility: **public**




### get_last_endpoint

    mixed ZSocket::get_last_endpoint()

ZSocket::get_last_endpoint

...

* Visibility: **public**




### set_tos

    mixed ZSocket::set_tos()

ZSocket::set_tos

...

* Visibility: **public**




### set_router_handover

    mixed ZSocket::set_router_handover()

ZSocket::set_router_handover

...

* Visibility: **public**




### set_router_mandatory

    mixed ZSocket::set_router_mandatory()

ZSocket::set_router_mandatory

...

* Visibility: **public**




### set_probe_router

    mixed ZSocket::set_probe_router()

ZSocket::set_probe_router

...

* Visibility: **public**




### set_req_relaxed

    mixed ZSocket::set_req_relaxed()

ZSocket::set_req_relaxed

...

* Visibility: **public**




### set_req_correlate

    mixed ZSocket::set_req_correlate()

ZSocket::set_req_correlate

...

* Visibility: **public**




### set_conflate

    mixed ZSocket::set_conflate()

ZSocket::set_conflate

...

* Visibility: **public**




### set_zap_domain

    mixed ZSocket::set_zap_domain()

ZSocket::set_zap_domain

...

* Visibility: **public**




### set_plain_server

    mixed ZSocket::set_plain_server()

ZSocket::set_plain_server

...

* Visibility: **public**




### set_plain_username

    mixed ZSocket::set_plain_username()

ZSocket::set_plain_username

...

* Visibility: **public**




### set_plain_password

    mixed ZSocket::set_plain_password()

ZSocket::set_plain_password

...

* Visibility: **public**




### set_curve_server

    mixed ZSocket::set_curve_server()

ZSocket::set_curve_server

...

* Visibility: **public**




### set_curve_publickey

    mixed ZSocket::set_curve_publickey()

ZSocket::set_curve_publickey

...

* Visibility: **public**




### set_curve_publickey_bin

    mixed ZSocket::set_curve_publickey_bin()

ZSocket::set_curve_publickey_bin

...

* Visibility: **public**




### set_curve_secretkey

    mixed ZSocket::set_curve_secretkey()

ZSocket::set_curve_secretkey

...

* Visibility: **public**




### set_curve_secretkey_bin

    mixed ZSocket::set_curve_secretkey_bin()

ZSocket::set_curve_secretkey_bin

...

* Visibility: **public**




### set_curve_serverkey

    mixed ZSocket::set_curve_serverkey()

ZSocket::set_curve_serverkey

...

* Visibility: **public**




### set_curve_serverkey_bin

    mixed ZSocket::set_curve_serverkey_bin()

ZSocket::set_curve_serverkey_bin

...

* Visibility: **public**




### set_gssapi_server

    mixed ZSocket::set_gssapi_server()

ZSocket::set_gssapi_server

...

* Visibility: **public**




### set_gssapi_plaintext

    mixed ZSocket::set_gssapi_plaintext()

ZSocket::set_gssapi_plaintext

...

* Visibility: **public**




### set_gssapi_principal

    mixed ZSocket::set_gssapi_principal()

ZSocket::set_gssapi_principal

...

* Visibility: **public**




### set_gssapi_service_principal

    mixed ZSocket::set_gssapi_service_principal()

ZSocket::set_gssapi_service_principal

...

* Visibility: **public**




### set_ipv6

    mixed ZSocket::set_ipv6()

ZSocket::set_ipv6

...

* Visibility: **public**




### set_immediate

    mixed ZSocket::set_immediate()

ZSocket::set_immediate

...

* Visibility: **public**




### set_router_raw

    mixed ZSocket::set_router_raw()

ZSocket::set_router_raw

...

* Visibility: **public**




### set_ipv4only

    mixed ZSocket::set_ipv4only()

ZSocket::set_ipv4only

...

* Visibility: **public**




### set_delay_attach_on_connect

    mixed ZSocket::set_delay_attach_on_connect()

ZSocket::set_delay_attach_on_connect

...

* Visibility: **public**




### set_sndhwm

    mixed ZSocket::set_sndhwm()

ZSocket::set_sndhwm

...

* Visibility: **public**




### set_rcvhwm

    mixed ZSocket::set_rcvhwm()

ZSocket::set_rcvhwm

...

* Visibility: **public**




### set_affinity

    mixed ZSocket::set_affinity()

ZSocket::set_affinity

...

* Visibility: **public**




### set_subscribe

    mixed ZSocket::set_subscribe()

ZSocket::set_subscribe

...

* Visibility: **public**




### set_unsubscribe

    mixed ZSocket::set_unsubscribe()

ZSocket::set_unsubscribe

...

* Visibility: **public**




### set_identity

    mixed ZSocket::set_identity()

ZSocket::set_identity

...

* Visibility: **public**




### set_rate

    mixed ZSocket::set_rate()

ZSocket::set_rate

...

* Visibility: **public**




### set_recovery_ivl

    mixed ZSocket::set_recovery_ivl()

ZSocket::set_recovery_ivl

...

* Visibility: **public**




### set_sndbuf

    mixed ZSocket::set_sndbuf()

ZSocket::set_sndbuf

...

* Visibility: **public**




### set_rcvbuf

    mixed ZSocket::set_rcvbuf()

ZSocket::set_rcvbuf

...

* Visibility: **public**




### set_linger

    mixed ZSocket::set_linger()

ZSocket::set_linger

...

* Visibility: **public**




### set_reconnect_ivl

    mixed ZSocket::set_reconnect_ivl()

ZSocket::set_reconnect_ivl

...

* Visibility: **public**




### set_reconnect_ivl_max

    mixed ZSocket::set_reconnect_ivl_max()

ZSocket::set_reconnect_ivl_max

...

* Visibility: **public**




### set_backlog

    mixed ZSocket::set_backlog()

ZSocket::set_backlog

...

* Visibility: **public**




### set_maxmsgsize

    mixed ZSocket::set_maxmsgsize()

ZSocket::set_maxmsgsize

...

* Visibility: **public**




### set_multicast_hops

    mixed ZSocket::set_multicast_hops()

ZSocket::set_multicast_hops

...

* Visibility: **public**




### set_rcvtimeo

    mixed ZSocket::set_rcvtimeo()

ZSocket::set_rcvtimeo

...

* Visibility: **public**




### set_sndtimeo

    mixed ZSocket::set_sndtimeo()

ZSocket::set_sndtimeo

...

* Visibility: **public**




### set_xpub_verbose

    mixed ZSocket::set_xpub_verbose()

ZSocket::set_xpub_verbose

...

* Visibility: **public**




### set_tcp_keepalive

    mixed ZSocket::set_tcp_keepalive()

ZSocket::set_tcp_keepalive

...

* Visibility: **public**




### set_tcp_keepalive_idle

    mixed ZSocket::set_tcp_keepalive_idle()

ZSocket::set_tcp_keepalive_idle

...

* Visibility: **public**




### set_tcp_keepalive_cnt

    mixed ZSocket::set_tcp_keepalive_cnt()

ZSocket::set_tcp_keepalive_cnt

...

* Visibility: **public**




### set_tcp_keepalive_intvl

    mixed ZSocket::set_tcp_keepalive_intvl()

ZSocket::set_tcp_keepalive_intvl

...

* Visibility: **public**




### set_tcp_accept_filter

    mixed ZSocket::set_tcp_accept_filter()

ZSocket::set_tcp_accept_filter

...

* Visibility: **public**



