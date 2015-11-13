ZAuth
===============

ZAuth

Authentication for ZeroMQ security mechanisms.


* Class name: ZAuth
* Namespace: 
* This class implements: [IZSocket](IZSocket.md)


Constants
----------


### AUTH_PLAIN

```
const AUTH_PLAIN = "PLAIN"
```





### AUTH_CURVE

```
const AUTH_CURVE = "CURVE"
```





### AUTH_GSSAPI

```
const AUTH_GSSAPI = "GSSAPI"
```







Methods
-------


### \ZAuth::__construct()

```
mixed ZAuth::\ZAuth::__construct()()
```

ZAuth::__construct



* Visibility: **public**



### \ZAuth::set_verbose()

```
mixed ZAuth::\ZAuth::set_verbose()()
```

ZAuth::set_verbose

Enable verbose logging of commands and activity. Verbose logging can help
debug non-trivial authentication policies

* Visibility: **public**



### \ZAuth::allow()

```
mixed ZAuth::\ZAuth::allow()(string $ip)
```

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



### \ZAuth::deny()

```
mixed ZAuth::\ZAuth::deny()(string $ip)
```

ZAuth::deny

Deny (blacklist) a list of IP addresses. For all security mechanisms,
this rejects the connection without any further authentication. Use
either a whitelist, or a blacklist, not not both. If you define both
a whitelist and a blacklist, only the whitelist takes effect

* Visibility: **public**

#### Arguments

* $ip **string** - &lt;p&gt;ip address&lt;/p&gt;



### \ZAuth::configure()

```
mixed ZAuth::\ZAuth::configure()()
```

ZAuth::configure



* Visibility: **public**


