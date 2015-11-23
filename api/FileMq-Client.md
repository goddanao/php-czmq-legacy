FileMq\Client
===============

Client

...


* Class name: Client
* Namespace: FileMq
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed FileMq\Client::__construct($endpoint, $local_path, $timeout)

Client::__construct

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**
* $local_path **mixed**
* $timeout **mixed**



### set_timeout

    mixed FileMq\Client::set_timeout($timeout)

Client::set_timeout

...

* Visibility: **public**


#### Arguments
* $timeout **mixed**



### connect

    mixed FileMq\Client::connect()

Client::connect

...

* Visibility: **public**




### subscribe

    mixed FileMq\Client::subscribe($remote_path)

Client::subscribe

...

* Visibility: **public**


#### Arguments
* $remote_path **mixed**



### recv

    \ZMsg FileMq\Client::recv()

Client::recv

Recieve a ZMsg.

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



