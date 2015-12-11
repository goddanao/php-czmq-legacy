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

    \Malamute\Consumer Malamute\Consumer::__construct(string $endpoint, string $stream, mixed $pattern)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $stream **string** - &lt;p&gt;... (optional)&lt;/p&gt;
* $pattern **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### consume

    mixed Malamute\Consumer::consume(mixed $stream, mixed $pattern)



...

* Visibility: **public**


#### Arguments
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;
* $pattern **mixed** - &lt;p&gt;...&lt;/p&gt;



### run

    mixed Malamute\Consumer::run(mixed $endpoint, mixed $stream, string $pattern, callable $callback)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;
* $pattern **string** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### headers

    mixed Malamute\Consumer::headers(mixed $header)



...

* Visibility: **public**


#### Arguments
* $header **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### recv

    mixed Malamute\Consumer::recv()



...

* Visibility: **public**




### recv_string

    mixed Malamute\Consumer::recv_string()



...

* Visibility: **public**




### recv_picture

    mixed Malamute\Consumer::recv_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



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



