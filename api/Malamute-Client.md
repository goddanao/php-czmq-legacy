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

    \Malamute\Client Malamute\Client::__construct(string $endpoint, string $address)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $address **string** - &lt;p&gt;... (optional)&lt;/p&gt;



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




### content

    mixed Malamute\Client::content()



...

* Visibility: **public**




### recv

    \ZMsg Malamute\Client::recv()

Recieve a ZMsg.



* Visibility: **public**




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



