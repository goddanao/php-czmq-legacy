Malamute\Producer
===============

Producer

...


* Class name: Producer
* Namespace: Malamute
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md), [IZEmitter](IZEmitter.md)






Methods
-------


### __construct

    \Malamute\Producer Malamute\Producer::__construct(string $endpoint, string $stream)



...

* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;...&lt;/p&gt;
* $stream **string** - &lt;p&gt;...&lt;/p&gt;



### run

    mixed Malamute\Producer::run(mixed $endpoint, mixed $stream, callable $callback)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $stream **mixed** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### send

    mixed Malamute\Producer::send(mixed $subject, mixed $data)

Send message.



* Visibility: **public**


#### Arguments
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;
* $data **mixed** - &lt;p&gt;Data to send.&lt;/p&gt;



### send_string

    mixed Malamute\Producer::send_string(mixed $subject, string $data)

Send a one frame only message with a string.



* Visibility: **public**


#### Arguments
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;
* $data **string** - &lt;p&gt;The string to send&lt;/p&gt;



### send_picture

    mixed Malamute\Producer::send_picture(mixed $subject, string $picture, mixed $data)

Send a message composed by data frames as specified in the picture format.



* Visibility: **public**


#### Arguments
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to push in message.&lt;/p&gt;
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_msgpack

    mixed Malamute\Producer::send_msgpack(mixed $subject, mixed $data)

Send a one frame only message encoded with MsgPack.



* Visibility: **public**


#### Arguments
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;
* $data **mixed** - &lt;p&gt;The data to send.&lt;/p&gt;



### send_zipped

    mixed Malamute\Producer::send_zipped(mixed $subject, mixed $data)

Send a one frame only message encoded with ZLib.



* Visibility: **public**


#### Arguments
* $subject **mixed** - &lt;p&gt;...&lt;/p&gt;
* $data **mixed** - &lt;p&gt;The data to be encoded.&lt;/p&gt;



### start

    mixed Malamute\Producer::start()



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



