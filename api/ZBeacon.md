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

    mixed ZBeacon::__construct()

ZBeacon::__construct

...

* Visibility: **public**




### set_verbose

    mixed ZBeacon::set_verbose()

ZBeacon::set_verbose

...

* Visibility: **public**




### set_port

    mixed ZBeacon::set_port(mixed $port)

ZBeacon::set_port

...

* Visibility: **public**


#### Arguments
* $port **mixed** - &lt;p&gt;...&lt;/p&gt;



### subscribe

    mixed ZBeacon::subscribe(mixed $filter)

ZBeacon::subscribe

...

* Visibility: **public**


#### Arguments
* $filter **mixed** - &lt;p&gt;...&lt;/p&gt;



### unsubscribe

    mixed ZBeacon::unsubscribe()

ZBeacon::unsubscribe

...

* Visibility: **public**




### publish

    mixed ZBeacon::publish(mixed $data, mixed $interval)

ZBeacon::publish

...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;
* $interval **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### silence

    mixed ZBeacon::silence()

ZBeacon::silence

...

* Visibility: **public**




### recv

    \FileMq\ZMsg ZBeacon::recv()

ZBeacon::recv

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


