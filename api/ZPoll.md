ZPoll
===============

ZPoll

...


* Class name: ZPoll
* Namespace: 







Methods
-------


### set_verbose

    mixed ZPoll::set_verbose(boolean $verbose)



...

* Visibility: **public**


#### Arguments
* $verbose **boolean** - &lt;p&gt;... (optional)&lt;/p&gt;



### add

    mixed ZPoll::add(integer|resource|\IZDescriptor|\IZSocket $pollitem, integer $mode)



...

* Visibility: **public**


#### Arguments
* $pollitem **integer|resource|[IZDescriptor](IZDescriptor.md)|[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;
* $mode **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### has

    mixed ZPoll::has(integer|resource|\IZDescriptor|\IZSocket $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **integer|resource|[IZDescriptor](IZDescriptor.md)|[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;



### remove

    mixed ZPoll::remove(integer|resource|\IZDescriptor|\IZSocket $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **integer|resource|[IZDescriptor](IZDescriptor.md)|[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;



### check_for

    mixed ZPoll::check_for(integer|resource|\IZDescriptor|\IZSocket $pollitem, integer $event)



...

* Visibility: **public**


#### Arguments
* $pollitem **integer|resource|[IZDescriptor](IZDescriptor.md)|[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;
* $event **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### events

    mixed ZPoll::events(integer|resource|\IZDescriptor|\IZSocket $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **integer|resource|[IZDescriptor](IZDescriptor.md)|[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;



### poll_array

    boolean ZPoll::poll_array(array $readers, array $writers, integer $timeout)



...

* Visibility: **public**


#### Arguments
* $readers **array**
* $writers **array**
* $timeout **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### poll

    boolean ZPoll::poll(integer $timeout)



...

* Visibility: **public**


#### Arguments
* $timeout **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### has_input

    boolean ZPoll::has_input(integer|resource|\IZDescriptor|\IZSocket $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **integer|resource|[IZDescriptor](IZDescriptor.md)|[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;



### has_output

    boolean ZPoll::has_output(integer|resource|\IZDescriptor|\IZSocket $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **integer|resource|[IZDescriptor](IZDescriptor.md)|[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;



### has_error

    boolean ZPoll::has_error(integer|resource|\IZDescriptor|\IZSocket $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **integer|resource|[IZDescriptor](IZDescriptor.md)|[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;


