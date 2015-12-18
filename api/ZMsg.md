ZMsg
===============

ZMsg

Multipart message handling


* Class name: ZMsg
* Namespace: 
* This class implements: ArrayAccess, Countable, Traversable






Methods
-------


### __construct

    \ZMsg ZMsg::__construct()





* Visibility: **public**




### append

    mixed ZMsg::append(\ZFrame $frame)

Push a frame at the end of the message.



* Visibility: **public**


#### Arguments
* $frame **[ZFrame](ZFrame.md)**



### prepend

    mixed ZMsg::prepend(\ZFrame $frame)

Add a frame at the top of the message.



* Visibility: **public**


#### Arguments
* $frame **[ZFrame](ZFrame.md)**



### pop

    \ZFrame|null ZMsg::pop()

Pop next frame in message.



* Visibility: **public**




### append_string

    mixed ZMsg::append_string(string $data)

Push a string frame at the end of the message.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;Data to append.&lt;/p&gt;



### prepend_string

    mixed ZMsg::prepend_string(string $data)

Add a string frame at the top of the message.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;Data to prepend.&lt;/p&gt;



### pop_string

    string|null ZMsg::pop_string()

Pop next frame in message as string.



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

    mixed ZMsg::pop_zipped()



...

* Visibility: **public**




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

    mixed ZMsg::pop_msgpack()



...

* Visibility: **public**




### send

    mixed ZMsg::send(\IZSocket $socket)

Send message.



* Visibility: **public**


#### Arguments
* $socket **[IZSocket](IZSocket.md)**



### remove

    mixed ZMsg::remove(\ZFrame $frame)

Remove the specified frame from the message.



* Visibility: **public**


#### Arguments
* $frame **[ZFrame](ZFrame.md)**



### first

    \ZFrame|null ZMsg::first()

Return first frame in message and reset the iterator.



* Visibility: **public**




### next

    \ZFrame|null ZMsg::next()

Return next frame in message and increment the iterator.



* Visibility: **public**




### last

    \ZFrame|null ZMsg::last()

Return last frame in message and put the iterator to the end.



* Visibility: **public**




### get_size

    integer ZMsg::get_size()

Return the number of frames in message.



* Visibility: **public**




### get_content_size

    integer ZMsg::get_content_size()

Return the size (in bytes) of the entire message.



* Visibility: **public**




### save

    mixed ZMsg::save(string $file)

Save the message to a file.



* Visibility: **public**


#### Arguments
* $file **string** - &lt;p&gt;File name.&lt;/p&gt;



### load

    mixed ZMsg::load(string $file)

Load message from a file.



* Visibility: **public**


#### Arguments
* $file **string** - &lt;p&gt;File name.&lt;/p&gt;



### dump

    mixed ZMsg::dump()

Dump the object to console.



* Visibility: **public**




### offsetExists

    boolean ZMsg::offsetExists(mixed $offset)

offsetExists



* Visibility: **public**


#### Arguments
* $offset **mixed**



### offsetGet

    mixed ZMsg::offsetGet(mixed $offset)

offsetGet



* Visibility: **public**


#### Arguments
* $offset **mixed**



### offsetSet

    mixed ZMsg::offsetSet(mixed $offset, $value)

offsetSet



* Visibility: **public**


#### Arguments
* $offset **mixed**
* $value **mixed**



### offsetUnset

    mixed ZMsg::offsetUnset(mixed $offset)

offsetUnset



* Visibility: **public**


#### Arguments
* $offset **mixed**



### count

    integer ZMsg::count()

count



* Visibility: **public**



