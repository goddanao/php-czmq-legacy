Majordomo\V1\Broker
===============

Broker

...


* Class name: Broker
* Namespace: Majordomo\V1
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Majordomo\V1\Broker Majordomo\V1\Broker::__construct()



...

* Visibility: **public**




### bind

    mixed Majordomo\V1\Broker::bind(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### set_verbose

    mixed Majordomo\V1\Broker::set_verbose()



...

* Visibility: **public**




### get_status

    mixed Majordomo\V1\Broker::get_status()



...

* Visibility: **public**




### set_capture

    mixed Majordomo\V1\Broker::set_capture(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



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



