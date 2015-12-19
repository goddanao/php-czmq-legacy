ZGossip
===============

ZGossip

Decentralized configuration management.


* Class name: ZGossip
* Namespace: 
* This class implements: [IZActor](IZActor.md), [IZDescriptor](IZDescriptor.md), [IZSocket](IZSocket.md), [IZEmitter](IZEmitter.md)






Methods
-------


### __construct

    \ZGossip ZGossip::__construct(boolean $verbose)





* Visibility: **public**


#### Arguments
* $verbose **boolean** - &lt;p&gt;Enable verbose mode debug outputs are shown. (optional)&lt;/p&gt;



### set_verbose

    mixed ZGossip::set_verbose()

Enable verbose mode, debug outputs are shown.



* Visibility: **public**




### configure

    mixed ZGossip::configure(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### bind

    boolean ZGossip::bind(string|array $endpoint)

Bind to the specified endpoint(s).



* Visibility: **public**


#### Arguments
* $endpoint **string|array** - &lt;p&gt;Endpoint(s) to bind. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;)&lt;/p&gt;



### connect

    boolean ZGossip::connect(string|array $endpoint)

Connect to the specified endpoint(s).



* Visibility: **public**


#### Arguments
* $endpoint **string|array** - &lt;p&gt;Endpoint(s) to connect to. (see &lt;a href=&quot;http://www.google.com&quot;&gt;Endpoint Format&lt;/a&gt;)&lt;/p&gt;



### set

    mixed ZGossip::set(string $property, string $value)



...

* Visibility: **public**


#### Arguments
* $property **string** - &lt;p&gt;...&lt;/p&gt;
* $value **string** - &lt;p&gt;...&lt;/p&gt;



### publish

    mixed ZGossip::publish(string $property, string $value)



...

* Visibility: **public**


#### Arguments
* $property **string** - &lt;p&gt;...&lt;/p&gt;
* $value **string** - &lt;p&gt;...&lt;/p&gt;



### count

    mixed ZGossip::count()



...

* Visibility: **public**




### recv

    \ZMsg ZGossip::recv()

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



