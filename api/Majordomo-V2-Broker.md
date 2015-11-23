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

    mixed Majordomo\V2\Broker::__construct($endpoint, $verbose)

Broker::__construct

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**
* $verbose **mixed**



### set_verbose

    mixed Majordomo\V2\Broker::set_verbose()

Broker::set_verbose

...

* Visibility: **public**




### load_config

    mixed Majordomo\V2\Broker::load_config()

Broker::load_config

...

* Visibility: **public**




### save_config

    mixed Majordomo\V2\Broker::save_config()

Broker::save_config

...

* Visibility: **public**




### set_config

    mixed Majordomo\V2\Broker::set_config()

Broker::set_config

...

* Visibility: **public**




### bind

    mixed Majordomo\V2\Broker::bind()

Broker::bind

...

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



