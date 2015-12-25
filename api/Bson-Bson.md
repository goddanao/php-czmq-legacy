Bson\Bson
===============

Bson

...


* Class name: Bson
* Namespace: Bson



Constants
----------


### BSON_TYPE_UNDEFINED

    const BSON_TYPE_UNDEFINED = 6





### BSON_TYPE_NULL

    const BSON_TYPE_NULL = 10





### BSON_TYPE_BOOL

    const BSON_TYPE_BOOL = 8





### BSON_TYPE_INT32

    const BSON_TYPE_INT32 = 16





### BSON_TYPE_INT64

    const BSON_TYPE_INT64 = 18





### BSON_TYPE_DOUBLE

    const BSON_TYPE_DOUBLE = 1





### BSON_TYPE_CODE

    const BSON_TYPE_CODE = 13





### BSON_TYPE_CODEWSCOPE

    const BSON_TYPE_CODEWSCOPE = 15





### BSON_TYPE_UTF8

    const BSON_TYPE_UTF8 = 2





### BSON_TYPE_TIMESTAMP

    const BSON_TYPE_TIMESTAMP = 17





### BSON_TYPE_DATE_TIME

    const BSON_TYPE_DATE_TIME = 9





### BSON_TYPE_REGEX

    const BSON_TYPE_REGEX = 11





### BSON_TYPE_BINARY

    const BSON_TYPE_BINARY = 5





### BSON_TYPE_SYMBOL

    const BSON_TYPE_SYMBOL = 14





### BSON_TYPE_OID

    const BSON_TYPE_OID = 7





### BSON_TYPE_ARRAY

    const BSON_TYPE_ARRAY = 4





### BSON_TYPE_DOCUMENT

    const BSON_TYPE_DOCUMENT = 3





### BSON_TYPE_EOD

    const BSON_TYPE_EOD = 0





### BSON_TYPE_DBPOINTER

    const BSON_TYPE_DBPOINTER = 12





### BSON_TYPE_MAXKEY

    const BSON_TYPE_MAXKEY = 127





### BSON_TYPE_MINKEY

    const BSON_TYPE_MINKEY = 255





### BSON_SUBTYPE_BINARY

    const BSON_SUBTYPE_BINARY = 0





### BSON_SUBTYPE_FUNCTION

    const BSON_SUBTYPE_FUNCTION = 1





### BSON_SUBTYPE_BINARY_DEPRECATED

    const BSON_SUBTYPE_BINARY_DEPRECATED = 2





### BSON_SUBTYPE_UUID_DEPRECATED

    const BSON_SUBTYPE_UUID_DEPRECATED = 3





### BSON_SUBTYPE_UUID

    const BSON_SUBTYPE_UUID = 4





### BSON_SUBTYPE_MD5

    const BSON_SUBTYPE_MD5 = 5





### BSON_SUBTYPE_USER

    const BSON_SUBTYPE_USER = 128







Methods
-------


### encode

    mixed Bson\Bson::encode(mixed $data)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### decode

    mixed Bson\Bson::decode(mixed $data)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### json_to_bson

    mixed Bson\Bson::json_to_bson(mixed $data)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### bson_to_json

    mixed Bson\Bson::bson_to_json(mixed $data)



...

* Visibility: **public**
* This method is **static**.


#### Arguments
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;


