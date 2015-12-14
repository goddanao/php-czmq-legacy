Majordomo\ITitanicStorage
===============

ITitanicStorage

...


* Interface name: ITitanicStorage
* Namespace: Majordomo
* This is an **interface**






Methods
-------


### read

    \ZMsg Majordomo\ITitanicStorage::read(string $what, string $uuid)



...

* Visibility: **public**


#### Arguments
* $what **string** - &lt;p&gt;...&lt;/p&gt;
* $uuid **string** - &lt;p&gt;...&lt;/p&gt;



### store

    mixed Majordomo\ITitanicStorage::store(string $what, string $uuid, \ZMsg $msg)



...

* Visibility: **public**


#### Arguments
* $what **string** - &lt;p&gt;...&lt;/p&gt;
* $uuid **string** - &lt;p&gt;...&lt;/p&gt;
* $msg **[ZMsg](ZMsg.md)** - &lt;p&gt;...&lt;/p&gt;



### close

    mixed Majordomo\ITitanicStorage::close(string $uuid)



...

* Visibility: **public**


#### Arguments
* $uuid **string** - &lt;p&gt;...&lt;/p&gt;



### status

    mixed Majordomo\ITitanicStorage::status(string $uuid)



...

* Visibility: **public**


#### Arguments
* $uuid **string** - &lt;p&gt;...&lt;/p&gt;



### process

    string|null Majordomo\ITitanicStorage::process()



...

* Visibility: **public**



