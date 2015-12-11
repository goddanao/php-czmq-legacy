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

    \ZGossip ZGossip::__construct(mixed $verbose)





* Visibility: **public**


#### Arguments
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed ZGossip::set_verbose()

Enable verbose logging of commands and activity.



* Visibility: **public**




### configure

    mixed ZGossip::configure(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### bind

    mixed ZGossip::bind(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### connect

    mixed ZGossip::connect(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### set

    mixed ZGossip::set(string $property, string $value)



...

* Visibility: **public**


#### Arguments
* $property **string** - &lt;p&gt;...&lt;/p&gt;
* $value **string** - &lt;p&gt;...&lt;/p&gt;



### publish

    mixed ZGossip::publish(string $property, string $value)



...

* Visibility: **public**


#### Arguments
* $property **string** - &lt;p&gt;...&lt;/p&gt;
* $value **string** - &lt;p&gt;...&lt;/p&gt;



### count

    mixed ZGossip::count()



...

* Visibility: **public**




### recv

    \ZMsg ZGossip::recv()

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



