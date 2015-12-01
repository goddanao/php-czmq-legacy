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

    mixed ZPoll::add(mixed $pollitem, integer $mode)



...

* Visibility: **public**


#### Arguments
* $pollitem **mixed** - &lt;p&gt;...&lt;/p&gt;
* $mode **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### has

    mixed ZPoll::has(mixed $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **mixed** - &lt;p&gt;...&lt;/p&gt;



### remove

    mixed ZPoll::remove(mixed $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **mixed** - &lt;p&gt;...&lt;/p&gt;



### check_for

    mixed ZPoll::check_for(mixed $pollitem, integer $event)



...

* Visibility: **public**


#### Arguments
* $pollitem **mixed** - &lt;p&gt;...&lt;/p&gt;
* $event **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### events

    mixed ZPoll::events(mixed $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **mixed** - &lt;p&gt;...&lt;/p&gt;



### poll_array

    mixed ZPoll::poll_array(array $readers, array $writers, mixed $timeout)



...

* Visibility: **public**


#### Arguments
* $readers **array**
* $writers **array**
* $timeout **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### poll

    mixed ZPoll::poll(integer $timeout)



...

* Visibility: **public**


#### Arguments
* $timeout **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### has_input

    boolean ZPoll::has_input(mixed $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **mixed** - &lt;p&gt;...&lt;/p&gt;



### has_output

    boolean ZPoll::has_output(mixed $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **mixed** - &lt;p&gt;...&lt;/p&gt;



### has_error

    boolean ZPoll::has_error(mixed $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **mixed** - &lt;p&gt;...&lt;/p&gt;


