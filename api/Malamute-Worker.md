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

    \Malamute\Worker Malamute\Worker::__construct(string $endpoint, string $address, string $pattern)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $address **string** - &lt;p&gt;...&lt;/p&gt;
* $pattern **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_timeout

    mixed Malamute\Worker::set_timeout(integer $timeout)



...

* Visibility: **public**


#### Arguments
* $timeout **integer** - &lt;p&gt;...&lt;/p&gt;



### run

    mixed Malamute\Worker::run(callable $callback)



...

* Visibility: **public**


#### Arguments
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



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



