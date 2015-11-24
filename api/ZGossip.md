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

    mixed ZGossip::configure(mixed $filename)

ZGossip::configure

...

* Visibility: **public**


#### Arguments
* $filename **mixed** - &lt;p&gt;...&lt;/p&gt;



### bind

    mixed ZGossip::bind(mixed $endpoint)

ZGossip::bind

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### connect

    mixed ZGossip::connect(mixed $endpoint)

ZGossip::connect

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### set

    mixed ZGossip::set(mixed $property, mixed $value)

ZGossip::set

...

* Visibility: **public**


#### Arguments
* $property **mixed** - &lt;p&gt;...&lt;/p&gt;
* $value **mixed** - &lt;p&gt;...&lt;/p&gt;



### publish

    mixed ZGossip::publish(mixed $property, mixed $value)

ZGossip::publish

...

* Visibility: **public**


#### Arguments
* $property **mixed** - &lt;p&gt;...&lt;/p&gt;
* $value **mixed** - &lt;p&gt;...&lt;/p&gt;



### count

    mixed ZGossip::count()

ZGossip::count

...

* Visibility: **public**




### recv

    \ZMsg ZGossip::recv()

ZGossip::recv

Recieve a ZMsg.

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



