Malamute\Client
===============

Client

...


* Class name: Client
* Namespace: Malamute
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Malamute\Client Malamute\Client::__construct(mixed $endpoint, mixed $address, mixed $timeout)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $address **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $timeout **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed Malamute\Client::set_verbose()



...

* Visibility: **public**




### connect

    mixed Malamute\Client::connect(mixed $endpoint, mixed $address, mixed $timeout)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $address **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $timeout **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### header

    mixed Malamute\Client::header()



...

* Visibility: **public**




### content

    mixed Malamute\Client::content()



...

* Visibility: **public**




### set_producer

    mixed Malamute\Client::set_producer(mixed $stream)



...

* Visibility: **public**


#### Arguments
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;



### set_worker

    mixed Malamute\Client::set_worker(mixed $address, mixed $patern)



...

* Visibility: **public**


#### Arguments
* $address **mixed** - &lt;p&gt;...&lt;/p&gt;
* $patern **mixed** - &lt;p&gt;...&lt;/p&gt;



### set_consumer

    mixed Malamute\Client::set_consumer(mixed $stream, mixed $patern)



...

* Visibility: **public**


#### Arguments
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;
* $patern **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_stream

    mixed Malamute\Client::send_stream(mixed $subject)



...

* Visibility: **public**


#### Arguments
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_mailbox

    mixed Malamute\Client::send_mailbox(mixed $address, mixed $payload, mixed $timeout, mixed $subject, mixed $tracker)



...

* Visibility: **public**


#### Arguments
* $address **mixed** - &lt;p&gt;...&lt;/p&gt;
* $payload **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $timeout **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $subject **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $tracker **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### send_service

    mixed Malamute\Client::send_service(mixed $address, mixed $subject, mixed $payload, mixed $timeout, mixed $tracker)



...

* Visibility: **public**


#### Arguments
* $address **mixed** - &lt;p&gt;...&lt;/p&gt;
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;
* $payload **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $timeout **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $tracker **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### recv

    \ZMsg Malamute\Client::recv()

Recieve a ZMsg.



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



