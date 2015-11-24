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

    mixed Malamute\Consumer::__construct(mixed $endpoint, mixed $stream)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;



### set_timeout

    mixed Malamute\Consumer::set_timeout(mixed $timeout)



...

* Visibility: **public**


#### Arguments
* $timeout **mixed** - &lt;p&gt;...&lt;/p&gt;



### header

    mixed Malamute\Consumer::header(mixed $header)



...

* Visibility: **public**


#### Arguments
* $header **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### run

    mixed Malamute\Consumer::run(mixed $pattern, callable $callback)



...

* Visibility: **public**


#### Arguments
* $pattern **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### get_client

    \FileMq\Malamute\Client Malamute\Consumer::get_client()

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



