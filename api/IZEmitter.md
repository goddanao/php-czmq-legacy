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



...

* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### once

    mixed IZEmitter::once(string $event, callable $listener)



...

* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### removelistener

    mixed IZEmitter::removelistener(string $event, callable $listener)



...

* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### removealllisteners

    mixed IZEmitter::removealllisteners(string $event)



...

* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### listeners

    array IZEmitter::listeners(string $event)



...

* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;



### emit

    mixed IZEmitter::emit(string $event, array $arguments)



...

* Visibility: **public**


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $arguments **array** - &lt;p&gt;...&lt;/p&gt;


