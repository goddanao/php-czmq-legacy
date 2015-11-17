Malamute\Client
===============

Client

...


* Class name: Client
* Namespace: Malamute
* This class implements: [IZSocket](IZSocket.md)






Methods
-------


### \Malamute\Client::__construct()

```
mixed Malamute\Client::\Malamute\Client::__construct()($endpoint, $address, $timeout)
```

Client::__construct

...

* Visibility: **public**

#### Arguments

* $endpoint **mixed**
* $address **mixed**
* $timeout **mixed**



### \Malamute\Client::set_verbose()

```
mixed Malamute\Client::\Malamute\Client::set_verbose()()
```

Client::set_verbose

...

* Visibility: **public**



### \Malamute\Client::connect()

```
mixed Malamute\Client::\Malamute\Client::connect()($endpoint, $address, $timeout)
```

Client::connect

...

* Visibility: **public**

#### Arguments

* $endpoint **mixed**
* $address **mixed**
* $timeout **mixed**



### \Malamute\Client::header()

```
mixed Malamute\Client::\Malamute\Client::header()()
```

Client::header

...

* Visibility: **public**



### \Malamute\Client::content()

```
mixed Malamute\Client::\Malamute\Client::content()()
```

Client::content

...

* Visibility: **public**



### \Malamute\Client::set_producer()

```
mixed Malamute\Client::\Malamute\Client::set_producer()($stream)
```

Client::set_producer

...

* Visibility: **public**

#### Arguments

* $stream **mixed**



### \Malamute\Client::set_worker()

```
mixed Malamute\Client::\Malamute\Client::set_worker()($address, $patern)
```

Client::set_worker

...

* Visibility: **public**

#### Arguments

* $address **mixed**
* $patern **mixed**



### \Malamute\Client::set_consumer()

```
mixed Malamute\Client::\Malamute\Client::set_consumer()($stream, $patern)
```

Client::set_consumer

...

* Visibility: **public**

#### Arguments

* $stream **mixed**
* $patern **mixed**



### \Malamute\Client::send_stream()

```
mixed Malamute\Client::\Malamute\Client::send_stream()($subject)
```

Client::send_stream

...

* Visibility: **public**

#### Arguments

* $subject **mixed**



### \Malamute\Client::send_mailbox()

```
mixed Malamute\Client::\Malamute\Client::send_mailbox()($address, $payload, $timeout, $subject, $tracker)
```

Client::send_mailbox

...

* Visibility: **public**

#### Arguments

* $address **mixed**
* $payload **mixed**
* $timeout **mixed**
* $subject **mixed**
* $tracker **mixed**



### \Malamute\Client::send_service()

```
mixed Malamute\Client::\Malamute\Client::send_service()($address, $subject, $payload, $timeout, $tracker)
```

Client::send_service

...

* Visibility: **public**

#### Arguments

* $address **mixed**
* $subject **mixed**
* $payload **mixed**
* $timeout **mixed**
* $tracker **mixed**



### \Malamute\Client::recv_picture()

```
mixed Malamute\Client::\Malamute\Client::recv_picture()($picture)
```

Client::recv_picture

...

* Visibility: **public**

#### Arguments

* $picture **mixed**



### \Malamute\Client::recv_string()

```
mixed Malamute\Client::\Malamute\Client::recv_string()()
```

Client::recv_string

...

* Visibility: **public**



### \Malamute\Client::recv()

```
mixed Malamute\Client::\Malamute\Client::recv()()
```

Client::recv

...

* Visibility: **public**



### \Malamute\Client::get_socket()

```
mixed Malamute\Client::\Malamute\Client::get_socket()()
```

Client::get_socket

...

* Visibility: **public**



### \Malamute\Client::get_fd()

```
mixed Malamute\Client::\Malamute\Client::get_fd()()
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


