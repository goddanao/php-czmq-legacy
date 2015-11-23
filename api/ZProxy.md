ZProxy
===============

ZProxy

...


* Class name: ZProxy
* Namespace: 
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed ZProxy::__construct()

ZProxy::__construct

...

* Visibility: **public**




### set_verbose

    mixed ZProxy::set_verbose()

ZProxy::set_verbose

...

* Visibility: **public**




### pause

    mixed ZProxy::pause()

ZProxy::pause

...

* Visibility: **public**




### resume

    mixed ZProxy::resume()

ZProxy::resume

...

* Visibility: **public**




### recv

    \FileMq\ZMsg ZProxy::recv()

ZProxy::recv

Recieve a ZMsg.

* Visibility: **public**




### set_frontend

    mixed ZProxy::set_frontend(mixed $socket_type, mixed $socket_endpoint)

ZProxy::set_frontend

...

* Visibility: **public**


#### Arguments
* $socket_type **mixed** - &lt;p&gt;...&lt;/p&gt;
* $socket_endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### set_backend

    mixed ZProxy::set_backend(mixed $socket_type, mixed $socket_endpoint)

ZProxy::set_backend

...

* Visibility: **public**


#### Arguments
* $socket_type **mixed** - &lt;p&gt;...&lt;/p&gt;
* $socket_endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### set_capture

    mixed ZProxy::set_capture(mixed $socket_endpoint)

ZProxy::set_capture

...

* Visibility: **public**


#### Arguments
* $socket_endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### get_fd

    integer IZDescriptor::get_fd()

IZDescriptor::get_fd

Get the underlying File Descriptor.

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    \FileMq\ZSocket IZSocket::get_socket()

IZSocket::get_socket

Get the underlying ZSocket.

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)



