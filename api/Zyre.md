Zyre
===============

Zyre

Zyre does local area discovery and clustering. A Zyre node broadcasts UDP beacons, and connects to peers that it finds.


* Class name: Zyre
* Namespace: 
* This class implements: [IZSocket](IZSocket.md), [IZDescriptor](IZDescriptor.md)






Methods
-------


### __construct

    mixed Zyre::__construct(string $name)

Creates a new Zyre node. Note that until you start the node it is silent and invisible to other nodes on the network.



* Visibility: **public**


#### Arguments
* $name **string** - &lt;p&gt;Zyre node name. (optional)&lt;/p&gt;



### start

    mixed Zyre::start()

Start node, after setting header values. When you start a node it begins discovery and connection.



* Visibility: **public**




### stop

    mixed Zyre::stop()

Stop node, this signals to other peers that this node will go away. This is polite; however you can also just destroy the node without stopping it.



* Visibility: **public**




### recv

    \ZMsg Zyre::recv()

Receive next message from network. The message may be a control message (ENTER, EXIT, JOIN, LEAVE) or data (WHISPER, SHOUT). Returns ZMsg object, or NULL if interrupted.



* Visibility: **public**




### dump

    mixed Zyre::dump()

Dump the Zyre node configuration.



* Visibility: **public**




### get_uuid

    string Zyre::get_uuid()

Get the UUID of the Zyre node



* Visibility: **public**




### get_name

    string Zyre::get_name()

Get then Zyre node name.



* Visibility: **public**




### get_peers

    array Zyre::get_peers()

Return a list of known peers.



* Visibility: **public**




### get_groups

    array Zyre::get_groups()

Return a list of known groups.



* Visibility: **public**




### get_peer_groups

    mixed Zyre::get_peer_groups()



...

* Visibility: **public**




### set_endpoint

    mixed Zyre::set_endpoint(string $endpoint)

By default, Zyre binds to an ephemeral TCP port and broadcasts the local
host name using UDP beaconing. When you call this method, Zyre will use
gossip discovery instead of UDP beaconing. You MUST set-up the gossip
service separately using zyre_gossip_bind() and _connect(). Note that the
endpoint MUST be valid for both bind and connect operations. You can use
inproc://, ipc://, or tcp:// transports (for tcp://, use an IP address
that is meaningful to remote as well as local nodes). Returns true if
the bind was successful.



* Visibility: **public**


#### Arguments
* $endpoint **string**



### set_port

    mixed Zyre::set_port(integer $port)

Set UDP beacon discovery port; defaults to 5670, this call overrides that so you can create independent clusters on the same network, for e.g. development vs. production. Has no effect after node start.



* Visibility: **public**


#### Arguments
* $port **integer** - &lt;p&gt;...&lt;/p&gt;



### set_interface

    mixed Zyre::set_interface(string $interface)

Set network interface for UDP beacons. If you do not set this, CZMQ will
choose an interface for you. On boxes with several interfaces you should
specify which one you want to use, or strange things can happen.



* Visibility: **public**


#### Arguments
* $interface **string**



### set_interval

    mixed Zyre::set_interval(integer $interval)

Set UDP beacon discovery interval, in milliseconds. Default is instant beacon exploration followed by pinging every 1,000 msecs.



* Visibility: **public**


#### Arguments
* $interval **integer** - &lt;p&gt;...&lt;/p&gt;



### gossip_bind

    mixed Zyre::gossip_bind(string $endpoint)

Set-up gossip discovery of other nodes. At least one node in the cluster
must bind to a well-known gossip endpoint, so other nodes can connect to
it. Note that gossip endpoints are completely distinct from Zyre node
endpoints, and should not overlap (they can use the same transport).



* Visibility: **public**


#### Arguments
* $endpoint **string**



### gossip_connect

    mixed Zyre::gossip_connect(string $endpoint)

Set-up gossip discovery of other nodes. A node may connect to multiple
other nodes, for redundancy paths. For details of the gossip network
design, see the CZMQ zgossip class.



* Visibility: **public**


#### Arguments
* $endpoint **string**



### get_peer_header

    mixed Zyre::get_peer_header(string $name)

Return the value of a header of a conected peer.



* Visibility: **public**


#### Arguments
* $name **string**



### get_version

    string Zyre::get_version()

Get Zyre version.



* Visibility: **public**
* This method is **static**.




### set_verbose

    mixed Zyre::set_verbose()

Set verbose mode; this tells the node to log all traffic as well as all major events.



* Visibility: **public**




### set_header

    mixed Zyre::set_header(string $name, mixed $value)

Set node header; these are provided to other nodes during discovery and come in each ENTER message.



* Visibility: **public**


#### Arguments
* $name **string** - &lt;p&gt;...&lt;/p&gt;
* $value **mixed** - &lt;p&gt;...&lt;/p&gt;



### join

    mixed Zyre::join(string $group)

Join a named group; after joining a group you can send messages to the group and all Zyre nodes in that group will receive them.



* Visibility: **public**


#### Arguments
* $group **string** - &lt;p&gt;Group name to join.&lt;/p&gt;



### leave

    mixed Zyre::leave(string $group)

Leave a joined group



* Visibility: **public**


#### Arguments
* $group **string** - &lt;p&gt;Group name to leave.&lt;/p&gt;



### send_peer

    mixed Zyre::send_peer(string $peer, mixed $data)

Send message to single peer, specified as a UUID string.



* Visibility: **public**


#### Arguments
* $peer **string** - &lt;p&gt;Peer UUID.&lt;/p&gt;
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### send_group

    mixed Zyre::send_group(string $group, mixed $data)

Send message to a named group.



* Visibility: **public**


#### Arguments
* $group **string** - &lt;p&gt;Group name.&lt;/p&gt;
* $data **mixed** - &lt;p&gt;...&lt;/p&gt;



### get_fd

    mixed IZDescriptor::get_fd()



...

* Visibility: **public**
* This method is defined by [IZDescriptor](IZDescriptor.md)




### get_socket

    mixed IZSocket::get_socket()



...

* Visibility: **public**
* This method is defined by [IZSocket](IZSocket.md)



