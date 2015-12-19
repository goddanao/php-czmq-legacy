ZBeacon
===============

ZBeacon

...


* Class name: ZBeacon
* Namespace: 
* This class implements: [IZActor](IZActor.md), [IZDescriptor](IZDescriptor.md), [IZSocket](IZSocket.md), [IZEmitter](IZEmitter.md)






Methods
-------


### __construct

    \ZBeacon ZBeacon::__construct(mixed $verbose)



...

* Visibility: **public**


#### Arguments
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed ZBeacon::set_verbose()

Enable verbose mode, debug outputs are shown.



* Visibility: **public**




### set_port

    string ZBeacon::set_port(integer $port)

Configure Udp port number. Return hostname or false if cannot bind.



* Visibility: **public**


#### Arguments
* $port **integer** - &lt;p&gt;...&lt;/p&gt;



### subscribe

    mixed ZBeacon::subscribe(string $filter)



...

* Visibility: **public**


#### Arguments
* $filter **string** - &lt;p&gt;...&lt;/p&gt;



### unsubscribe

    mixed ZBeacon::unsubscribe()



...

* Visibility: **public**




### publish

    mixed ZBeacon::publish(string $data, integer $interval)



...

* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;...&lt;/p&gt;
* $interval **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### silence

    mixed ZBeacon::silence()



...

* Visibility: **public**




### recv

    \ZMsg ZBeacon::recv()

Recieve next message from the socket.



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



