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

    mixed Malamute\Client::__construct($endpoint, $address, $timeout)

Client::__construct

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**
* $address **mixed**
* $timeout **mixed**



### set_verbose

    mixed Malamute\Client::set_verbose()

Client::set_verbose

...

* Visibility: **public**




### connect

    mixed Malamute\Client::connect($endpoint, $address, $timeout)

Client::connect

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**
* $address **mixed**
* $timeout **mixed**



### header

    mixed Malamute\Client::header()

Client::header

...

* Visibility: **public**




### content

    mixed Malamute\Client::content()

Client::content

...

* Visibility: **public**




### set_producer

    mixed Malamute\Client::set_producer($stream)

Client::set_producer

...

* Visibility: **public**


#### Arguments
* $stream **mixed**



### set_worker

    mixed Malamute\Client::set_worker($address, $patern)

Client::set_worker

...

* Visibility: **public**


#### Arguments
* $address **mixed**
* $patern **mixed**



### set_consumer

    mixed Malamute\Client::set_consumer($stream, $patern)

Client::set_consumer

...

* Visibility: **public**


#### Arguments
* $stream **mixed**
* $patern **mixed**



### send_stream

    mixed Malamute\Client::send_stream($subject)

Client::send_stream

...

* Visibility: **public**


#### Arguments
* $subject **mixed**



### send_mailbox

    mixed Malamute\Client::send_mailbox($address, $payload, $timeout, $subject, $tracker)

Client::send_mailbox

...

* Visibility: **public**


#### Arguments
* $address **mixed**
* $payload **mixed**
* $timeout **mixed**
* $subject **mixed**
* $tracker **mixed**



### send_service

    mixed Malamute\Client::send_service($address, $subject, $payload, $timeout, $tracker)

Client::send_service

...

* Visibility: **public**


#### Arguments
* $address **mixed**
* $subject **mixed**
* $payload **mixed**
* $timeout **mixed**
* $tracker **mixed**



### recv

    mixed Malamute\Client::recv()

Client::recv

...

* Visibility: **public**




### get_fd

    mixed IZDescriptor::get_fd()

IZDescriptor::get_fd

...

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    mixed IZSocket::get_socket()

IZSocket::get_socket

...

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)



