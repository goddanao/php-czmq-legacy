Majordomo\V1\Worker
===============

Worker

...


* Class name: Worker
* Namespace: Majordomo\V1
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed Majordomo\V1\Worker::__construct($broker_endpoint, $name, $verbose)

Worker::__construct

...

* Visibility: **public**


#### Arguments
* $broker_endpoint **mixed**
* $name **mixed**
* $verbose **mixed**



### run

    mixed Majordomo\V1\Worker::run(callable $callback)

Worker::run

...

* Visibility: **public**


#### Arguments
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



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



