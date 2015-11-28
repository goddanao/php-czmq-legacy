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

    \Majordomo\V2\Worker Majordomo\V2\Worker::__construct(string $name, string $broker_endpoint, callable $callback)



...

* Visibility: **public**


#### Arguments
* $name **string** - &lt;p&gt;...&lt;/p&gt;
* $broker_endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### set_verbose

    mixed Majordomo\V2\Worker::set_verbose()



...

* Visibility: **public**




### run

    mixed Majordomo\V2\Worker::run()



...

* Visibility: **public**




### process

    mixed Majordomo\V2\Worker::process()



...

* Visibility: **public**




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



