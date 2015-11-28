Malamute\Broker
===============

Broker

...


* Class name: Broker
* Namespace: Malamute
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Malamute\Broker Malamute\Broker::__construct()



...

* Visibility: **public**




### set_verbose

    mixed Malamute\Broker::set_verbose()



...

* Visibility: **public**




### bind

    mixed Malamute\Broker::bind(string $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### load_config

    mixed Malamute\Broker::load_config(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### save_config

    mixed Malamute\Broker::save_config(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### set_config

    mixed Malamute\Broker::set_config(string $key, string $value)



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



