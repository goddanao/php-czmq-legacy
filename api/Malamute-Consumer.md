Malamute\Consumer
===============

Consumer

...


* Class name: Consumer
* Namespace: Malamute
* This class implements: [IZActor](IZActor.md), [IZDescriptor](IZDescriptor.md), [IZSocket](IZSocket.md), [IZEmitter](IZEmitter.md)






Methods
-------


### __construct

    \Malamute\Consumer Malamute\Consumer::__construct(string $endpoint, string $stream)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $stream **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### consume

    mixed Malamute\Consumer::consume(mixed $stream)



...

* Visibility: **public**


#### Arguments
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;



### headers

    mixed Malamute\Consumer::headers(mixed $header)



...

* Visibility: **public**


#### Arguments
* $header **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



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

    \ZMsg Malamute\Consumer::recv()

Recieve next message from the socket.



* Visibility: **public**




### recv_string

    string Malamute\Consumer::recv_string()

Recieve a message and pop first frame as string.



* Visibility: **public**




### recv_picture

    mixed Malamute\Consumer::recv_picture(string $picture)

Recieve a message and pop frames as indicated in the picture format specified.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to extract from message.&lt;/p&gt;



### recv_msgpack

    mixed Malamute\Consumer::recv_msgpack()

Recieve a message and pop first frame decoding with MsgPack.



* Visibility: **public**




### recv_zipped

    mixed Malamute\Consumer::recv_zipped()

Recieve a message and pop first frame decoding with ZLib.



* Visibility: **public**




### recv_bson

    mixed Malamute\Consumer::recv_bson()



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




### start

    mixed IZActor::start()



...

* Visibility: **public**
* This method is defined by [IZActor](IZActor.md)




### run

    mixed IZActor::run()



...

* Visibility: **public**
* This method is **static**.
* This method is defined by [IZActor](IZActor.md)



