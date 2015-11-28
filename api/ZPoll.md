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

    mixed ZPoll::add(\IZDescriptor $socket, integer $mode)



...

* Visibility: **public**


#### Arguments
* $socket **[IZDescriptor](IZDescriptor.md)** - &lt;p&gt;...&lt;/p&gt;
* $mode **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### has

    mixed ZPoll::has(\IZDescriptor $socket)



...

* Visibility: **public**


#### Arguments
* $socket **[IZDescriptor](IZDescriptor.md)** - &lt;p&gt;...&lt;/p&gt;



### remove

    mixed ZPoll::remove(\IZDescriptor $socket)



...

* Visibility: **public**


#### Arguments
* $socket **[IZDescriptor](IZDescriptor.md)** - &lt;p&gt;...&lt;/p&gt;



### check_for

    mixed ZPoll::check_for(\IZDescriptor $socket, integer $event)



...

* Visibility: **public**


#### Arguments
* $socket **[IZDescriptor](IZDescriptor.md)** - &lt;p&gt;...&lt;/p&gt;
* $event **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### events

    mixed ZPoll::events(\IZDescriptor $socket)



...

* Visibility: **public**


#### Arguments
* $socket **[IZDescriptor](IZDescriptor.md)** - &lt;p&gt;...&lt;/p&gt;



### poll

    mixed ZPoll::poll(integer $timeout)



...

* Visibility: **public**


#### Arguments
* $timeout **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### has_input

    boolean ZPoll::has_input(\IZDescriptor $socket)



...

* Visibility: **public**


#### Arguments
* $socket **[IZDescriptor](IZDescriptor.md)** - &lt;p&gt;...&lt;/p&gt;



### has_output

    boolean ZPoll::has_output(\IZDescriptor $socket)



...

* Visibility: **public**


#### Arguments
* $socket **[IZDescriptor](IZDescriptor.md)** - &lt;p&gt;...&lt;/p&gt;



### has_error

    boolean ZPoll::has_error(\IZDescriptor $socket)



...

* Visibility: **public**


#### Arguments
* $socket **[IZDescriptor](IZDescriptor.md)** - &lt;p&gt;...&lt;/p&gt;


