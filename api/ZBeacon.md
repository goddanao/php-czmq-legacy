ZBeacon
===============

ZBeacon

...


* Class name: ZBeacon
* Namespace: 
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md), [IZEmitter](IZEmitter.md)






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



...

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

Recieve a ZMsg.



* Visibility: **public**




### start

    mixed ZBeacon::start()



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



