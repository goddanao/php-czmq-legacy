Majordomo\V2\Broker
===============

Broker

...


* Class name: Broker
* Namespace: Majordomo\V2
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Majordomo\V2\Broker Majordomo\V2\Broker::__construct(string $endpoint, boolean $verbose)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;... (optional)&lt;/p&gt;
* $verbose **boolean** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed Majordomo\V2\Broker::set_verbose()



...

* Visibility: **public**




### bind

    mixed Majordomo\V2\Broker::bind(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### load_config

    mixed Majordomo\V2\Broker::load_config(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### save_config

    mixed Majordomo\V2\Broker::save_config(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### set_config

    mixed Majordomo\V2\Broker::set_config(string $key, string $value)



...

* Visibility: **public**


#### Arguments
* $key **string** - &lt;p&gt;...&lt;/p&gt;
* $value **string** - &lt;p&gt;...&lt;/p&gt;



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



