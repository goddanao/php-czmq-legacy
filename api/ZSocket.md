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

    \ZSocket ZSocket::__construct(string $socket_type, string $endpoint)



...

* Visibility: **public**


#### Arguments
* $socket_type **string** - &lt;p&gt;...&lt;/p&gt;
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



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



### attach

    mixed ZSocket::attach(string $endpoints, boolean $serverish)



...

* Visibility: **public**


#### Arguments
* $endpoints **string** - &lt;p&gt;...&lt;/p&gt;
* $serverish **boolean** - &lt;p&gt;... (optional)&lt;/p&gt;



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




### get_socket_type

    mixed ZSocket::get_socket_type()



...

* Visibility: **public**




### send

    mixed ZSocket::send(string $data)



...

* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;...&lt;/p&gt;



### recv

    mixed ZSocket::recv()



...

* Visibility: **public**




### send_string

    mixed ZSocket::send_string(string $data)



...

* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;...&lt;/p&gt;



### recv_string

    mixed ZSocket::recv_string()



...

* Visibility: **public**




### send_picture

    mixed ZSocket::send_picture(string $picture)



...

* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;...&lt;/p&gt;



### recv_picture

    mixed ZSocket::recv_picture(string $picture)



...

* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;...&lt;/p&gt;



### pub

    mixed ZSocket::pub(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### sub

    mixed ZSocket::sub(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### rep

    mixed ZSocket::rep(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### req

    mixed ZSocket::req(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### dealer

    mixed ZSocket::dealer(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### router

    mixed ZSocket::router(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### push

    mixed ZSocket::push(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### pull

    mixed ZSocket::pull(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### xpub

    mixed ZSocket::xpub(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### xsub

    mixed ZSocket::xsub(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### xreq

    mixed ZSocket::xreq(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### xrep

    mixed ZSocket::xrep(string $endpoint)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### stream

    mixed ZSocket::stream(string $endpoint)

Create a ZMQ_STREAM socket.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### server

    mixed ZSocket::server(mixed $endpoint)

Create a ZMQ_SERVER socket. (Requires ZMQ > 4.2.0)



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### client

    mixed ZSocket::client(mixed $endpoint)

Create a ZMQ_CLIENT socket. (Requires ZMQ > 4.2.0)



* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



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



