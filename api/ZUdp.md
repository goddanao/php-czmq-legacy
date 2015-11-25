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

    \ZUdp ZUdp::__construct(string $interface, integer $port, boolean $routable)





* Visibility: **public**


#### Arguments
* $interface **string** - &lt;p&gt;The interface name to bind (optional)&lt;/p&gt;
* $port **integer** - &lt;p&gt;The port number to bind (optional)&lt;/p&gt;
* $routable **boolean** - &lt;p&gt;uses multicast (not yet implemented), else uses broadcast (default) (optional)&lt;/p&gt;



### set_verbose

    mixed ZUdp::set_verbose()

Verbose logging



* Visibility: **public**




### send

    mixed ZUdp::send()

Send a ZMsg.



* Visibility: **public**




### recv

    \ZMsg ZUdp::recv()

Recieve a ZMsg.



* Visibility: **public**




### get_fd

    mixed IZDescriptor::get_fd()



...

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)



