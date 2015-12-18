IZEmitter
===============

IZEmitter

...


* Interface name: IZEmitter
* Namespace: 
* This is an **interface**






Methods
-------


### on

    mixed IZEmitter::on(string $event, callable $listener)

Register an event listener.



* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;Event name.&lt;/p&gt;
* $listener **callable** - &lt;p&gt;Callback.&lt;/p&gt;



### once

    mixed IZEmitter::once(string $event, callable $listener)

Register an event listener to be executed once.



* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;Event name.&lt;/p&gt;
* $listener **callable** - &lt;p&gt;Event callback.&lt;/p&gt;



### remove_listener

    mixed IZEmitter::remove_listener(string $event, callable $listener)

Remove a registered listener.



* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;Event name.&lt;/p&gt;
* $listener **callable** - &lt;p&gt;Event callback.&lt;/p&gt;



### remove_all_listeners

    mixed IZEmitter::remove_all_listeners(string $event)

Remove all registered listeners for the event.



* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;Event name. (optional)&lt;/p&gt;



### listeners

    array|null IZEmitter::listeners(string $event)

Return the listeners registered for the event.



* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;Event name.&lt;/p&gt;



### emit

    mixed IZEmitter::emit(string $event, array $arguments)

Emit an event.



* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;Event name.&lt;/p&gt;
* $arguments **array** - &lt;p&gt;Event arguments.&lt;/p&gt;


