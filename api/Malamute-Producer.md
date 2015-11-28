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

    \Malamute\Producer Malamute\Producer::__construct(string $endpoint, string $stream)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $stream **string** - &lt;p&gt;...&lt;/p&gt;



### set_timeout

    mixed Malamute\Producer::set_timeout(integer $timeout)



...

* Visibility: **public**


#### Arguments
* $timeout **integer** - &lt;p&gt;...&lt;/p&gt;



### run

    mixed Malamute\Producer::run(string $subject, callable $callback)



...

* Visibility: **public**


#### Arguments
* $subject **string** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### get_client

    \Malamute\Client Malamute\Producer::get_client()

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



