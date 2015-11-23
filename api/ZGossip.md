ZGossip
===============

ZGossip

Decentralized configuration management.


* Class name: ZGossip
* Namespace: 
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed ZGossip::__construct()

ZGossip::__construct



* Visibility: **public**




### set_verbose

    mixed ZGossip::set_verbose()

ZGossip::set_verbose

Enable verbose logging of commands and activity.

* Visibility: **public**




### configure

    mixed ZGossip::configure($filename)

ZGossip::configure

...

* Visibility: **public**


#### Arguments
* $filename **mixed**



### bind

    mixed ZGossip::bind($endpoint)

ZGossip::bind

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**



### connect

    mixed ZGossip::connect($endpoint)

ZGossip::connect

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**



### set

    mixed ZGossip::set($property, $value)

ZGossip::set

...

* Visibility: **public**


#### Arguments
* $property **mixed**
* $value **mixed**



### publish

    mixed ZGossip::publish($property, $value)

ZGossip::publish

...

* Visibility: **public**


#### Arguments
* $property **mixed**
* $value **mixed**



### count

    mixed ZGossip::count()

ZGossip::count

...

* Visibility: **public**




### recv

    \FileMq\ZMsg ZGossip::recv()

ZGossip::recv

Recieve a ZMsg.

* Visibility: **public**




### get_fd

    integer IZDescriptor::get_fd()

IZDescriptor::get_fd

Get the underlying File Descriptor.

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    \FileMq\ZSocket IZSocket::get_socket()

IZSocket::get_socket

Get the underlying ZSocket.

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)



