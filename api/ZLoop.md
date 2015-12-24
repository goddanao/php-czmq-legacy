ZLoop
===============

ZLoop

ZeroMQ Loop


* Class name: ZLoop
* Namespace: 







Methods
-------


### __construct

    \ZLoop ZLoop::__construct()



...

* Visibility: **public**




### set_verbose

    mixed ZLoop::set_verbose()

Enable verbose mode, debug outputs are shown.



* Visibility: **public**




### set_max_timers

    mixed ZLoop::set_max_timers(integer $max_timers)



...

* Visibility: **public**


#### Arguments
* $max_timers **integer** - &lt;p&gt;...&lt;/p&gt;



### start

    mixed ZLoop::start()



...

* Visibility: **public**




### stop

    mixed ZLoop::stop()



...

* Visibility: **public**




### add

    mixed ZLoop::add(integer|resource|\IZDescriptor|\IZSocket $pollitem, callable $callback, integer $mode)



...

* Visibility: **public**


#### Arguments
* $pollitem **integer|resource|[IZDescriptor](IZDescriptor.md)|[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;
* $callback **callable** - &lt;p&gt;...&lt;/p&gt;
* $mode **integer** - &lt;p&gt;... (optional)&lt;/p&gt;



### remove

    mixed ZLoop::remove(integer|resource|\IZDescriptor|\IZSocket $pollitem)



...

* Visibility: **public**


#### Arguments
* $pollitem **integer|resource|[IZDescriptor](IZDescriptor.md)|[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;



### add_timer

    integer ZLoop::add_timer(integer $timeout, callable $callback, integer $repeat)

Add a repeating timer with a callback. Return a timer_id.



* Visibility: **public**


#### Arguments
* $timeout **integer** - &lt;p&gt;Timeout ms.&lt;/p&gt;
* $callback **callable** - &lt;p&gt;The callaback.&lt;/p&gt;
* $repeat **integer** - &lt;p&gt;How many times the timer will repeat. (optional)&lt;/p&gt;



### remove_timer

    mixed ZLoop::remove_timer(integer $timer_id)

Remove the timer



* Visibility: **public**


#### Arguments
* $timer_id **integer** - &lt;p&gt;The timer_id returned form add_timer.&lt;/p&gt;



### ignore_interrupts

    mixed ZLoop::ignore_interrupts()



...

* Visibility: **public**



