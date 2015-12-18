ZUdp
===============

ZUdp

Udp low level class


* Class name: ZUdp
* Namespace: 
* This class implements: [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    \ZUdp ZUdp::__construct(string $interface, integer $port, boolean $routable)





* Visibility: **public**


#### Arguments
* $interface **string** - &lt;p&gt;The interface name to bind (optional)&lt;/p&gt;
* $port **integer** - &lt;p&gt;The port number to bind (optional)&lt;/p&gt;
* $routable **boolean** - &lt;p&gt;uses multicast (not yet implemented), else uses broadcast (default) (optional)&lt;/p&gt;



### set_verbose

    mixed ZUdp::set_verbose()

Enable verbose mode debug outputs are shown.



* Visibility: **public**




### recv

    \ZMsg ZUdp::recv()

Recieve next message from the socket.



* Visibility: **public**




### recv_string

    string ZUdp::recv_string()

Recieve a message and pop first frame as string.



* Visibility: **public**




### recv_picture

    mixed ZUdp::recv_picture(string $picture)

Recieve a message and pop frames as indicated in the picture format specified.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to extract from message.&lt;/p&gt;



### recv_msgpack

    mixed ZUdp::recv_msgpack()

Recieve a message and pop first frame decoding with MsgPack.



* Visibility: **public**




### recv_zipped

    mixed ZUdp::recv_zipped()

Recieve a message and pop first frame decoding with ZLib.



* Visibility: **public**




### send

    mixed ZUdp::send(mixed $data)

Send message.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;Data to send.&lt;/p&gt;



### send_string

    mixed ZUdp::send_string(string $data)

Send a one frame only message with a string.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;The string to send&lt;/p&gt;



### send_picture

    mixed ZUdp::send_picture(string $picture)

Send a message composed by data frames as specified in the picture format.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to push in message.&lt;/p&gt;



### send_msgpack

    mixed ZUdp::send_msgpack(mixed $data)

Send a one frame only message encoded with MsgPack.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;The data to send.&lt;/p&gt;



### send_zipped

    mixed ZUdp::send_zipped(mixed $data)

Send a one frame only message encoded with ZLib.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;The data to be encoded.&lt;/p&gt;



### get_fd

    integer IZDescriptor::get_fd()

Get the underlying File Descriptor.



* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)



