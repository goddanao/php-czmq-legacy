ZCert
===============

ZCert

Certificate Holder Class


* Class name: ZCert
* Namespace: 







Methods
-------


### __construct

    \ZCert ZCert::__construct(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;Certificate filename. (optional)&lt;/p&gt;



### get_public_key

    string ZCert::get_public_key()

Return the public key.



* Visibility: **public**




### get_secret_key

    string ZCert::get_secret_key()

Return the secret key.



* Visibility: **public**




### get_meta

    string ZCert::get_meta(string $name)



...

* Visibility: **public**


#### Arguments
* $name **string** - &lt;p&gt;...&lt;/p&gt;



### get_meta_keys

    array ZCert::get_meta_keys()



...

* Visibility: **public**




### set_meta

    mixed ZCert::set_meta(string $name, string $value)



...

* Visibility: **public**


#### Arguments
* $name **string** - &lt;p&gt;...&lt;/p&gt;
* $value **string** - &lt;p&gt;...&lt;/p&gt;



### save

    mixed ZCert::save(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### save_public

    mixed ZCert::save_public(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### save_secret

    mixed ZCert::save_secret(string $filename)



...

* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;...&lt;/p&gt;



### apply

    mixed ZCert::apply(\IZSocket $socket)



...

* Visibility: **public**


#### Arguments
* $socket **[IZSocket](IZSocket.md)**



### dump

    mixed ZCert::dump()

Dump the object to console.



* Visibility: **public**



