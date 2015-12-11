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

    \FileMq\Server FileMq\Server::__construct(mixed $endpoint, array $options)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $options **array** - &lt;p&gt;... (optional)&lt;/p&gt;



### run

    mixed FileMq\Server::run(mixed $endpoint, mixed $path, mixed $alias, array $options)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $path **mixed** - &lt;p&gt;...&lt;/p&gt;
* $alias **mixed** - &lt;p&gt;...&lt;/p&gt;
* $options **array** - &lt;p&gt;... (optional)&lt;/p&gt;



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



### send

    mixed FileMq\Server::send(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv

    \ZMsg FileMq\Server::recv()

Recieve a ZMsg.



* Visibility: **public**




### send_string

    mixed FileMq\Server::send_string(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_string

    mixed FileMq\Server::recv_string()



...

* Visibility: **public**




### send_picture

    mixed FileMq\Server::send_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_picture

    mixed FileMq\Server::recv_picture(mixed $picture)



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



