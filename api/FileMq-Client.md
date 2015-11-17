FileMq\Client
===============

Client

...


* Class name: Client
* Namespace: FileMq
* This class implements: [IZSocket](IZSocket.md)






Methods
-------


### \FileMq\Client::__construct()

```
mixed FileMq\Client::\FileMq\Client::__construct()($endpoint, $local_path, $timeout)
```

Client::__construct

...

* Visibility: **public**

#### Arguments

* $endpoint **mixed**
* $local_path **mixed**
* $timeout **mixed**



### \FileMq\Client::set_timeout()

```
mixed FileMq\Client::\FileMq\Client::set_timeout()($timeout)
```

Client::set_timeout

...

* Visibility: **public**

#### Arguments

* $timeout **mixed**



### \FileMq\Client::connect()

```
mixed FileMq\Client::\FileMq\Client::connect()()
```

Client::connect

...

* Visibility: **public**



### \FileMq\Client::subscribe()

```
mixed FileMq\Client::\FileMq\Client::subscribe()($remote_path)
```

Client::subscribe

...

* Visibility: **public**

#### Arguments

* $remote_path **mixed**



### \FileMq\Client::run()

```
mixed FileMq\Client::\FileMq\Client::run()(callable $callback)
```

Client::run

...

* Visibility: **public**

#### Arguments

* $callback **callable** - &lt;p&gt;...&lt;/p&gt;



### \FileMq\Client::get_socket()

```
mixed FileMq\Client::\FileMq\Client::get_socket()()
```

Client::get_socket

...

* Visibility: **public**



### \FileMq\Client::get_fd()

```
mixed FileMq\Client::\FileMq\Client::get_fd()()
```

Client::get_fd

...

* Visibility: **public**



### \IZSocket::get_socket()

```
mixed IZSocket::\IZSocket::get_socket()()
```

IZSocket::get_socket

...

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)



### \IZSocket::get_fd()

```
mixed IZSocket::\IZSocket::get_fd()()
```

IZSocket::get_fd

...

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)


