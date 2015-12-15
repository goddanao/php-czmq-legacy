Malamute\Worker
===============

Worker

...


* Class name: Worker
* Namespace: Malamute
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Malamute\Worker Malamute\Worker::__construct(string $endpoint, mixed $name)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $name **mixed** - &lt;p&gt;...&lt;/p&gt;



### run

    mixed Malamute\Worker::run(mixed $endpoint, mixed $name, callable $callback)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $name **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### headers

    mixed Malamute\Worker::headers(mixed $header)



...

* Visibility: **public**


#### Arguments
* $header **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### recv

    mixed Malamute\Worker::recv()



...

* Visibility: **public**




### recv_string

    mixed Malamute\Worker::recv_string()



...

* Visibility: **public**




### recv_picture

    mixed Malamute\Worker::recv_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_msgpack

    mixed Malamute\Worker::recv_msgpack()



...

* Visibility: **public**




### recv_zipped

    mixed Malamute\Worker::recv_zipped()



...

* Visibility: **public**




### send

    mixed Malamute\Worker::send(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_string

    mixed Malamute\Worker::send_string(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_picture

    mixed Malamute\Worker::send_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_msgpack

    mixed Malamute\Worker::send_msgpack(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_zipped

    mixed Malamute\Worker::send_zipped(mixed $data)



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



