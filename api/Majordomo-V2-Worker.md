Majordomo\V2\Worker
===============

Worker

...


* Class name: Worker
* Namespace: Majordomo\V2
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed Majordomo\V2\Worker::__construct($name, $broker_endpoint, callable $callback)

Worker::__construct

...

* Visibility: **public**


#### Arguments
* $name **mixed**
* $broker_endpoint **mixed**
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### set_verbose

    mixed Majordomo\V2\Worker::set_verbose()

Worker::set_verbose

...

* Visibility: **public**




### run

    mixed Majordomo\V2\Worker::run()

Worker::run

...

* Visibility: **public**




### process

    mixed Majordomo\V2\Worker::process()

Worker::process

...

* Visibility: **public**




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



