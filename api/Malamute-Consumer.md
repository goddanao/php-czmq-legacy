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
* $stream **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### consume

    mixed Malamute\Consumer::consume(mixed $stream)



...

* Visibility: **public**


#### Arguments
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;



### run

    mixed Malamute\Consumer::run(mixed $endpoint, mixed $stream, callable $callback)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;
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



### recv_msgpack

    mixed Malamute\Consumer::recv_msgpack()



...

* Visibility: **public**




### recv_zipped

    mixed Malamute\Consumer::recv_zipped()



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



