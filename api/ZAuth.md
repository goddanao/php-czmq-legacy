ZAuth
===============

ZAuth

Authentication for ZeroMQ security mechanisms.


* Class name: ZAuth
* Namespace: 
* This class implements: [ZDescriptor](ZDescriptor.md)


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

    mixed ZAuth::__construct()

ZAuth::__construct



* Visibility: **public**




### set_verbose

    mixed ZAuth::set_verbose()

ZAuth::set_verbose

Enable verbose logging of commands and activity. Verbose logging can help
debug non-trivial authentication policies

* Visibility: **public**




### recv

    mixed ZAuth::recv()

ZAuth::recv

...

* Visibility: **public**




### allow

    mixed ZAuth::allow(string $ip)

ZAuth::allow

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

ZAuth::deny

Deny (blacklist) a list of IP addresses. For all security mechanisms,
this rejects the connection without any further authentication. Use
either a whitelist, or a blacklist, not not both. If you define both
a whitelist and a blacklist, only the whitelist takes effect

* Visibility: **public**


#### Arguments
* $ip **string** - &lt;p&gt;ip address&lt;/p&gt;



### configure

    mixed ZAuth::configure()

ZAuth::configure



* Visibility: **public**




### get_fd

    mixed ZDescriptor::get_fd()

ZDescriptor::get_fd

...

* Visibility: **public**
* This method is defined by [ZDescriptor](ZDescriptor.md)



