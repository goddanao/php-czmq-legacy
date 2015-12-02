Majordomo\V1\Client
===============

Client

...


* Class name: Client
* Namespace: Majordomo\V1
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \Majordomo\V1\Client Majordomo\V1\Client::__construct()



...

* Visibility: **public**




### call

    \ZMsg Majordomo\V1\Client::call(string $service, array|string|\ZFrame|\ZMsg $data)



...

* Visibility: **public**


#### Arguments
* $service **string** - &lt;p&gt;...&lt;/p&gt;
* $data **array|string|[ZFrame](ZFrame.md)|[ZMsg](ZMsg.md)** - &lt;p&gt;... (optional)&lt;/p&gt;



### call_async

    mixed Majordomo\V1\Client::call_async(string $service, array|string|\ZFrame|\ZMsg $data)



...

* Visibility: **public**


#### Arguments
* $service **string** - &lt;p&gt;...&lt;/p&gt;
* $data **array|string|[ZFrame](ZFrame.md)|[ZMsg](ZMsg.md)** - &lt;p&gt;... (optional)&lt;/p&gt;



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



