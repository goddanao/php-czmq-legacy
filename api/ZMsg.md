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



### append

    mixed ZMsg::append(\ZFrame $frame)



...

* Visibility: **public**


#### Arguments
* $frame **[ZFrame](ZFrame.md)** - &lt;p&gt;...&lt;/p&gt;



### prepend

    mixed ZMsg::prepend(\ZFrame $frame)



...

* Visibility: **public**


#### Arguments
* $frame **[ZFrame](ZFrame.md)** - &lt;p&gt;...&lt;/p&gt;



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




### send

    mixed ZMsg::send(\IZSocket $socket)

Send a ZMsg



* Visibility: **public**


#### Arguments
* $socket **[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;



### remove

    mixed ZMsg::remove(\ZFrame $frame)



...

* Visibility: **public**


#### Arguments
* $frame **[ZFrame](ZFrame.md)** - &lt;p&gt;...&lt;/p&gt;



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




### dump

    mixed ZMsg::dump()



...

* Visibility: **public**



