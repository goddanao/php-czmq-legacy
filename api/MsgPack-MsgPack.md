MsgPack\MsgPack
===============

MsgPack

MsgPack is a static class which offers customizable encoding/decoding support for msgpack format.
Supports basic php types and objects (only public properties).


* Class name: MsgPack
* Namespace: MsgPack



Constants
----------


### MSGPACK_OBJECT_NIL

    const MSGPACK_OBJECT_NIL = 0





### MSGPACK_OBJECT_BOOLEAN

    const MSGPACK_OBJECT_BOOLEAN = 1





### MSGPACK_OBJECT_POSITIVE_INTEGER

    const MSGPACK_OBJECT_POSITIVE_INTEGER = 2





### MSGPACK_OBJECT_NEGATIVE_INTEGER

    const MSGPACK_OBJECT_NEGATIVE_INTEGER = 3





### MSGPACK_OBJECT_FLOAT

    const MSGPACK_OBJECT_FLOAT = 4





### MSGPACK_OBJECT_STR

    const MSGPACK_OBJECT_STR = 5





### MSGPACK_OBJECT_ARRAY

    const MSGPACK_OBJECT_ARRAY = 6





### MSGPACK_OBJECT_MAP

    const MSGPACK_OBJECT_MAP = 7





### MSGPACK_OBJECT_BIN

    const MSGPACK_OBJECT_BIN = 8





### MSGPACK_OBJECT_EXT

    const MSGPACK_OBJECT_EXT = 9







Methods
-------


### encode

    mixed MsgPack\MsgPack::encode(mixed $data, callable $encoder)

Encode the specified data.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $data **mixed** - &lt;p&gt;The data to be encoded.&lt;/p&gt;
* $encoder **callable** - &lt;p&gt;An encoder callback used to custom encode objects. (optional)&lt;/p&gt;



### decode

    mixed MsgPack\MsgPack::decode(mixed $data, callable $decoder)

Decode the specified msgpack data.



* Visibility: **public**
* This method is **static**.


#### Arguments
* $data **mixed** - &lt;p&gt;The data to be decoded.&lt;/p&gt;
* $decoder **callable** - &lt;p&gt;A decode callback used to custom decode objects. (optional)&lt;/p&gt;


