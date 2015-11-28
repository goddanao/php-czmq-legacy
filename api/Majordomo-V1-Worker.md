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

    \Majordomo\V1\Worker Majordomo\V1\Worker::__construct(string $broker_endpoint, string $name, boolean $verbose)



...

* Visibility: **public**


#### Arguments
* $broker_endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $name **string** - &lt;p&gt;...&lt;/p&gt;
* $verbose **boolean** - &lt;p&gt;... (optional)&lt;/p&gt;



### run

    mixed Majordomo\V1\Worker::run(callable $callback)



...

* Visibility: **public**


#### Arguments
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



