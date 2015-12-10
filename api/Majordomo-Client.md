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

    \Majordomo\Client Majordomo\Client::__construct(string $broker_endpoint)



...

* Visibility: **public**


#### Arguments
* $broker_endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### set_verbose

    mixed Majordomo\Client::set_verbose()



...

* Visibility: **public**




### recv

    \ZMsg Majordomo\Client::recv()



...

* Visibility: **public**




### call

    \ZMsg Majordomo\Client::call(string $service_name)



...

* Visibility: **public**


#### Arguments
* $service_name **string** - &lt;p&gt;...&lt;/p&gt;



### call_async

    boolean Majordomo\Client::call_async(string $service_name)



...

* Visibility: **public**


#### Arguments
* $service_name **string** - &lt;p&gt;...&lt;/p&gt;



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



