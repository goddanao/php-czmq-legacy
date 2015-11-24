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

    mixed Majordomo\V1\Worker::__construct(mixed $broker_endpoint, mixed $name, mixed $verbose)

Worker::__construct

...

* Visibility: **public**


#### Arguments
* $broker_endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $name **mixed** - &lt;p&gt;...&lt;/p&gt;
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### run

    mixed Majordomo\V1\Worker::run(callable $callback)

Worker::run

...

* Visibility: **public**


#### Arguments
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



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



