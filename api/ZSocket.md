ZSocket
===============

ZSocket

ZeroMQ Socket


* Class name: ZSocket
* Namespace: 
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)




Properties
----------


### $handshake_ivl

    public integer $handshake_ivl

Get/Set maximum handshake interval. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc15)



* Visibility: **public**


### $ipv4only

    public boolean $ipv4only

Enable/Disable Use IPv4-only on socket (This option is deprecated. Please use the ZMQ_IPV6 option). [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc54)



* Visibility: **public**


### $sndhwm

    public integer $sndhwm

Get/Set high water mark for outbound messages. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc39)



* Visibility: **public**


### $rcvhwm

    public integer $rcvhwm

Get/Set high water mark for inbound messages. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc28)



* Visibility: **public**


### $affinity

    public integer $affinity

Get/Set I/O thread affinity. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc3)



* Visibility: **public**


### $identity

    public string $identity

Get/Set socket identity. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc16)



* Visibility: **public**


### $rate

    public integer $rate

Get/Set multicast data rate. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc26)



* Visibility: **public**


### $recovery_ivl

    public integer $recovery_ivl

Get/Set multicast recovery interval. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc32)



* Visibility: **public**


### $sndbuf

    public integer $sndbuf

Get/Set kernel transmit buffer size. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc38)



* Visibility: **public**


### $rcvbuf

    public integer $rcvbuf

Get/Set kernel receive buffer size. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc27)



* Visibility: **public**


### $linger

    public integer $linger

Get/Set linger period for socket shutdown. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc19)



* Visibility: **public**


### $reconnect_ivl

    public integer $reconnect_ivl

Get/Set reconnection interval. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc30)



* Visibility: **public**


### $reconnect_ivl_max

    public integer $reconnect_ivl_max

Get/Set maximum reconnection interval. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc31)



* Visibility: **public**


### $backlog

    public integer $backlog

Get/Set maximum length of the queue of outstanding connections. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc4)



* Visibility: **public**


### $maxmsgsize

    public integer $maxmsgsize

Get/Set Maximum acceptable inbound message size. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc20)



* Visibility: **public**


### $multicast_hops

    public integer $multicast_hops

Get/Set Maximum network hops for multicast packets. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc21)



* Visibility: **public**


### $rcvtimeo

    public integer $rcvtimeo

Get/Set Maximum time before a recv operation returns with EAGAIN. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc29)



* Visibility: **public**


### $sndtimeo

    public integer $sndtimeo

Get/Set Maximum time before a send operation returns with EAGAIN. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc40)



* Visibility: **public**


### $tcp_keepalive

    public integer $tcp_keepalive

Get/Set Override SO_KEEPALIVE socket option [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc42)



* Visibility: **public**


### $tcp_keepalive_idle

    public integer $tcp_keepalive_idle

Get/Set Override TCP_KEEPCNT (or TCP_KEEPALIVE on some OS). [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc44)



* Visibility: **public**


### $tcp_keepalive_cnt

    public integer $tcp_keepalive_cnt

Get/Set Override TCP_KEEPCNT socket option. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc43)



* Visibility: **public**


### $tcp_keepalive_intvl

    public integer $tcp_keepalive_intvl

Get/Set Override TCP_KEEPINTVL socket option. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc45)



* Visibility: **public**


### $tcp_accept_filter

    public string $tcp_accept_filter

Get/Set filters to allow new TCP connections (This option is deprecated, please use authentication via the ZAP API and IP address whitelisting / blacklisting). [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc50)



* Visibility: **public**


### $tos

    public integer $tos

Get/Set the Type-of-Service on socket. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc46)



* Visibility: **public**


### $zap_domain

    public string $zap_domain

Get/Set RFC 27 authentication domain. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc49)



* Visibility: **public**


### $plain_server

    public boolean $plain_server

Enable/Disable PLAIN server role. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc23)



* Visibility: **public**


### $plain_username

    public string $plain_username

Get/Set PLAIN security username. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc24)



* Visibility: **public**


### $plain_password

    public string $plain_password

Get/Set PLAIN security password. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc22)



* Visibility: **public**


### $curve_server

    public boolean $curve_server

Enable/Disable CURVE server role. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc9)



* Visibility: **public**


### $curve_publickey

    public string $curve_publickey

Set CURVE public key. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc7)



* Visibility: **public**


### $curve_secretkey

    public string $curve_secretkey

Set CURVE secret key. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc8)



* Visibility: **public**


### $curve_serverkey

    public string $curve_serverkey

Set CURVE server key. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc10)



* Visibility: **public**


### $gssapi_server

    public boolean $gssapi_server

Enable/Disable GSSAPI server role. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc13)



* Visibility: **public**


### $gssapi_plaintext

    public boolean $gssapi_plaintext

Enable/Disable GSSAPI encryption. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc11)



* Visibility: **public**


### $gssapi_principal

    public string $gssapi_principal

Get/Set name of GSSAPI principal. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc12)



* Visibility: **public**


### $gssapi_service_principal

    public string $gssapi_service_principal

Get/Set name of GSSAPI service principal. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc14)



* Visibility: **public**


### $ipv6

    public boolean $ipv6

Enable/Disable IPv6 on socket. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc18)



* Visibility: **public**


### $immediate

    public boolean $immediate

Enable/Disable queue messages only to completed connections. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc17)



* Visibility: **public**


### $rid

    public string $rid

Set the next outbound connection id. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc5) (write only)



* Visibility: **public**


### $conflate

    public boolean $conflate

Enable/Disable keep only last message. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc6) (write only)



* Visibility: **public**


### $router_handover

    public boolean $router_handover

Enable/Disable handle duplicate client identities on ROUTER sockets. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc35) (write only)



* Visibility: **public**


### $router_mandatory

    public boolean $router_mandatory

Enable/Disable accept only routable messages on ROUTER sockets. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc36) (write only)



* Visibility: **public**


### $probe_router

    public boolean $probe_router

Enable/Disable bootstrap connections to ROUTER sockets. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc25) (write only)



* Visibility: **public**


### $req_relaxed

    public boolean $req_relaxed

Enable/Disable relax strict alternation between request and reply. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc34) (write only)



* Visibility: **public**


### $req_correlate

    public boolean $req_correlate

Enable/Disable match replies with requests. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc33) (write only)



* Visibility: **public**


### $router_raw

    public boolean $router_raw

Enable/Disable switch ROUTER socket to raw mode (This option is deprecated, please use ZMQ_STREAM sockets instead). [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc37) (write only)



* Visibility: **public**


### $delay_attach_on_connect

    public boolean $delay_attach_on_connect

Enable/Disable  [more..](http://api.zeromq.org/4-1:zmq-setsockopt) (write only)



* Visibility: **public**


### $xpub_verbose

    public boolean $xpub_verbose

Enable/Disable provide all subscription messages on XPUB sockets. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc48) (write only)



* Visibility: **public**


### $type

    public string $type

Get ZSocket type. (read only)



* Visibility: **public**


### $mechanism

    public string $mechanism

Get current security mechanism configured for socket. (read only)



* Visibility: **public**


### $last_endpoint

    public string $last_endpoint

Get the last known connected/binded endpoint. (read only)



* Visibility: **public**


### $events

    public integer $events

Get the current events for socket. (read only)



* Visibility: **public**


### $rcvmore

    public boolean $rcvmore

Get More message data parts to follow. (read only)



* Visibility: **public**


Methods
-------


### __construct

    \ZSocket ZSocket::__construct(mixed $type, string $endpoint)



...

* Visibility: **public**


#### Arguments
* $type **mixed** - &lt;p&gt;The socket type to be created.&lt;/p&gt;
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### set_verbose

    mixed ZSocket::set_verbose()

Enable verbose mode, debug outputs are shown.



* Visibility: **public**




### set_unbounded

    mixed ZSocket::set_unbounded()

Set socket to use unbounded pipes (HWM=0); use this in cases when you are totally certain the message volume can fit in memory



* Visibility: **public**




### bind

    boolean ZSocket::bind(string|array $endpoint)

Bind to the specified endpoint(s).



* Visibility: **public**


#### Arguments
* $endpoint **string|array** - &lt;p&gt;Endpoint(s) to bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;)&lt;/p&gt;



### unbind

    mixed ZSocket::unbind(string $endpoint)

Unbind from the specified endpoint(s).



* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint(s) to unbind from.&lt;/p&gt;



### connect

    boolean ZSocket::connect(string|array $endpoint)

Connect to the specified endpoint(s).



* Visibility: **public**


#### Arguments
* $endpoint **string|array** - &lt;p&gt;Endpoint(s) to connect to. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;)&lt;/p&gt;



### disconnect

    mixed ZSocket::disconnect(string $endpoint)

Disconnect from the specified endpoint(s).



* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint(s) to disconnect from.&lt;/p&gt;



### signal

    boolean ZSocket::signal(integer $byte)

Send a signal over a socket. A signal is a short message carrying a success/failure code (by convention, 0 means OK).

* Signals are encoded to be distinguishable from 'normal' messages

* Visibility: **public**


#### Arguments
* $byte **integer** - &lt;p&gt;...&lt;/p&gt;



### wait

    boolean ZSocket::wait()

Wait on a signal. Use this to coordinate between threads, over pipe pairs. Blocks until the signal is received.



* Visibility: **public**




### flush

    mixed ZSocket::flush()

If there is a partial message still waiting on the socket, remove and discard it. This is useful
* when reading partial messages, to get specific message types.



* Visibility: **public**




### recv

    \ZMsg ZSocket::recv()

Recieve next message from the socket.



* Visibility: **public**




### recv_string

    string ZSocket::recv_string()

Recieve a message and pop first frame as string.



* Visibility: **public**




### recv_picture

    mixed ZSocket::recv_picture(string $picture)

Recieve a message and pop frames as indicated in the picture format specified.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to extract from message.&lt;/p&gt;



### recv_msgpack

    mixed ZSocket::recv_msgpack()

Recieve a message and pop first frame decoding with MsgPack.



* Visibility: **public**




### recv_zipped

    mixed ZSocket::recv_zipped()

Recieve a message and pop first frame decoding with ZLib.



* Visibility: **public**




### send

    mixed ZSocket::send(mixed $data)

Send message.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;Data to send.&lt;/p&gt;



### send_string

    mixed ZSocket::send_string(string $data)

Send a one frame only message with a string.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;The string to send&lt;/p&gt;



### send_picture

    mixed ZSocket::send_picture(string $picture)

Send a message composed by data frames as specified in the picture format.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to push in message.&lt;/p&gt;



### send_msgpack

    mixed ZSocket::send_msgpack(mixed $data)

Send a one frame only message encoded with MsgPack.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;The data to send.&lt;/p&gt;



### send_zipped

    mixed ZSocket::send_zipped(mixed $data)

Send a one frame only message encoded with ZLib.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;The data to be encoded.&lt;/p&gt;



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

Alias for ROUTER socket. Default action is bind.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;Endpoint to connect or bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;) (optional)&lt;/p&gt;



### xrep

    \ZSocket ZSocket::xrep(string $endpoint)

Alias for DEALER socket. Default action is connect.



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

    array ZSocket::get_options()

Return a map of socket options values.



* Visibility: **public**




### get_fd

    integer IZDescriptor::get_fd()

Get the underlying File Descriptor.



* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    \ZSocket IZSocket::get_socket()

Get the underlying ZSocket.



* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)




### subscribe

    mixed ZSocket::subscribe(string $topic)

Subscribe a specific topic. (only ZMQ_SUB socket type).



* Visibility: **public**


#### Arguments
* $topic **string** - &lt;p&gt;Topic name.&lt;/p&gt;



### unsubscribe

    mixed ZSocket::unsubscribe(string $topic)

Unsubscribe a specific topic. (only ZMQ_SUB socket type).



* Visibility: **public**


#### Arguments
* $topic **string** - &lt;p&gt;Topic name.&lt;/p&gt;


