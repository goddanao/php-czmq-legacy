FileMq\Client
===============

Client

FileMQ Client


* Class name: Client
* Namespace: FileMq
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \FileMq\Client FileMq\Client::__construct(string $endpoint, string $local_path, integer $timeout)

Create e new instance.



* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;FileMQ Server endpoint.&lt;/p&gt;
* $local_path **string** - &lt;p&gt;Local folder to sync with server.&lt;/p&gt;
* $timeout **integer** - &lt;p&gt;Connect timeout. 0 means infinite. (optional)&lt;/p&gt;



### run

    mixed FileMq\Client::run(mixed $endpoint, mixed $local_path, mixed $remote_path, mixed $timeout)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $local_path **mixed** - &lt;p&gt;...&lt;/p&gt;
* $remote_path **mixed** - &lt;p&gt;...&lt;/p&gt;
* $timeout **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### subscribe

    mixed FileMq\Client::subscribe(string $remote_path)



...

* Visibility: **public**


#### Arguments
* $remote_path **string** - &lt;p&gt;...&lt;/p&gt;



### send

    mixed FileMq\Client::send(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv

    \ZMsg FileMq\Client::recv()

Recieve a ZMsg.



* Visibility: **public**




### send_string

    mixed FileMq\Client::send_string(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_string

    mixed FileMq\Client::recv_string()



...

* Visibility: **public**




### send_picture

    mixed FileMq\Client::send_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_picture

    mixed FileMq\Client::recv_picture(mixed $picture)



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



