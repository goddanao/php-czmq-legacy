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



### run

    mixed Malamute\Producer::run(mixed $endpoint, mixed $stream, callable $callback)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### send

    mixed Malamute\Producer::send(mixed $subject, mixed $data)



...

* Visibility: **public**


#### Arguments
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_string

    mixed Malamute\Producer::send_string(mixed $subject, mixed $data)



...

* Visibility: **public**


#### Arguments
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_picture

    mixed Malamute\Producer::send_picture(mixed $subject, mixed $picture, mixed $data)



...

* Visibility: **public**


#### Arguments
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



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



