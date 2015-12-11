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

    \ZProxy ZProxy::__construct(mixed $verbose)



...

* Visibility: **public**


#### Arguments
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed ZProxy::set_verbose()



...

* Visibility: **public**




### pause

    mixed ZProxy::pause()



...

* Visibility: **public**




### resume

    mixed ZProxy::resume()



...

* Visibility: **public**




### recv

    \ZMsg ZProxy::recv()

Recieve a ZMsg.



* Visibility: **public**




### set_frontend

    mixed ZProxy::set_frontend(string $type, string $endpoint)



...

* Visibility: **public**


#### Arguments
* $type **string** - &lt;p&gt;...&lt;/p&gt;
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### set_backend

    mixed ZProxy::set_backend(string $type, string $endpoint)



...

* Visibility: **public**


#### Arguments
* $type **string** - &lt;p&gt;...&lt;/p&gt;
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### set_capture

    mixed ZProxy::set_capture(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



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



