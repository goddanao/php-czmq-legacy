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

    \Majordomo\Titanic Majordomo\Titanic::__construct(string $endpoint, \FileMq\Majordomo\ITitanicStorage $storage, integer $threads)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $storage **FileMq\Majordomo\ITitanicStorage** - &lt;p&gt;... (optional)&lt;/p&gt;
* $threads **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### run

    mixed Majordomo\Titanic::run(string $endpoint, \FileMq\Majordomo\ITitanicStorage $storage, integer $threads)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $storage **FileMq\Majordomo\ITitanicStorage** - &lt;p&gt;... (optional)&lt;/p&gt;
* $threads **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



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



