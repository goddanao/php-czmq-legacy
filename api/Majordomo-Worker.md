Majordomo\Worker
===============

Worker

...


* Class name: Worker
* Namespace: Majordomo
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Majordomo\Worker Majordomo\Worker::__construct(mixed $name, mixed $broker_endpoint, callable $callback)



...

* Visibility: **public**


#### Arguments
* $name **mixed** - &lt;p&gt;...&lt;/p&gt;
* $broker_endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### set_verbose

    mixed Majordomo\Worker::set_verbose()



...

* Visibility: **public**




### run

    mixed Majordomo\Worker::run(mixed $name, mixed $broker_endpoint, callable $callback)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $name **mixed** - &lt;p&gt;...&lt;/p&gt;
* $broker_endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



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



