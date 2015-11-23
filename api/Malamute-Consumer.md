Malamute\Consumer
===============

Consumer

...


* Class name: Consumer
* Namespace: Malamute
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed Malamute\Consumer::__construct($endpoint, $stream)

Consumer::__construct

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**
* $stream **mixed**



### set_timeout

    mixed Malamute\Consumer::set_timeout($timeout)

Consumer::set_timeout

...

* Visibility: **public**


#### Arguments
* $timeout **mixed**



### header

    mixed Malamute\Consumer::header($header)

Consumer::header

...

* Visibility: **public**


#### Arguments
* $header **mixed**



### run

    mixed Malamute\Consumer::run($pattern, callable $callback)

Consumer::run

...

* Visibility: **public**


#### Arguments
* $pattern **mixed**
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### get_client

    \FileMq\Malamute\Client Malamute\Consumer::get_client()

Consumer::get_client

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


