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




### recv

    \ZMsg ZUdp::recv()

Recieve a ZMsg.



* Visibility: **public**




### recv_string

    mixed ZUdp::recv_string()



...

* Visibility: **public**




### recv_picture

    mixed ZUdp::recv_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_msgpack

    mixed ZUdp::recv_msgpack()



...

* Visibility: **public**




### recv_zipped

    mixed ZUdp::recv_zipped()



...

* Visibility: **public**




### send

    mixed ZUdp::send(mixed $data)

Send a ZMsg.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_string

    mixed ZUdp::send_string(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_picture

    mixed ZUdp::send_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_msgpack

    mixed ZUdp::send_msgpack(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_zipped

    mixed ZUdp::send_zipped(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### get_fd

    integer IZDescriptor::get_fd()

Get the underlying File Descriptor.



* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)



