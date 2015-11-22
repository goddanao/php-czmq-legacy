FileMq\Client
===============

Client

...


* Class name: Client
* Namespace: FileMq
* This class implements: [ZDescriptor](ZDescriptor.md)






Methods
-------


### __construct

    mixed FileMq\Client::__construct($endpoint, $local_path, $timeout)

Client::__construct

...

* Visibility: **public**


#### Arguments
* $endpoint **mixed**
* $local_path **mixed**
* $timeout **mixed**



### set_timeout

    mixed FileMq\Client::set_timeout($timeout)

Client::set_timeout

...

* Visibility: **public**


#### Arguments
* $timeout **mixed**



### connect

    mixed FileMq\Client::connect()

Client::connect

...

* Visibility: **public**




### subscribe

    mixed FileMq\Client::subscribe($remote_path)

Client::subscribe

...

* Visibility: **public**


#### Arguments
* $remote_path **mixed**



### recv

    mixed FileMq\Client::recv()

Client::recv

...

* Visibility: **public**




### get_fd

    mixed ZDescriptor::get_fd()

ZDescriptor::get_fd

...

* Visibility: **public**
* This method is defined by [ZDescriptor](ZDescriptor.md)



