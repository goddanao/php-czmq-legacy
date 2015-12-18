Majordomo\Worker
===============

Worker

...


* Class name: Worker
* Namespace: Majordomo
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md), [IZEmitter](IZEmitter.md)






Methods
-------


### __construct

    \Majordomo\Worker Majordomo\Worker::__construct(mixed $name, mixed $broker_endpoint)



...

* Visibility: **public**


#### Arguments
* $name **mixed** - &lt;p&gt;...&lt;/p&gt;
* $broker_endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### set_verbose

    mixed Majordomo\Worker::set_verbose()

Enable verbose mode debug outputs are shown.



* Visibility: **public**




### run

    mixed Majordomo\Worker::run(mixed $name, mixed $broker_endpoint, callable $callback)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $name **mixed** - &lt;p&gt;...&lt;/p&gt;
* $broker_endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### start

    mixed Majordomo\Worker::start()



...

* Visibility: **public**




### on

    mixed IZEmitter::on(string $event, callable $listener)

Register an event listener.



* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;Event name.&lt;/p&gt;
* $listener **callable** - &lt;p&gt;Callback.&lt;/p&gt;



### once

    mixed IZEmitter::once(string $event, callable $listener)

Register an event listener to be executed once.



* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;Event name.&lt;/p&gt;
* $listener **callable** - &lt;p&gt;Event callback.&lt;/p&gt;



### remove_listener

    mixed IZEmitter::remove_listener(string $event, callable $listener)

Remove a registered listener.



* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;Event name.&lt;/p&gt;
* $listener **callable** - &lt;p&gt;Event callback.&lt;/p&gt;



### remove_all_listeners

    mixed IZEmitter::remove_all_listeners(string $event)

Remove all registered listeners for the event.



* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;Event name. (optional)&lt;/p&gt;



### listeners

    array|null IZEmitter::listeners(string $event)

Return the listeners registered for the event.



* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;Event name.&lt;/p&gt;



### emit

    mixed IZEmitter::emit(string $event, array $arguments)

Emit an event.



* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;Event name.&lt;/p&gt;
* $arguments **array** - &lt;p&gt;Event arguments.&lt;/p&gt;



### recv

    \ZMsg Majordomo\Worker::recv()

Recieve next message from the socket.



* Visibility: **public**




### recv_string

    string Majordomo\Worker::recv_string()

Recieve a message and pop first frame as string.



* Visibility: **public**




### recv_picture

    mixed Majordomo\Worker::recv_picture(string $picture)

Recieve a message and pop frames as indicated in the picture format specified.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to extract from message.&lt;/p&gt;



### recv_msgpack

    mixed Majordomo\Worker::recv_msgpack()

Recieve a message and pop first frame decoding with MsgPack.



* Visibility: **public**




### recv_zipped

    mixed Majordomo\Worker::recv_zipped()

Recieve a message and pop first frame decoding with ZLib.



* Visibility: **public**




### send

    mixed Majordomo\Worker::send(mixed $data)

Send message.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;Data to send.&lt;/p&gt;



### send_string

    mixed Majordomo\Worker::send_string(string $data)

Send a one frame only message with a string.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;The string to send&lt;/p&gt;



### send_picture

    mixed Majordomo\Worker::send_picture(string $picture)

Send a message composed by data frames as specified in the picture format.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to push in message.&lt;/p&gt;



### send_msgpack

    mixed Majordomo\Worker::send_msgpack(mixed $data)

Send a one frame only message encoded with MsgPack.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;The data to send.&lt;/p&gt;



### send_zipped

    mixed Majordomo\Worker::send_zipped(mixed $data)

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



