Majordomo\Broker
===============

Broker

...


* Class name: Broker
* Namespace: Majordomo
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md), [IZEmitter](IZEmitter.md)






Methods
-------


### __construct

    \Majordomo\Broker Majordomo\Broker::__construct(mixed $endpoint, mixed $verbose)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed Majordomo\Broker::set_verbose()



...

* Visibility: **public**




### run

    mixed Majordomo\Broker::run(mixed $endpoint, mixed $verbose)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### bind

    mixed Majordomo\Broker::bind(mixed $endpoint)



...

* Visibility: **public**


#### Arguments
* $endpoint **mixed** - &lt;p&gt;...&lt;/p&gt;



### load_config

    mixed Majordomo\Broker::load_config(mixed $filename)



...

* Visibility: **public**


#### Arguments
* $filename **mixed** - &lt;p&gt;...&lt;/p&gt;



### save_config

    mixed Majordomo\Broker::save_config(mixed $filename)



...

* Visibility: **public**


#### Arguments
* $filename **mixed** - &lt;p&gt;...&lt;/p&gt;



### set_config

    mixed Majordomo\Broker::set_config(mixed $key, mixed $value)



...

* Visibility: **public**


#### Arguments
* $key **mixed** - &lt;p&gt;...&lt;/p&gt;
* $value **mixed** - &lt;p&gt;...&lt;/p&gt;



### start

    mixed Majordomo\Broker::start()



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

    mixed Majordomo\Broker::recv()



...

* Visibility: **public**




### recv_string

    mixed Majordomo\Broker::recv_string()



...

* Visibility: **public**




### recv_picture

    mixed Majordomo\Broker::recv_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### recv_msgpack

    mixed Majordomo\Broker::recv_msgpack()



...

* Visibility: **public**




### recv_zipped

    mixed Majordomo\Broker::recv_zipped()



...

* Visibility: **public**




### send

    mixed Majordomo\Broker::send(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_string

    mixed Majordomo\Broker::send_string(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_picture

    mixed Majordomo\Broker::send_picture(mixed $picture)



...

* Visibility: **public**


#### Arguments
* $picture **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_msgpack

    mixed Majordomo\Broker::send_msgpack(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_zipped

    mixed Majordomo\Broker::send_zipped(mixed $data)



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



