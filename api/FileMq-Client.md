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

    \FileMq\Client FileMq\Client::__construct(mixed $endpoint, mixed $local_path, mixed $timeout)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $local_path **mixed** - &lt;p&gt;...&lt;/p&gt;
* $timeout **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_timeout

    mixed FileMq\Client::set_timeout(mixed $timeout)



...

* Visibility: **public**


#### Arguments
* $timeout **mixed** - &lt;p&gt;...&lt;/p&gt;



### connect

    mixed FileMq\Client::connect()



...

* Visibility: **public**




### subscribe

    mixed FileMq\Client::subscribe(mixed $remote_path)



...

* Visibility: **public**


#### Arguments
* $remote_path **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv

    \ZMsg FileMq\Client::recv()

Recieve a ZMsg.



* Visibility: **public**




### get_fd

    mixed IZDescriptor::get_fd()



...

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    mixed IZSocket::get_socket()



...

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)



