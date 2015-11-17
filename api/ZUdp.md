ZUdp
===============

ZUdp

Udp low level class


* Class name: ZUdp
* Namespace: 
* This class implements: [IZSocket](IZSocket.md)






Methods
-------


### \ZUdp::__construct()

```
mixed ZUdp::\ZUdp::__construct()(string $interface, integer $port, boolean $routable)
```

ZUdp::__construct



* Visibility: **public**

#### Arguments

* $interface **string** - &lt;p&gt;The interface name to bind (optional)&lt;/p&gt;
* $port **integer** - &lt;p&gt;The port number to bind (optional)&lt;/p&gt;
* $routable **boolean** - &lt;p&gt;uses multicast (not yet implemented), else uses broadcast (default) (optional)&lt;/p&gt;



### \ZUdp::set_verbose()

```
mixed ZUdp::\ZUdp::set_verbose()()
```

ZUdp::set_verbose

Verbose logging

* Visibility: **public**



### \ZUdp::send()

```
mixed ZUdp::\ZUdp::send()()
```

ZUdp::send

Send a ZMsg over Udp

* Visibility: **public**



### \ZUdp::recv()

```
\FileMq\ZMsg ZUdp::\ZUdp::recv()()
```

ZUdp::recv

Recieve ZMsg over Udp

* Visibility: **public**


