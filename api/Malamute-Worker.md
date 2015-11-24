Malamute\Worker
===============

Worker

...


* Class name: Worker
* Namespace: Malamute
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed Malamute\Worker::__construct(mixed $endpoint, mixed $address, mixed $pattern)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $address **mixed** - &lt;p&gt;...&lt;/p&gt;
* $pattern **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_timeout

    mixed Malamute\Worker::set_timeout(mixed $timeout)



...

* Visibility: **public**


#### Arguments
* $timeout **mixed** - &lt;p&gt;...&lt;/p&gt;



### run

    mixed Malamute\Worker::run(callable $callback)



...

* Visibility: **public**


#### Arguments
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### get_client

    \FileMq\Malamute\Client Malamute\Worker::get_client()

Get the underlying Malamute Client.



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



