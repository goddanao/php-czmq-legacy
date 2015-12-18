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

Enable verbose mode debug outputs are shown.



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

Recieve next message from the socket.



* Visibility: **public**




### recv_string

    string Majordomo\Client::recv_string()

Recieve a message and pop first frame as string.



* Visibility: **public**




### recv_picture

    mixed Majordomo\Client::recv_picture(string $picture)

Recieve a message and pop frames as indicated in the picture format specified.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to extract from message.&lt;/p&gt;



### recv_msgpack

    mixed Majordomo\Client::recv_msgpack()

Recieve a message and pop first frame decoding with MsgPack.



* Visibility: **public**




### recv_zipped

    mixed Majordomo\Client::recv_zipped()

Recieve a message and pop first frame decoding with ZLib.



* Visibility: **public**




### send

    mixed Majordomo\Client::send(mixed $data)

Send message.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;Data to send.&lt;/p&gt;



### send_string

    mixed Majordomo\Client::send_string(string $data)

Send a one frame only message with a string.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;The string to send&lt;/p&gt;



### send_picture

    mixed Majordomo\Client::send_picture(string $picture)

Send a message composed by data frames as specified in the picture format.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to push in message.&lt;/p&gt;



### send_msgpack

    mixed Majordomo\Client::send_msgpack(mixed $data)

Send a one frame only message encoded with MsgPack.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;The data to send.&lt;/p&gt;



### send_zipped

    mixed Majordomo\Client::send_zipped(mixed $data)

Send a one frame only message encoded with ZLib.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;The data to be encoded.&lt;/p&gt;



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



