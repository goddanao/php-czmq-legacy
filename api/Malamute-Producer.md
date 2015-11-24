Malamute\Producer
===============

Producer

...


* Class name: Producer
* Namespace: Malamute
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed Malamute\Producer::__construct(mixed $endpoint, mixed $stream)

Producer::__construct

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;



### set_timeout

    mixed Malamute\Producer::set_timeout(mixed $timeout)

Producer::set_timeout

...

* Visibility: **public**


#### Arguments
* $timeout **mixed** - &lt;p&gt;...&lt;/p&gt;



### run

    mixed Malamute\Producer::run(mixed $subject, callable $callback)

Producer::run

...

* Visibility: **public**


#### Arguments
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### get_client

    \FileMq\Malamute\Client Malamute\Producer::get_client()

Producer::get_client

Get the underlying Malamute Client.

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



