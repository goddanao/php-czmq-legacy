ZBeacon
===============

ZBeacon

...


* Class name: ZBeacon
* Namespace: 
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \ZBeacon ZBeacon::__construct(mixed $verbose)



...

* Visibility: **public**


#### Arguments
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed ZBeacon::set_verbose()



...

* Visibility: **public**




### set_port

    string ZBeacon::set_port(integer $port)

Configure Udp port number. Return hostname or false if cannot bind.



* Visibility: **public**


#### Arguments
* $port **integer** - &lt;p&gt;...&lt;/p&gt;



### subscribe

    mixed ZBeacon::subscribe(string $filter)



...

* Visibility: **public**


#### Arguments
* $filter **string** - &lt;p&gt;...&lt;/p&gt;



### unsubscribe

    mixed ZBeacon::unsubscribe()



...

* Visibility: **public**




### publish

    mixed ZBeacon::publish(string $data, integer $interval)



...

* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;...&lt;/p&gt;
* $interval **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### silence

    mixed ZBeacon::silence()



...

* Visibility: **public**




### recv

    \ZMsg ZBeacon::recv()

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



