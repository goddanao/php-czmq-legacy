FileMq\Server
===============

Server

...


* Class name: Server
* Namespace: FileMq
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed FileMq\Server::__construct()

Server::__construct

...

* Visibility: **public**




### set_verbose

    mixed FileMq\Server::set_verbose()

Server::set_verbose

...

* Visibility: **public**




### load_config

    mixed FileMq\Server::load_config()

Server::load_config

...

* Visibility: **public**




### set_config

    mixed FileMq\Server::set_config()

Server::set_config

...

* Visibility: **public**




### save_config

    mixed FileMq\Server::save_config()

Server::save_config

...

* Visibility: **public**




### bind

    mixed FileMq\Server::bind()

Server::bind

...

* Visibility: **public**




### publish

    mixed FileMq\Server::publish(mixed $local_path, mixed $alias)

Server::publish

...

* Visibility: **public**


#### Arguments
* $local_path **mixed** - &lt;p&gt;...&lt;/p&gt;
* $alias **mixed** - &lt;p&gt;...&lt;/p&gt;



### get_fd

    mixed IZDescriptor::get_fd()

IZDescriptor::get_fd

...

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    mixed IZSocket::get_socket()

IZSocket::get_socket

...

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)




### recv

    \ZMsg FileMq\Server::recv()

Server::recv

Recieve a ZMsg.

* Visibility: **public**



