ZProxy
===============

ZProxy

Run a steerable proxy in background. The proxy switches messages between a frontend socket and a backend socket. Supports pause / resume.


* Class name: ZProxy
* Namespace: 
* This class implements: [IZActor](IZActor.md), [IZDescriptor](IZDescriptor.md), [IZSocket](IZSocket.md), [IZEmitter](IZEmitter.md)






Methods
-------


### __construct

    \ZProxy ZProxy::__construct(mixed $verbose)





* Visibility: **public**


#### Arguments
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed ZProxy::set_verbose()

Enable verbose mode, debug outputs are shown.



* Visibility: **public**




### pause

    mixed ZProxy::pause()

Put the proxy in pause.



* Visibility: **public**




### resume

    mixed ZProxy::resume()

Resume the proxy activity.



* Visibility: **public**




### recv

    \ZMsg ZProxy::recv()

Recieve next message from the socket.



* Visibility: **public**




### set_frontend

    mixed ZProxy::set_frontend(string $type, string $endpoint)

Set frontend socket type and endpoint.



* Visibility: **public**


#### Arguments
* $type **string** - &lt;p&gt;Frontend socket type.&lt;/p&gt;
* $endpoint **string** - &lt;p&gt;Frontend endpoint.&lt;/p&gt;



### set_backend

    mixed ZProxy::set_backend(string $type, string $endpoint)

Set backend socket type and endpoint.



* Visibility: **public**


#### Arguments
* $type **string** - &lt;p&gt;Backend socket type.&lt;/p&gt;
* $endpoint **string** - &lt;p&gt;Backend endpoint.&lt;/p&gt;



### set_capture

    mixed ZProxy::set_capture(string $endpoint)

Capture all proxied messages; these are delivered to the application via an inproc PULL socket
* that you have already bound to the specified endpoint



* Visibility: **public**


#### Arguments
* $endpoint **string** - &lt;p&gt;Capture endpoint.&lt;/p&gt;



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



