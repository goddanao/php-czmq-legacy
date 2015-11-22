ZUdp
===============

ZUdp

Udp low level class


* Class name: ZUdp
* Namespace: 
* This class implements: [ZDescriptor](ZDescriptor.md)






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

Send a ZMsg over Udp

* Visibility: **public**




### recv

    \FileMq\ZMsg ZUdp::recv()

ZUdp::recv

Recieve ZMsg over Udp

* Visibility: **public**




### get_fd

    mixed ZDescriptor::get_fd()

ZDescriptor::get_fd

...

* Visibility: **public**
* This method is defined by [ZDescriptor](ZDescriptor.md)



