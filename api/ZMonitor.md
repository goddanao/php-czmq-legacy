ZMonitor
===============

ZMonitor

...


* Class name: ZMonitor
* Namespace: 
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)


Constants
----------


### EVT_CONNECTED

    const EVT_CONNECTED = "CONNECTED"





### EVT_CONNECT_DELAYED

    const EVT_CONNECT_DELAYED = "CONNECT_DELAYED"





### EVT_CONNECT_RETRIED

    const EVT_CONNECT_RETRIED = "CONNECT_RETRIED"





### EVT_LISTENING

    const EVT_LISTENING = "LISTENING"





### EVT_BIND_FAILED

    const EVT_BIND_FAILED = "BIND_FAILED"





### EVT_ACCEPTED

    const EVT_ACCEPTED = "ACCEPTED"





### EVT_ACCEPT_FAILED

    const EVT_ACCEPT_FAILED = "ACCEPT_FAILED"





### EVT_CLOSED

    const EVT_CLOSED = "CLOSED"





### EVT_CLOSE_FAILED

    const EVT_CLOSE_FAILED = "CLOSE_FAILED"





### EVT_DISCONNECTED

    const EVT_DISCONNECTED = "DISCONNECTED"





### EVT_MONITOR_STOPPED

    const EVT_MONITOR_STOPPED = "MONITOR_STOPPED"





### EVT_ALL

    const EVT_ALL = "ALL"







Methods
-------


### __construct

    mixed ZMonitor::__construct(\IZSocket $socket)

ZMonitor::__construct

...

* Visibility: **public**


#### Arguments
* $socket **[IZSocket](IZSocket.md)** - &lt;p&gt;...&lt;/p&gt;



### set_verbose

    mixed ZMonitor::set_verbose()

ZMonitor::set_verbose

...

* Visibility: **public**




### listen

    mixed ZMonitor::listen(mixed $event)

ZMonitor::listen

...

* Visibility: **public**


#### Arguments
* $event **mixed** - &lt;p&gt;...&lt;/p&gt;



### start

    mixed ZMonitor::start()

ZMonitor::start

...

* Visibility: **public**




### recv

    \ZMsg ZMonitor::recv()

ZMonitor::recv

Recieve a ZMsg.

* Visibility: **public**




### get_fd

    mixed IZDescriptor::get_fd()

IZDescriptor::get_fd

...

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    mixed IZSocket::get_socket()

IZSocket::get_socket

...

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)



