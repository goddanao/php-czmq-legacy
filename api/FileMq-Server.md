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

    \FileMq\Server FileMq\Server::__construct()



...

* Visibility: **public**




### set_verbose

    mixed FileMq\Server::set_verbose()



...

* Visibility: **public**




### bind

    mixed FileMq\Server::bind(string $endpoint)

FileMQ Server endpoint to bind.



* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### load_config

    mixed FileMq\Server::load_config(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### save_config

    mixed FileMq\Server::save_config(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### set_config

    mixed FileMq\Server::set_config(string $key, string $value)



...

* Visibility: **public**


#### Arguments
* $key **string** - &lt;p&gt;...&lt;/p&gt;
* $value **string** - &lt;p&gt;...&lt;/p&gt;



### publish

    mixed FileMq\Server::publish(string $local_path, string $alias)



...

* Visibility: **public**


#### Arguments
* $local_path **string** - &lt;p&gt;...&lt;/p&gt;
* $alias **string** - &lt;p&gt;...&lt;/p&gt;



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




### recv

    \ZMsg FileMq\Server::recv()

Recieve a ZMsg.



* Visibility: **public**



