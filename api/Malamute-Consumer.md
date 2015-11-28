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

    \Malamute\Consumer Malamute\Consumer::__construct(string $endpoint, string $stream)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $stream **string** - &lt;p&gt;...&lt;/p&gt;



### set_timeout

    mixed Malamute\Consumer::set_timeout(integer $timeout)



...

* Visibility: **public**


#### Arguments
* $timeout **integer** - &lt;p&gt;...&lt;/p&gt;



### header

    mixed Malamute\Consumer::header(string $header)



...

* Visibility: **public**


#### Arguments
* $header **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### run

    mixed Malamute\Consumer::run(string $pattern, callable $callback)



...

* Visibility: **public**


#### Arguments
* $pattern **string** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### get_client

    \Malamute\Client Malamute\Consumer::get_client()

Get the underlying Malamute Client.



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



