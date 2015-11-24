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





* Visibility: **public**




### set_verbose

    mixed ZGossip::set_verbose()

Enable verbose logging of commands and activity.



* Visibility: **public**




### configure

    mixed ZGossip::configure(mixed $filename)



...

* Visibility: **public**


#### Arguments
* $filename **mixed** - &lt;p&gt;...&lt;/p&gt;



### bind

    mixed ZGossip::bind(mixed $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### connect

    mixed ZGossip::connect(mixed $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### set

    mixed ZGossip::set(mixed $property, mixed $value)



...

* Visibility: **public**


#### Arguments
* $property **mixed** - &lt;p&gt;...&lt;/p&gt;
* $value **mixed** - &lt;p&gt;...&lt;/p&gt;



### publish

    mixed ZGossip::publish(mixed $property, mixed $value)



...

* Visibility: **public**


#### Arguments
* $property **mixed** - &lt;p&gt;...&lt;/p&gt;
* $value **mixed** - &lt;p&gt;...&lt;/p&gt;



### count

    mixed ZGossip::count()



...

* Visibility: **public**




### recv

    \ZMsg ZGossip::recv()

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



