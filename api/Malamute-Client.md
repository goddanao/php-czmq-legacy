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

    \Malamute\Client Malamute\Client::__construct(string $endpoint, string $address, integer $timeout)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $address **string** - &lt;p&gt;... (optional)&lt;/p&gt;
* $timeout **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed Malamute\Client::set_verbose()



...

* Visibility: **public**




### connect

    mixed Malamute\Client::connect(string $endpoint, string $address, integer $timeout)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;
* $address **string** - &lt;p&gt;... (optional)&lt;/p&gt;
* $timeout **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### header

    mixed Malamute\Client::header()



...

* Visibility: **public**




### content

    mixed Malamute\Client::content()



...

* Visibility: **public**




### set_producer

    mixed Malamute\Client::set_producer(string $stream)



...

* Visibility: **public**


#### Arguments
* $stream **string** - &lt;p&gt;...&lt;/p&gt;



### set_worker

    mixed Malamute\Client::set_worker(string $address, string $patern)



...

* Visibility: **public**


#### Arguments
* $address **string** - &lt;p&gt;...&lt;/p&gt;
* $patern **string** - &lt;p&gt;...&lt;/p&gt;



### set_consumer

    mixed Malamute\Client::set_consumer(string $stream, string $patern)



...

* Visibility: **public**


#### Arguments
* $stream **string** - &lt;p&gt;...&lt;/p&gt;
* $patern **string** - &lt;p&gt;...&lt;/p&gt;



### send_stream

    mixed Malamute\Client::send_stream(string $subject)



...

* Visibility: **public**


#### Arguments
* $subject **string** - &lt;p&gt;...&lt;/p&gt;



### send_mailbox

    mixed Malamute\Client::send_mailbox(string $address, mixed $payload, integer $timeout, string $subject, string $tracker)



...

* Visibility: **public**


#### Arguments
* $address **string** - &lt;p&gt;...&lt;/p&gt;
* $payload **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $timeout **integer** - &lt;p&gt;... (optional)&lt;/p&gt;
* $subject **string** - &lt;p&gt;... (optional)&lt;/p&gt;
* $tracker **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### send_service

    mixed Malamute\Client::send_service(string $address, string $subject, mixed $payload, integer $timeout, string $tracker)



...

* Visibility: **public**


#### Arguments
* $address **string** - &lt;p&gt;...&lt;/p&gt;
* $subject **string** - &lt;p&gt;...&lt;/p&gt;
* $payload **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $timeout **integer** - &lt;p&gt;... (optional)&lt;/p&gt;
* $tracker **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### recv

    \ZMsg Malamute\Client::recv()

Recieve a ZMsg.



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



