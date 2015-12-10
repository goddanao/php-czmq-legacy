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

    mixed IZEmitter::on(mixed $event, callable $listener)



...

* Visibility: **public**


#### Arguments
* $event **mixed** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### once

    mixed IZEmitter::once(mixed $event, callable $listener)



...

* Visibility: **public**


#### Arguments
* $event **mixed** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### removelistener

    mixed IZEmitter::removelistener(mixed $event, callable $listener)



...

* Visibility: **public**


#### Arguments
* $event **mixed** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### removealllisteners

    mixed IZEmitter::removealllisteners(mixed $event)



...

* Visibility: **public**


#### Arguments
* $event **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### listeners

    mixed IZEmitter::listeners(mixed $event)



...

* Visibility: **public**


#### Arguments
* $event **mixed** - &lt;p&gt;...&lt;/p&gt;



### emit

    mixed IZEmitter::emit(mixed $event, array $arguments)



...

* Visibility: **public**


#### Arguments
* $event **mixed** - &lt;p&gt;...&lt;/p&gt;
* $arguments **array** - &lt;p&gt;...&lt;/p&gt;


