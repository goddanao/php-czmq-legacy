ZMsg
===============

ZMsg

ZeroMQ Multipart message handling.


* Class name: ZMsg
* Namespace: 
* This class implements: ArrayAccess, Countable, Traversable






Methods
-------


### __construct

    \ZMsg ZMsg::__construct()





* Visibility: **public**




### append

    mixed ZMsg::append(\ZFrame $data)

Push a frame at the end of the message.



* Visibility: **public**


#### Arguments
* $data **[ZFrame](ZFrame.md)** - &lt;p&gt;Frame to append.&lt;/p&gt;



### prepend

    mixed ZMsg::prepend(\ZFrame $data)

Add a frame at the top of the message.



* Visibility: **public**


#### Arguments
* $data **[ZFrame](ZFrame.md)** - &lt;p&gt;Frame to prepend.&lt;/p&gt;



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

Push data frames as specified in the picture format at the end of the message.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to push in message.&lt;/p&gt;



### prepend_picture

    mixed ZMsg::prepend_picture(string $picture)

Add data frames as specified in the picture format at the top of the message.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to push in message.&lt;/p&gt;



### pop_picture

    mixed ZMsg::pop_picture(string $picture)

Pop frames from message as as specified in the picture format.



* Visibility: **public**


#### Arguments
* $picture **string** - &lt;p&gt;Positional string indicating the sequence and data type(s) to push in message.&lt;/p&gt;



### append_zipped

    mixed ZMsg::append_zipped(string $data)

Push a ZLib encoded frame at the end of the message.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;Data to append.&lt;/p&gt;



### prepend_zipped

    mixed ZMsg::prepend_zipped(string $data)

Add a ZLib encoded frame at the top of the message.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;Data to prepend.&lt;/p&gt;



### pop_zipped

    mixed|null ZMsg::pop_zipped()

Pop next ZLib decoded frame in message.



* Visibility: **public**




### append_msgpack

    mixed ZMsg::append_msgpack(string $data)

Push a MsgPack encoded frame at the end of the message.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;Data to append.&lt;/p&gt;



### prepend_msgpack

    mixed ZMsg::prepend_msgpack(string $data)

Add a MsgPack encoded frame at the top of the message.



* Visibility: **public**


#### Arguments
* $data **string** - &lt;p&gt;Data to prepend.&lt;/p&gt;



### pop_msgpack

    mixed|null ZMsg::pop_msgpack()

Pop next MsgPack decoded frame in message.



* Visibility: **public**




### append_bson

    mixed ZMsg::append_bson(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### prepend_bson

    mixed ZMsg::prepend_bson(mixed $data)



...

* Visibility: **public**


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### pop_bson

    mixed ZMsg::pop_bson()



...

* Visibility: **public**




### send

    mixed ZMsg::send(\Bson\IZSocket $socket)

Send message.



* Visibility: **public**


#### Arguments
* $socket **Bson\IZSocket** - &lt;p&gt;...&lt;/p&gt;



### remove

    mixed ZMsg::remove(\ZFrame $frame)

Remove the specified frame from the message.



* Visibility: **public**


#### Arguments
* $frame **[ZFrame](ZFrame.md)** - &lt;p&gt;The frame to remove.&lt;/p&gt;



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



