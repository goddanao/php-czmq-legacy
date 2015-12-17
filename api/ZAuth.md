ZAuth
===============

ZAuth

Authentication for ZeroMQ security mechanisms.


* Class name: ZAuth
* Namespace: 
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md), [IZEmitter](IZEmitter.md)


Constants
----------


### AUTH_PLAIN

    const AUTH_PLAIN = "PLAIN"





### AUTH_CURVE

    const AUTH_CURVE = "CURVE"





### AUTH_GSSAPI

    const AUTH_GSSAPI = "GSSAPI"







Methods
-------


### __construct

    \ZAuth ZAuth::__construct(mixed $verbose)





* Visibility: **public**


#### Arguments
* $verbose **mixed** - &lt;p&gt;... (optional)&lt;/p&gt;



### set_verbose

    mixed ZAuth::set_verbose()

Enable verbose logging of commands and activity. Verbose logging can help
debug non-trivial authentication policies



* Visibility: **public**




### recv

    \ZMsg ZAuth::recv()

Recieve a ZMsg.



* Visibility: **public**




### allow

    mixed ZAuth::allow(string $ip)

Allow (whitelist) a list of IP addresses. For NULL, all clients from
these addresses will be accepted. For PLAIN and CURVE, they will be
allowed to continue with authentication. You can call this method
multiple times to whitelist more IP addresses. If you whitelist one
or nmore addresses, any non-whitelisted addresses are treated as
blacklisted



* Visibility: **public**


#### Arguments
* $ip **string** - &lt;p&gt;ip address&lt;/p&gt;



### deny

    mixed ZAuth::deny(string $ip)

Deny (blacklist) a list of IP addresses. For all security mechanisms,
this rejects the connection without any further authentication. Use
either a whitelist, or a blacklist, not not both. If you define both
a whitelist and a blacklist, only the whitelist takes effect



* Visibility: **public**


#### Arguments
* $ip **string** - &lt;p&gt;ip address&lt;/p&gt;



### configure

    mixed ZAuth::configure(string $mode, string $path)





* Visibility: **public**


#### Arguments
* $mode **string** - &lt;p&gt;...&lt;/p&gt;
* $path **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### get_fd

    integer IZDescriptor::get_fd()

Get the underlying File Descriptor.



* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    \ZSocket IZSocket::get_socket()

Get the underlying ZSocket.



* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)




### start

    mixed ZAuth::start()



...

* Visibility: **public**




### on

    mixed IZEmitter::on(string $event, callable $listener)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### once

    mixed IZEmitter::once(string $event, callable $listener)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### remove_listener

    mixed IZEmitter::remove_listener(string $event, callable $listener)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $listener **callable** - &lt;p&gt;...&lt;/p&gt;



### remove_all_listeners

    mixed IZEmitter::remove_all_listeners(string $event)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;... (optional)&lt;/p&gt;



### listeners

    array|null IZEmitter::listeners(string $event)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;



### emit

    mixed IZEmitter::emit(string $event, array $arguments)



...

* Visibility: **public**
* This method is defined by [IZEmitter](IZEmitter.md)


#### Arguments
* $event **string** - &lt;p&gt;...&lt;/p&gt;
* $arguments **array** - &lt;p&gt;...&lt;/p&gt;


