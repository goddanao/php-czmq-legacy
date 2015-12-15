Majordomo\Titanic
===============

Titanic

...


* Class name: Titanic
* Namespace: Majordomo
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Majordomo\Titanic Majordomo\Titanic::__construct(string $endpoint, \FileMq\ITitanicStorage $storage, integer $threads)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $storage **FileMq\ITitanicStorage** - &lt;p&gt;... (optional)&lt;/p&gt;
* $threads **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### run

    mixed Majordomo\Titanic::run(string $endpoint, \FileMq\ITitanicStorage $storage, integer $threads)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $storage **FileMq\ITitanicStorage** - &lt;p&gt;... (optional)&lt;/p&gt;
* $threads **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### recv

    mixed Majordomo\Titanic::recv()



...

* Visibility: **public**




### recv_string

    mixed Majordomo\Titanic::recv_string()



...

* Visibility: **public**




### recv_picture

    mixed Majordomo\Titanic::recv_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_msgpack

    mixed Majordomo\Titanic::recv_msgpack()



...

* Visibility: **public**




### recv_zipped

    mixed Majordomo\Titanic::recv_zipped()



...

* Visibility: **public**




### send

    mixed Majordomo\Titanic::send(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_string

    mixed Majordomo\Titanic::send_string(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_picture

    mixed Majordomo\Titanic::send_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_msgpack

    mixed Majordomo\Titanic::send_msgpack(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_zipped

    mixed Majordomo\Titanic::send_zipped(mixed $data)



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



