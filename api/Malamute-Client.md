Malamute\Client
===============

Client

...


* Class name: Client
* Namespace: Malamute
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Malamute\Client Malamute\Client::__construct(string $endpoint, string $address, mixed $username, mixed $password)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $address **string** - &lt;p&gt;... (optional)&lt;/p&gt;
* $username **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $password **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### call_async

    mixed Malamute\Client::call_async(mixed $service, mixed $data)



...

* Visibility: **public**


#### Arguments
* $service **mixed** - &lt;p&gt;...&lt;/p&gt;
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### call

    mixed Malamute\Client::call(mixed $service, mixed $data)



...

* Visibility: **public**


#### Arguments
* $service **mixed** - &lt;p&gt;...&lt;/p&gt;
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### headers

    mixed Malamute\Client::headers()



...

* Visibility: **public**




### recv

    \ZMsg Malamute\Client::recv()

Recieve a ZMsg.



* Visibility: **public**




### recv_string

    string Malamute\Client::recv_string()



...

* Visibility: **public**




### recv_picture

    array Malamute\Client::recv_picture(string $picture)



...

* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;...&lt;/p&gt;



### recv_msgpack

    mixed Malamute\Client::recv_msgpack()



...

* Visibility: **public**




### recv_zipped

    mixed Malamute\Client::recv_zipped()



...

* Visibility: **public**




### get_fd

    integer IZDescriptor::get_fd()

Get the underlying File Descriptor.



* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    \ZSocket IZSocket::get_socket()

Get the underlying ZSocket.



* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)



