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

    mixed Malamute\Worker::__construct($endpoint, $address, $pattern)

Worker::__construct

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**
* $address **mixed**
* $pattern **mixed**



### set_timeout

    mixed Malamute\Worker::set_timeout($timeout)

Worker::set_timeout

...

* Visibility: **public**


#### Arguments
* $timeout **mixed**



### run

    mixed Malamute\Worker::run(callable $callback)

Worker::run

...

* Visibility: **public**


#### Arguments
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### get_client

    \FileMq\Malamute\Client Malamute\Worker::get_client()

Worker::get_client

Get the underlying Malamute Client.

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



