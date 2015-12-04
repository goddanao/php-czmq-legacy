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

    mixed Majordomo\ITitanicStorage::read(mixed $what, mixed $uuid)



...

* Visibility: **public**


#### Arguments
* $what **mixed** - &lt;p&gt;...&lt;/p&gt;
* $uuid **mixed** - &lt;p&gt;...&lt;/p&gt;



### store

    mixed Majordomo\ITitanicStorage::store(mixed $what, mixed $uuid, \FileMq\ZMsg $msg)



...

* Visibility: **public**


#### Arguments
* $what **mixed** - &lt;p&gt;...&lt;/p&gt;
* $uuid **mixed** - &lt;p&gt;...&lt;/p&gt;
* $msg **FileMq\ZMsg** - &lt;p&gt;...&lt;/p&gt;



### close

    mixed Majordomo\ITitanicStorage::close(mixed $uuid)



...

* Visibility: **public**


#### Arguments
* $uuid **mixed** - &lt;p&gt;...&lt;/p&gt;



### status

    mixed Majordomo\ITitanicStorage::status(mixed $uuid)



...

* Visibility: **public**


#### Arguments
* $uuid **mixed** - &lt;p&gt;...&lt;/p&gt;



### process

    mixed Majordomo\ITitanicStorage::process()



...

* Visibility: **public**



