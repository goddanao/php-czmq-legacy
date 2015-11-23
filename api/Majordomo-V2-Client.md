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

    mixed Majordomo\V2\Client::__construct($broker_endpoint)

Client::__construct

...

* Visibility: **public**


#### Arguments
* $broker_endpoint **mixed**



### set_verbose

    mixed Majordomo\V2\Client::set_verbose()

Client::set_verbose

...

* Visibility: **public**




### recv

    \FileMq\ZMsg Majordomo\V2\Client::recv()

Client::recv

Recieve a ZMsg.

* Visibility: **public**




### call

    mixed Majordomo\V2\Client::call($service_name)

Client::call

...

* Visibility: **public**


#### Arguments
* $service_name **mixed**



### call_async

    mixed Majordomo\V2\Client::call_async($service_name)

Client::call_async

...

* Visibility: **public**


#### Arguments
* $service_name **mixed**



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



