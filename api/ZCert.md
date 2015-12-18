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

Create e new Certificate, optionally load it's content from file.



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

Return the meta value for the specified key.



* Visibility: **public**


#### Arguments
* $name **string** - &lt;p&gt;Meta key.&lt;/p&gt;



### get_meta_keys

    array ZCert::get_meta_keys()

Return an array of all available meta keys.



* Visibility: **public**




### set_meta

    mixed ZCert::set_meta(string $name, string $value)

Set the meta value for the specified key.



* Visibility: **public**


#### Arguments
* $name **string** - &lt;p&gt;Meta key.&lt;/p&gt;
* $value **string** - &lt;p&gt;Meta value.&lt;/p&gt;



### save

    mixed ZCert::save(string $filename)

Save the certificate to the specified filename.



* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;Certificate filename.&lt;/p&gt;



### save_public

    mixed ZCert::save_public(string $filename)

Save the public key to the specified file.



* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;Public key filename.&lt;/p&gt;



### save_secret

    mixed ZCert::save_secret(string $filename)

Save the secret key to the specified file.



* Visibility: **public**


#### Arguments
* $filename **string** - &lt;p&gt;Secret key filename.&lt;/p&gt;



### apply

    mixed ZCert::apply(\IZSocket $socket)

Apply the certificate to the specified socket.



* Visibility: **public**


#### Arguments
* $socket **[IZSocket](IZSocket.md)**



### dump

    mixed ZCert::dump()

Dump the object to console.



* Visibility: **public**



