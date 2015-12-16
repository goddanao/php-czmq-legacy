Majordomo\Client
===============

Client

...


* Class name: Client
* Namespace: Majordomo
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Majordomo\Client Majordomo\Client::__construct(string $broker_endpoint)



...

* Visibility: **public**


#### Arguments
* $broker_endpoint **string** - &lt;p&gt;...&lt;/p&gt;



### set_verbose

    mixed Majordomo\Client::set_verbose()



...

* Visibility: **public**




### call

    \ZMsg Majordomo\Client::call(string $service_name)



...

* Visibility: **public**


#### Arguments
* $service_name **string** - &lt;p&gt;...&lt;/p&gt;



### call_async

    boolean Majordomo\Client::call_async(string $service_name)



...

* Visibility: **public**


#### Arguments
* $service_name **string** - &lt;p&gt;...&lt;/p&gt;



### recv

    \ZMsg Majordomo\Client::recv()



...

* Visibility: **public**




### recv_string

    mixed Majordomo\Client::recv_string()



...

* Visibility: **public**




### recv_picture

    mixed Majordomo\Client::recv_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_msgpack

    mixed Majordomo\Client::recv_msgpack()



...

* Visibility: **public**




### recv_zipped

    mixed Majordomo\Client::recv_zipped()



...

* Visibility: **public**




### send

    mixed Majordomo\Client::send(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_string

    mixed Majordomo\Client::send_string(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_picture

    mixed Majordomo\Client::send_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_msgpack

    mixed Majordomo\Client::send_msgpack(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_zipped

    mixed Majordomo\Client::send_zipped(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



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



