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

    \Malamute\Worker Malamute\Worker::__construct(string $endpoint, mixed $name, string $pattern)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $name **mixed** - &lt;p&gt;...&lt;/p&gt;
* $pattern **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### run

    mixed Malamute\Worker::run(mixed $endpoint, mixed $name, mixed $pattern, callable $callback)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $name **mixed** - &lt;p&gt;...&lt;/p&gt;
* $pattern **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### headers

    mixed Malamute\Worker::headers(mixed $header)



...

* Visibility: **public**


#### Arguments
* $header **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### get_client

    \Malamute\Client Malamute\Worker::get_client()

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



