Majordomo\V2\Client
===============

Client

...


* Class name: Client
* Namespace: Majordomo\V2
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Majordomo\V2\Client Majordomo\V2\Client::__construct(string $broker_endpoint)



...

* Visibility: **public**


#### Arguments
* $broker_endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### set_verbose

    mixed Majordomo\V2\Client::set_verbose()



...

* Visibility: **public**




### recv

    \ZMsg Majordomo\V2\Client::recv()

Recieve a ZMsg.



* Visibility: **public**




### call

    \ZMsg Majordomo\V2\Client::call(string $service_name)



...

* Visibility: **public**


#### Arguments
* $service_name **string** - &lt;p&gt;...&lt;/p&gt;



### call_async

    mixed Majordomo\V2\Client::call_async(string $service_name)



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



