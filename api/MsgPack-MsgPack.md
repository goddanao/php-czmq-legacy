MsgPack\MsgPack
===============

MsgPack

MsgPack is a static class which offers customizable encoding/decoding support for msgpack format.
Supports basic php types and objects (only public properties).


* Class name: MsgPack
* Namespace: MsgPack







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


