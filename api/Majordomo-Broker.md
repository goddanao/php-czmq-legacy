Majordomo\Broker
===============

Broker

...


* Class name: Broker
* Namespace: Majordomo
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Majordomo\Broker Majordomo\Broker::__construct(mixed $endpoint, mixed $verbose)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed Majordomo\Broker::set_verbose()



...

* Visibility: **public**




### run

    mixed Majordomo\Broker::run(mixed $endpoint, mixed $verbose)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### bind

    mixed Majordomo\Broker::bind(mixed $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### load_config

    mixed Majordomo\Broker::load_config(mixed $filename)



...

* Visibility: **public**


#### Arguments
* $filename **mixed** - &lt;p&gt;...&lt;/p&gt;



### save_config

    mixed Majordomo\Broker::save_config(mixed $filename)



...

* Visibility: **public**


#### Arguments
* $filename **mixed** - &lt;p&gt;...&lt;/p&gt;



### set_config

    mixed Majordomo\Broker::set_config(mixed $key, mixed $value)



...

* Visibility: **public**


#### Arguments
* $key **mixed** - &lt;p&gt;...&lt;/p&gt;
* $value **mixed** - &lt;p&gt;...&lt;/p&gt;



### send

    mixed Majordomo\Broker::send(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv

    mixed Majordomo\Broker::recv()



...

* Visibility: **public**




### send_string

    mixed Majordomo\Broker::send_string(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_string

    mixed Majordomo\Broker::recv_string()



...

* Visibility: **public**




### send_picture

    mixed Majordomo\Broker::send_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_picture

    mixed Majordomo\Broker::recv_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



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



