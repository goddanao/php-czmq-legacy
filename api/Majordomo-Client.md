Majordomo\Client
===============

Client

...


* Class name: Client
* Namespace: Majordomo
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Majordomo\Client Majordomo\Client::__construct(mixed $broker_endpoint)



...

* Visibility: **public**


#### Arguments
* $broker_endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### set_verbose

    mixed Majordomo\Client::set_verbose()



...

* Visibility: **public**




### recv

    mixed Majordomo\Client::recv()



...

* Visibility: **public**




### call

    mixed Majordomo\Client::call(mixed $service_name)



...

* Visibility: **public**


#### Arguments
* $service_name **mixed** - &lt;p&gt;...&lt;/p&gt;



### call_async

    mixed Majordomo\Client::call_async(mixed $service_name)



...

* Visibility: **public**


#### Arguments
* $service_name **mixed** - &lt;p&gt;...&lt;/p&gt;



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


