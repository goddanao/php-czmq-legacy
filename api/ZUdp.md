ZUdp
===============

ZUdp

Udp low level class


* Class name: ZUdp
* Namespace: 
* This class implements: [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed ZUdp::__construct(string $interface, integer $port, boolean $routable)

ZUdp::__construct



* Visibility: **public**


#### Arguments
* $interface **string** - &lt;p&gt;The interface name to bind (optional)&lt;/p&gt;
* $port **integer** - &lt;p&gt;The port number to bind (optional)&lt;/p&gt;
* $routable **boolean** - &lt;p&gt;uses multicast (not yet implemented), else uses broadcast (default) (optional)&lt;/p&gt;



### set_verbose

    mixed ZUdp::set_verbose()

ZUdp::set_verbose

Verbose logging

* Visibility: **public**




### send

    mixed ZUdp::send()

ZUdp::send

Send a ZMsg.

* Visibility: **public**




### recv

    \FileMq\ZMsg ZUdp::recv()

ZUdp::recv

Recieve a ZMsg.

* Visibility: **public**




### get_fd

    integer IZDescriptor::get_fd()

IZDescriptor::get_fd

Get the underlying File Descriptor.

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)



