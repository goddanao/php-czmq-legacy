Malamute\Broker
===============

Broker

...


* Class name: Broker
* Namespace: Malamute
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md), [IZEmitter](IZEmitter.md)






Methods
-------


### __construct

    \Malamute\Broker Malamute\Broker::__construct(mixed $endpoint, array $options)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $options **array** - &lt;p&gt;... (optional)&lt;/p&gt;



### bind

    boolean Malamute\Broker::bind(string|array $endpoint)

Bind to the specified endpoint(s).



* Visibility: **public**


#### Arguments
* $endpoint **string|array** - &lt;p&gt;Endpoint(s) to bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;)&lt;/p&gt;



### run

    mixed Malamute\Broker::run(mixed $endpoint, array $options)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $options **array** - &lt;p&gt;... (optional)&lt;/p&gt;



### load_config

    mixed Malamute\Broker::load_config(string $filename)

Load the configuration data from a file.



* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;File name.&lt;/p&gt;



### save_config

    mixed Malamute\Broker::save_config(string $filename)

Save the configuration data to a file.



* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;File name.&lt;/p&gt;



### set_config

    mixed Malamute\Broker::set_config(string $key, string $value)

Set a config key to a specific value.



* Visibility: **public**


#### Arguments
* $key **string** - &lt;p&gt;Configuration key.&lt;/p&gt;
* $value **string** - &lt;p&gt;Configuration value.&lt;/p&gt;



### start

    mixed Malamute\Broker::start()



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

    \ZMsg Malamute\Broker::recv()

Recieve next message from the socket.



* Visibility: **public**




### recv_string

    string Malamute\Broker::recv_string()

Recieve a message and pop first frame as string.



* Visibility: **public**




### recv_picture

    mixed Malamute\Broker::recv_picture(string $picture)

Recieve a message and pop frames as indicated in the picture format specified.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to extract from message.&lt;/p&gt;



### recv_msgpack

    mixed Malamute\Broker::recv_msgpack()

Recieve a message and pop first frame decoding with MsgPack.



* Visibility: **public**




### recv_zipped

    mixed Malamute\Broker::recv_zipped()

Recieve a message and pop first frame decoding with ZLib.



* Visibility: **public**




### send

    mixed Malamute\Broker::send(mixed $data)

Send message.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;Data to send.&lt;/p&gt;



### send_string

    mixed Malamute\Broker::send_string(string $data)

Send a one frame only message with a string.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;The string to send&lt;/p&gt;



### send_picture

    mixed Malamute\Broker::send_picture(string $picture)

Send a message composed by data frames as specified in the picture format.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to push in message.&lt;/p&gt;



### send_msgpack

    mixed Malamute\Broker::send_msgpack(mixed $data)

Send a one frame only message encoded with MsgPack.



* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;The data to send.&lt;/p&gt;



### send_zipped

    mixed Malamute\Broker::send_zipped(mixed $data)

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



