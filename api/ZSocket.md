ZSocket
===============

ZSocket

...


* Class name: ZSocket
* Namespace: 
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)




Properties
----------


### $ipv4only

    public boolean $ipv4only





* Visibility: **public**


### $sndhwm

    public integer $sndhwm





* Visibility: **public**


### $rcvhwm

    public integer $rcvhwm





* Visibility: **public**


### $affinity

    public integer $affinity





* Visibility: **public**


### $identity

    public string $identity





* Visibility: **public**


### $rate

    public integer $rate





* Visibility: **public**


### $recovery_ivl

    public integer $recovery_ivl





* Visibility: **public**


### $sndbuf

    public integer $sndbuf





* Visibility: **public**


### $rcvbuf

    public integer $rcvbuf





* Visibility: **public**


### $linger

    public integer $linger





* Visibility: **public**


### $reconnect_ivl

    public integer $reconnect_ivl





* Visibility: **public**


### $reconnect_ivl_max

    public integer $reconnect_ivl_max





* Visibility: **public**


### $backlog

    public integer $backlog





* Visibility: **public**


### $maxmsgsize

    public integer $maxmsgsize





* Visibility: **public**


### $multicast_hops

    public integer $multicast_hops





* Visibility: **public**


### $rcvtimeo

    public integer $rcvtimeo





* Visibility: **public**


### $sndtimeo

    public integer $sndtimeo





* Visibility: **public**


### $tcp_keepalive

    public integer $tcp_keepalive





* Visibility: **public**


### $tcp_keepalive_idle

    public integer $tcp_keepalive_idle





* Visibility: **public**


### $tcp_keepalive_cnt

    public integer $tcp_keepalive_cnt





* Visibility: **public**


### $tcp_keepalive_intvl

    public integer $tcp_keepalive_intvl





* Visibility: **public**


### $tcp_accept_filter

    public string $tcp_accept_filter





* Visibility: **public**


### $tos

    public integer $tos





* Visibility: **public**


### $zap_domain

    public string $zap_domain





* Visibility: **public**


### $plain_server

    public boolean $plain_server





* Visibility: **public**


### $plain_username

    public string $plain_username





* Visibility: **public**


### $plain_password

    public string $plain_password





* Visibility: **public**


### $curve_server

    public boolean $curve_server





* Visibility: **public**


### $curve_publickey

    public string $curve_publickey





* Visibility: **public**


### $curve_secretkey

    public string $curve_secretkey





* Visibility: **public**


### $curve_serverkey

    public string $curve_serverkey





* Visibility: **public**


### $gssapi_server

    public boolean $gssapi_server





* Visibility: **public**


### $gssapi_plaintext

    public string $gssapi_plaintext





* Visibility: **public**


### $gssapi_principal

    public string $gssapi_principal





* Visibility: **public**


### $gssapi_service_principal

    public string $gssapi_service_principal





* Visibility: **public**


### $ipv6

    public boolean $ipv6





* Visibility: **public**


### $immediate

    public boolean $immediate





* Visibility: **public**


### $type

    public string $type

(read only)



* Visibility: **public**


### $rcvmore

    public boolean $rcvmore

(read only)



* Visibility: **public**


### $events

    public integer $events

(read only)



* Visibility: **public**


### $last_endpoint

    public string $last_endpoint

(read only)



* Visibility: **public**


### $mechanism

    public string $mechanism

(read only)



* Visibility: **public**


Methods
-------


### __construct

    \ZSocket ZSocket::__construct(mixed $type, string $endpoint)



...

* Visibility: **public**


#### Arguments
* $type **mixed** - &lt;p&gt;...&lt;/p&gt;
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### set_verbose

    mixed ZSocket::set_verbose()



...

* Visibility: **public**




### set_unbounded

    mixed ZSocket::set_unbounded()



...

* Visibility: **public**




### bind

    mixed ZSocket::bind(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### unbind

    mixed ZSocket::unbind(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### connect

    mixed ZSocket::connect(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### disconnect

    mixed ZSocket::disconnect(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### signal

    mixed ZSocket::signal(integer $byte)



...

* Visibility: **public**


#### Arguments
* $byte **integer** - &lt;p&gt;...&lt;/p&gt;



### wait

    mixed ZSocket::wait()



...

* Visibility: **public**




### flush

    mixed ZSocket::flush()



...

* Visibility: **public**




### send

    mixed ZSocket::send(string $data)



...

* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;...&lt;/p&gt;



### recv

    \ZMsg ZSocket::recv()



...

* Visibility: **public**




### send_string

    mixed ZSocket::send_string(string $data)



...

* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;...&lt;/p&gt;



### recv_string

    string ZSocket::recv_string()



...

* Visibility: **public**




### send_picture

    mixed ZSocket::send_picture(string $picture)



...

* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;...&lt;/p&gt;



### recv_picture

    array ZSocket::recv_picture(string $picture)



...

* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;...&lt;/p&gt;



### pub

    \ZSocket ZSocket::pub(string $endpoint)

Create a PUB socket. Default action is bind.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### sub

    \ZSocket ZSocket::sub(string $endpoint, string $topic)

Create a SUB socket, and optionally subscribe to some prefix string. Default action is connect.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;
* $topic **string** - &lt;p&gt;Topic to subscribe. (optional)&lt;/p&gt;



### rep

    \ZSocket ZSocket::rep(string $endpoint)

Create a REP socket. Default action is bind.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### req

    \ZSocket ZSocket::req(string $endpoint)

Create a REQ socket. Default action is connect.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### dealer

    \ZSocket ZSocket::dealer(string $endpoint)

Create a DEALER socket. Default action is connect.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### router

    \ZSocket ZSocket::router(string $endpoint)

Create a ROUTER socket. Default action is bind.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### push

    \ZSocket ZSocket::push(string $endpoint)

Create a PUSH socket. Default action is connect.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### pull

    \ZSocket ZSocket::pull(string $endpoint)

Create a PULL socket. Default action is bind.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### xpub

    \ZSocket ZSocket::xpub(string $endpoint)

Create an XPUB socket. Default action is bind.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### xsub

    \ZSocket ZSocket::xsub(string $endpoint)

Create an XSUB socket. Default action is connect.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### xreq

    \ZSocket ZSocket::xreq(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### xrep

    \ZSocket ZSocket::xrep(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### pair

    \ZSocket ZSocket::pair(string $endpoint)

Create a PAIR socket. Default action is connect.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### stream

    \ZSocket ZSocket::stream(string $endpoint)

Create a STREAM socket. Default action is connect.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### server

    \ZSocket ZSocket::server(string $endpoint)

Create a SERVER socket. Default action is bind. (Requires ZMQ > 4.2.0)



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### client

    \ZSocket ZSocket::client(string $endpoint)

Create a CLIENT socket. Default action is connect. (Requires ZMQ > 4.2.0)



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### get_options

    mixed ZSocket::get_options()



...

* Visibility: **public**




### get_fd

    integer IZDescriptor::get_fd()



...

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    \ZSocket IZSocket::get_socket()



...

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)




### set_router_raw

    mixed ZSocket::set_router_raw()



...

* Visibility: **public**




### set_delay_attach_on_connect

    mixed ZSocket::set_delay_attach_on_connect()



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




### set_xpub_verbose

    mixed ZSocket::set_xpub_verbose()



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




### set_curve_publickey_bin

    mixed ZSocket::set_curve_publickey_bin()



...

* Visibility: **public**




### set_curve_secretkey_bin

    mixed ZSocket::set_curve_secretkey_bin()



...

* Visibility: **public**




### set_curve_serverkey_bin

    mixed ZSocket::set_curve_serverkey_bin()



...

* Visibility: **public**



