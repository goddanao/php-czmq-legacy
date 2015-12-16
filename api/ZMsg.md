ZMsg
===============

ZMsg

Multipart message handling


* Class name: ZMsg
* Namespace: 







Methods
-------


### __construct

    \ZMsg ZMsg::__construct()





* Visibility: **public**




### append

    mixed ZMsg::append(\ZFrame $frame)



...

* Visibility: **public**


#### Arguments
* $frame **[ZFrame](ZFrame.md)**



### prepend

    mixed ZMsg::prepend(\ZFrame $frame)



...

* Visibility: **public**


#### Arguments
* $frame **[ZFrame](ZFrame.md)**



### pop

    \ZFrame ZMsg::pop()



...

* Visibility: **public**




### append_string

    mixed ZMsg::append_string(string $data)



...

* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;...&lt;/p&gt;



### prepend_string

    mixed ZMsg::prepend_string(string $data)



...

* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;...&lt;/p&gt;



### pop_string

    string ZMsg::pop_string()



...

* Visibility: **public**




### append_picture

    mixed ZMsg::append_picture(string $picture)



...

* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;...&lt;/p&gt;



### prepend_picture

    mixed ZMsg::prepend_picture(string $picture)



...

* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;...&lt;/p&gt;



### pop_picture

    array ZMsg::pop_picture(string $picture)



...

* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;...&lt;/p&gt;



### append_zipped

    mixed ZMsg::append_zipped(mixed $zipped)



...

* Visibility: **public**


#### Arguments
* $zipped **mixed** - &lt;p&gt;...&lt;/p&gt;



### prepend_zipped

    mixed ZMsg::prepend_zipped(mixed $zipped)



...

* Visibility: **public**


#### Arguments
* $zipped **mixed** - &lt;p&gt;...&lt;/p&gt;



### pop_zipped

    mixed ZMsg::pop_zipped(mixed $zipped)



...

* Visibility: **public**


#### Arguments
* $zipped **mixed** - &lt;p&gt;...&lt;/p&gt;



### append_msgpack

    mixed ZMsg::append_msgpack(mixed $msgpack)



...

* Visibility: **public**


#### Arguments
* $msgpack **mixed** - &lt;p&gt;...&lt;/p&gt;



### prepend_msgpack

    mixed ZMsg::prepend_msgpack(mixed $msgpack)



...

* Visibility: **public**


#### Arguments
* $msgpack **mixed** - &lt;p&gt;...&lt;/p&gt;



### pop_msgpack

    mixed ZMsg::pop_msgpack(mixed $msgpack)



...

* Visibility: **public**


#### Arguments
* $msgpack **mixed** - &lt;p&gt;...&lt;/p&gt;



### send

    mixed ZMsg::send(\IZSocket $socket)

Send a ZMsg



* Visibility: **public**


#### Arguments
* $socket **[IZSocket](IZSocket.md)**



### remove

    mixed ZMsg::remove(\ZFrame $frame)



...

* Visibility: **public**


#### Arguments
* $frame **[ZFrame](ZFrame.md)**



### first

    \ZFrame ZMsg::first()



...

* Visibility: **public**




### next

    \ZFrame ZMsg::next()



...

* Visibility: **public**




### last

    \ZFrame ZMsg::last()



...

* Visibility: **public**




### get_size

    integer ZMsg::get_size()



...

* Visibility: **public**




### get_content_size

    integer ZMsg::get_content_size()



...

* Visibility: **public**




### save

    mixed ZMsg::save(mixed $file)



...

* Visibility: **public**


#### Arguments
* $file **mixed** - &lt;p&gt;...&lt;/p&gt;



### load

    mixed ZMsg::load(mixed $file)



...

* Visibility: **public**


#### Arguments
* $file **mixed** - &lt;p&gt;...&lt;/p&gt;



### dump

    mixed ZMsg::dump()



...

* Visibility: **public**



