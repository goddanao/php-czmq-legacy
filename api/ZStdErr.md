ZStdErr
===============

ZStdErr

Simple wrap for StdErr.


* Class name: ZStdErr
* Namespace: 
* This class implements: [IZDescriptor](IZDescriptor.md)






Methods
-------


### recv

    \ZMsg ZStdErr::recv()

Recieve next message from the socket.



* Visibility: **public**




### send

    mixed ZStdErr::send(mixed $data)

Send message.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;Data to send.&lt;/p&gt;



### get_fd

    integer IZDescriptor::get_fd()

Get the underlying File Descriptor.



* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)



