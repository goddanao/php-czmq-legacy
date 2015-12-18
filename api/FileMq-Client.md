FileMq\Client
===============

Client

FileMQ Client


* Class name: Client
* Namespace: FileMq
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md), [IZEmitter](IZEmitter.md)






Methods
-------


### __construct

    \FileMq\Client FileMq\Client::__construct(string $endpoint, string $local_path, integer $timeout)

Create e new instance.



* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;FileMQ Server endpoint.&lt;/p&gt;
* $local_path **string** - &lt;p&gt;Local folder to sync with server.&lt;/p&gt;
* $timeout **integer** - &lt;p&gt;Connect timeout. 0 means infinite. (optional)&lt;/p&gt;



### run

    mixed FileMq\Client::run(mixed $endpoint, mixed $local_path, mixed $remote_path, mixed $timeout)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $local_path **mixed** - &lt;p&gt;...&lt;/p&gt;
* $remote_path **mixed** - &lt;p&gt;...&lt;/p&gt;
* $timeout **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### subscribe

    mixed FileMq\Client::subscribe(string $remote_path)



...

* Visibility: **public**


#### Arguments
* $remote_path **string** - &lt;p&gt;...&lt;/p&gt;



### start

    mixed FileMq\Client::start()



...

* Visibility: **public**




### on

    mixed IZEmitter::on(string $event, callable $listener)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### once

    mixed IZEmitter::once(string $event, callable $listener)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### remove_listener

    mixed IZEmitter::remove_listener(string $event, callable $listener)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### remove_all_listeners

    mixed IZEmitter::remove_all_listeners(string $event)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### listeners

    array|null IZEmitter::listeners(string $event)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;



### emit

    mixed IZEmitter::emit(string $event, array $arguments)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $arguments **array** - &lt;p&gt;...&lt;/p&gt;



### recv

    \ZMsg FileMq\Client::recv()

Recieve a ZMsg.



* Visibility: **public**




### recv_string

    string FileMq\Client::recv_string()

Recieve a message and pop first frame as string.



* Visibility: **public**




### recv_picture

    mixed FileMq\Client::recv_picture(string $picture)

Recieve a message and pop frames as indicated in the picture format specified.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to extract from message.&lt;/p&gt;



### recv_msgpack

    mixed FileMq\Client::recv_msgpack()

Recieve a message and pop first frame decoding with MsgPack.



* Visibility: **public**




### recv_zipped

    mixed FileMq\Client::recv_zipped()

Recieve a message and pop first frame decoding with ZLib.



* Visibility: **public**




### send

    mixed FileMq\Client::send(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_string

    mixed FileMq\Client::send_string(string $data)

Send a one frame only message with a string.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;The string to send&lt;/p&gt;



### send_picture

    mixed FileMq\Client::send_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_msgpack

    mixed FileMq\Client::send_msgpack(mixed $data)

Send a one frame only message encoded with MsgPack.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;The data to send.&lt;/p&gt;



### send_zipped

    mixed FileMq\Client::send_zipped(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



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



