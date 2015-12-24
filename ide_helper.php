<?php

namespace {

/**
 * ZSys
 *
 * ZSys is static class holding zeromq system level methods / consts.
 */
final  class ZSys {
  const SOCKET_PUB = "pub";
  const SOCKET_SUB = "sub";
  const SOCKET_REP = "rep";
  const SOCKET_REQ = "req";
  const SOCKET_DEALER = "dealer";
  const SOCKET_ROUTER = "router";
  const SOCKET_PUSH = "push";
  const SOCKET_PULL = "pull";
  const SOCKET_XPUB = "xpub";
  const SOCKET_XSUB = "xsub";
  const SOCKET_XREP = "xrep";
  const SOCKET_XREQ = "xreq";
  const SOCKET_PAIR = "pair";
  const SOCKET_STREAM = "stream";
  const SOCKET_SERVER = "server";
  const SOCKET_CLIENT = "client";
  const EVENT_CLOSED = 0x00000080;
  const EVENT_CONNECTED = 0x00000001;
  const EVENT_CONNECT_DELAYED = 0x00000002;
  const EVENT_CONNECT_RETRIED = 0x00000004;
  const EVENT_LISTENING = 0x00000008;
  const EVENT_BIND_FAILED = 0x00000010;
  const EVENT_ACCEPTED = 0x00000020;
  const EVENT_ACCEPT_FAILED = 0x00000040;
  const EVENT_CLOSE_FAILED = 0x00000100;
  const EVENT_DISCONNECTED = 0x00000200;
  const EVENT_MONITOR_STOPPED = 0x00000400;
  const EVENT_ALL = 0x0000ffff;
  const POLL_WAIT_FOREVER = -1;
  const POLL_NONE = 0;
  const POLL_IN = 1;
  const POLL_OUT = 2;
  const POLL_ERR = 4;
  const POLL_PRI = 8;


  /**
   * Configure the number of I/O threads that ZeroMQ will use. A good
   * rule of thumb is one thread per gigabit of traffic in or out. The
   * default is 1, sufficient for most applications. If the environment
   * variable ZSYS_IO_THREADS is defined, that provides the default.
   * Note that this method is valid only before any socket is created.
   * 
   * @param int $threads  
  */
  static public function set_io_threads($threads) {}

  /**
   * Configure use of IPv6 for new zsock instances. By default sockets accept
   * and make only IPv4 connections. When you enable IPv6, sockets will accept
   * and connect to both IPv4 and IPv6 peers. You can override the setting on
   * each zsock_t instance. The default is IPv4 only (ipv6 set to 0). If the
   * environment variable ZSYS_IPV6 is defined (as 1 or 0), this provides the
   * default. Note: has no effect on ZMQ v2.
   * 
   * @param bool $enable  
  */
  static public function set_ipv6($enable) {}

  /**
   * Configure the default linger timeout in msecs for new zsock instances.
   * You can also set this separately on each zsock_t instance. The default
   * linger time is zero, i.e. any pending messages will be dropped. If the
   * environment variable ZSYS_LINGER is defined, that provides the default.
   * Note that process exit will typically be delayed by the linger time.
   * 
   * @param int $linger  
  */
  static public function set_default_linger($linger) {}

  /**
   * Configure the default outgoing pipe limit (HWM) for new zsock instances.
   * You can also set this separately on each zsock_t instance. The default
   * HWM is 1,000, on all versions of ZeroMQ. If the environment variable
   * ZSYS_SNDHWM is defined, that provides the default. Note that a value of
   * zero means no limit, i.e. infinite memory consumption.
   * 
   * @param int $sndhwm  
  */
  static public function set_default_sndhwm($sndhwm) {}

  /**
   * Configure the default incoming pipe limit (HWM) for new zsock instances.
   * You can also set this separately on each zsock_t instance. The default
   * HWM is 1,000, on all versions of ZeroMQ. If the environment variable
   * ZSYS_RCVHWM is defined, that provides the default. Note that a value of
   * zero means no limit, i.e. infinite memory consumption.
   * 
   * @param int $rcvhwm  
  */
  static public function set_default_rcvhwm($rcvhwm) {}

  /**
   * Configure the default HWM for zactor internal pipes; this is set on both
   * ends of the pipe, for outgoing messages only (sndhwm). The default HWM is
   * 1,000, on all versions of ZeroMQ. If the environment var ZSYS_ACTORHWM is
   * defined, that provides the default. Note that a value of zero means no
   * limit, i.e. infinite memory consumption.
   * 
   * @param int $pipehwm  
  */
  static public function set_pipehwm($pipehwm) {}

  /**
   * Return the HWM for zactor internal pipes.
   * 
   * @return int
  */
  static public function get_pipehwm() {}

  /**
   * Returns true if the underlying libzmq supports CURVE security.
   * 
   * @return bool
  */
  static public function has_curve() {}

  /**
   * Return maximum number of ZeroMQ sockets that the system will support.
   * 
   * @return int
  */
  static public function get_socket_limit() {}

  /**
   * Configure the number of sockets that ZeroMQ will allow. The default
   * is 1024. The actual limit depends on the system, and you can query it
   * by using get_socket_limit (). A value of zero means 'maximum'.
   * Note that this method is valid only before any socket is created.
   * 
   * @param int $max_sockets  
  */
  static public function set_max_sockets($max_sockets) {}

  /**
   * Return current host name, for use in public tcp:// endpoints.
   * 
   * @return string
  */
  static public function hostname() {}

  /**
   * Set network interface name to use for broadcasts, particularly zbeacon.
   * This lets the interface be configured for test environments where required.
   * For example, on Mac OS X, zbeacon cannot bind to 255.255.255.255 which is
   * the default when there is no specified interface. If the environment
   * variable ZSYS_INTERFACE is set, use that as the default interface name.
   * Setting the interface to '*' means 'use all available interfaces'.
   * 
   * @param string $interface  
  */
  static public function set_interface($interface) {}

  /**
   * Return network interface to use for broadcasts, or '' if none was set.
   * 
   * @return string
  */
  static public function get_interface() {}

  /**
   * Return network interfaces
   * 
   * @return array
  */
  static public function list_interfaces() {}

  /**
   * Return an array of supported socket types (depends on zmq version installed).
   * 
   * @return array
  */
  static public function get_available_socket_type() {}

  /**
   * Set log identity, which is a string that prefixes all log messages sent
   * by this process. The log identity defaults to the environment variable
   * ZSYS_LOGIDENT, if that is set.
   * 
   * @param string $log_ident  
  */
  static public function set_log_ident($log_ident) {}

  /**
   * Sends log output to a PUB socket bound to the specified endpoint. To
   * collect such log output, create a SUB socket, subscribe to the traffic
   * you care about, and connect to the endpoint. Log traffic is sent as a
   * single string frame, in the same format as when sent to stdout. The
   * log system supports a single sender; multiple calls to this method will
   * bind the same sender to multiple endpoints. To disable the sender, call
   * this method with a null argument.
   * 
   * @param string $log_endpoint  
  */
  static public function set_log_endpoint($log_endpoint) {}

  /**
   * Enable or disable logging to the system facility (syslog on POSIX boxes,
   * event log on Windows). By default this is enabled.
   * 
   * @param bool $enable  
  */
  static public function set_log_system($enable) {}

  /**
   * Return ZMQ version
   * 
   * @return string
  */
  static public function libzmq_version() {}

  /**
   * Return CZMQ version
   * 
   * @return string
  */
  static public function libczmq_version() {}

  /**
   * Return Zyre version
   * 
   * @return string
  */
  static public function libzyre_version() {}

  /**
   * Return Majordomo Protocol version
   * 
   * @return string
  */
  static public function libmdp_version() {}

  /**
   * Return FileMq version
   * 
   * @return string
  */
  static public function libfmq_version() {}

  /**
   * Return MsgPack version
   * 
   * @return string
  */
  static public function libmsgpack_version() {}

  /**
   * Return Malamute version
   * 
   * @return string
  */
  static public function libmlm_version() {}

  /**
   * Generate an UUID and return as 32 bytes string.
   * 
   * @return string
  */
  static public function uuid() {}

  /**
   * Log message as Info
   * 
   * @param string $message  
  */
  static public function info($message) {}

  /**
   * Log message as Debug
   * 
   * @param string $message  
  */
  static public function debug($message) {}

  /**
   * Log message as Warning
   * 
   * @param string $message  
  */
  static public function warning($message) {}

  /**
   * Log message as Error
   * 
   * @param string $message  
  */
  static public function error($message) {}

  /**
   * Check if IPV6 is active by default on newly created sockets.
   * 
   * @return bool
  */
  static public function get_ipv6() {}

  /**
   * Return IPv6 address to use for zbeacon reception, or '' if none was set.
   * 
   * @return string
  */
  static public function get_ipv6_address() {}

  /**
   * Set IPv6 address to use zbeacon socket, particularly for receiving zbeacon.
   *This needs to be set IPv6 is enabled as IPv6 can have multiple addresses
   *on a given interface. If the environment variable ZSYS_IPV6_ADDRESS is set,
   *use that as the default IPv6 address.
   * 
   * @param string $address IPV6 address
  */
  static public function set_ipv6_address($address) {}

  /**
   * Return IPv6 multicast address to use for sending zbeacon, or '' if none was set
   * 
   * @return string
  */
  static public function get_ipv6_mcast_address() {}

  /**
   * Set IPv6 milticast address to use for sending zbeacon messages. This needs
   *to be set if IPv6 is enabled. If the environment variable
   *ZSYS_IPV6_MCAST_ADDRESS is set, use that as the default IPv6 multicast
   *address.
   * 
   * @param string $address IPv6 milticast address
  */
  static public function set_ipv6_mcast_address($address) {}

}


/**
 * ZUdp
 *
 * Udp low level class
 */
class ZUdp implements \IZDescriptor {

  /**
   *  
   * 
   * @param string $interface The interface name to bind (optional)
   * @param int $port The port number to bind (optional)
   * @param bool $routable uses multicast (not yet implemented), else uses broadcast (default) (optional)
   * @return \ZUdp
  */
  public function __construct($interface = null, $port = 5670, $routable = false) {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param string $data The string to send
  */
  public function send_string($data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function send_picture($picture) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $data The data to send.
  */
  public function send_msgpack($data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function send_bson($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

}


/**
 * ZMsg
 *
 * ZeroMQ Multipart message handling.
 */
class ZMsg implements \ArrayAccess, \Countable, \Traversable {

  /**
   *  
   * 
   * @return \ZMsg
  */
  public function __construct() {}

  /**
   * Push a frame at the end of the message.
   * 
   * @param \ZFrame &$data Frame to append.
  */
  public function append(\ZFrame &$data) {}

  /**
   * Add a frame at the top of the message.
   * 
   * @param \ZFrame &$data Frame to prepend.
  */
  public function prepend(\ZFrame &$data) {}

  /**
   * Pop next frame in message.
   * 
   * @return \ZFrame|null
  */
  public function pop() {}

  /**
   * Push a string frame at the end of the message.
   * 
   * @param string $data Data to append.
  */
  public function append_string($data) {}

  /**
   * Add a string frame at the top of the message.
   * 
   * @param string $data Data to prepend.
  */
  public function prepend_string($data) {}

  /**
   * Pop next frame in message as string.
   * 
   * @return string|null
  */
  public function pop_string() {}

  /**
   * Push data frames as specified in the picture format at the end of the message.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function append_picture($picture) {}

  /**
   * Add data frames as specified in the picture format at the top of the message.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function prepend_picture($picture) {}

  /**
   * Pop frames from message as as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
   * @return mixed
  */
  public function pop_picture($picture) {}

  /**
   * Push a ZLib encoded frame at the end of the message.
   * 
   * @param string $data Data to append.
  */
  public function append_zipped($data) {}

  /**
   * Add a ZLib encoded frame at the top of the message.
   * 
   * @param string $data Data to prepend.
  */
  public function prepend_zipped($data) {}

  /**
   * Pop next ZLib decoded frame in message.
   * 
   * @return mixed|null
  */
  public function pop_zipped() {}

  /**
   * Push a MsgPack encoded frame at the end of the message.
   * 
   * @param string $data Data to append.
  */
  public function append_msgpack($data) {}

  /**
   * Add a MsgPack encoded frame at the top of the message.
   * 
   * @param string $data Data to prepend.
  */
  public function prepend_msgpack($data) {}

  /**
   * Pop next MsgPack decoded frame in message.
   * 
   * @return mixed|null
  */
  public function pop_msgpack() {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function append_bson($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function prepend_bson($data) {}

  /**
   * ...
   * 
  */
  public function pop_bson() {}

  /**
   * Send message.
   * 
   * @param IZSocket &$socket ...
  */
  public function send(\IZSocket &$socket) {}

  /**
   * Remove the specified frame from the message.
   * 
   * @param \ZFrame &$frame The frame to remove.
  */
  public function remove(\ZFrame &$frame) {}

  /**
   * Return first frame in message and reset the iterator.
   * 
   * @return \ZFrame|null
  */
  public function first() {}

  /**
   * Return next frame in message and increment the iterator.
   * 
   * @return \ZFrame|null
  */
  public function next() {}

  /**
   * Return last frame in message and put the iterator to the end.
   * 
   * @return \ZFrame|null
  */
  public function last() {}

  /**
   * Return the number of frames in message.
   * 
   * @return int
  */
  public function get_size() {}

  /**
   * Return the size (in bytes) of the entire message.
   * 
   * @return int
  */
  public function get_content_size() {}

  /**
   * Save the message to a file.
   * 
   * @param string $file File name.
  */
  public function save($file) {}

  /**
   * Load message from a file.
   * 
   * @param string $file File name.
  */
  public function load($file) {}

  /**
   * Dump the object to console.
   * 
  */
  public function dump() {}

  /**
   * offsetExists
   *
   * @param mixed $offset
   * @return boolean
   */
  public function offsetExists ( $offset ) {}
  
  /**
   * offsetGet
   *
   * @param mixed $offset
   * @return mixed
   */
  public function offsetGet ( $offset ) {}
  
  /**
   * offsetSet
   *
   * @param mixed $offset
   * @param mixed 
   */
  public function offsetSet ( $offset, $value ) {}
  
  /**
   * offsetUnset
   *
   * @param mixed $offset
   */
  public function offsetUnset ( $offset ) {}
  
  /**
   * count
   *
   * @return int
   */
  public function count () {}
  
}


/**
 * ZFrame
 *
 * Manage single frame in multipart message.
 */
class ZFrame {

  /**
   *  
   * 
   * @return \ZFrame
  */
  public function __construct() {}

  /**
   * Dump the object to console.
   * 
  */
  public function dump() {}

  /**
   * Pack binary data into the frame. Same as php pack function.
   * 
   * @param string $format See php pack.
  */
  public function pack($format) {}

  /**
   * Unpack binary data from the frame. Same as php unpack function.
   * 
   * @param string $format See php unpack.
   * @return mixed
  */
  public function unpack($format) {}

}


/**
 * ZLoop
 *
 * ZeroMQ Loop
 */
class ZLoop {

  /**
   * ...
   * 
   * @return \ZLoop
  */
  public function __construct() {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
   * @param int $max_timers ...
  */
  public function set_max_timers($max_timers) {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  public function stop() {}

  /**
   * ...
   * 
   * @param int|resource|\IZDescriptor|\IZSocket $pollitem ...
   * @param callable $callback ...
   * @param int $mode ... (optional)
  */
  public function add($pollitem, callable $callback, $mode = \ZSys::POLL_IN) {}

  /**
   * ...
   * 
   * @param int|resource|\IZDescriptor|\IZSocket $pollitem ...
  */
  public function remove($pollitem) {}

  /**
   * Add a repeating timer with a callback. Return a timer_id.
   * 
   * @param int $timeout Timeout ms.
   * @param callable $callback The callaback.
   * @param int $repeat How many times the timer will repeat. (optional)
   * @return int
  */
  public function add_timer($timeout, callable $callback, $repeat = 1) {}

  /**
   * Remove the timer 
   * 
   * @param int $timer_id The timer_id returned form add_timer.
  */
  public function remove_timer($timer_id) {}

  /**
   * ...
   * 
  */
  public function ignore_interrupts() {}

}


/**
 * ZPoll
 *
 * ZeroMQ Loop
 */
class ZPoll {

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
   * @param mixed $verbose ... (optional)
  */
  public function set_verbose($verbose) {}

  /**
   * ...
   * 
   * @param int|resource|\IZDescriptor|\IZSocket $pollitem ...
   * @param int $mode ... (optional)
  */
  public function add($pollitem, $mode = \ZSys::POLL_IN) {}

  /**
   * ...
   * 
   * @param int|resource|\IZDescriptor|\IZSocket $pollitem ...
  */
  public function has($pollitem) {}

  /**
   * ...
   * 
   * @param int|resource|\IZDescriptor|\IZSocket $pollitem ...
  */
  public function remove($pollitem) {}

  /**
   * ...
   * 
   * @param int|resource|\IZDescriptor|\IZSocket $pollitem ...
   * @param int $event ... (optional)
  */
  public function check_for($pollitem, $event = \ZSys::POLL_IN) {}

  /**
   * ...
   * 
   * @param int|resource|\IZDescriptor|\IZSocket $pollitem ...
  */
  public function events($pollitem) {}

  /**
   * ...
   * 
   * @param array &$readers ...
   * @param array &$writers ...
   * @param int $timeout ... (optional)
   * @return bool
  */
  public function poll_array(array &$readers, array &$writers, $timeout) {}

  /**
   * ...
   * 
   * @param int $timeout ... (optional)
   * @return bool
  */
  public function poll($timeout = \ZSys::POLL_WAIT_FOREVER) {}

  /**
   * ...
   * 
   * @param int|resource|\IZDescriptor|\IZSocket $pollitem ...
   * @return bool
  */
  public function has_input($pollitem) {}

  /**
   * ...
   * 
   * @param int|resource|\IZDescriptor|\IZSocket $pollitem ...
   * @return bool
  */
  public function has_output($pollitem) {}

  /**
   * ...
   * 
   * @param int|resource|\IZDescriptor|\IZSocket $pollitem ...
   * @return bool
  */
  public function has_error($pollitem) {}

}


/**
 * ZCert
 *
 * Certificate Holder Class
 */
class ZCert {

  /**
   * Create e new Certificate, optionally load it's content from file.
   * 
   * @param string $filename Certificate filename. (optional)
   * @return \ZCert
  */
  public function __construct($filename = null) {}

  /**
   * Return the public key.
   * 
   * @return string
  */
  public function get_public_key() {}

  /**
   * Return the secret key.
   * 
   * @return string
  */
  public function get_secret_key() {}

  /**
   * Return the meta value for the specified key.
   * 
   * @param string $name Meta key.
   * @return string
  */
  public function get_meta($name) {}

  /**
   * Return an array of all available meta keys.
   * 
   * @return array
  */
  public function get_meta_keys() {}

  /**
   * Set the meta value for the specified key.
   * 
   * @param string $name Meta key.
   * @param string $value Meta value.
  */
  public function set_meta($name, $value) {}

  /**
   * Save the certificate to the specified filename.
   * 
   * @param string $filename Certificate filename.
  */
  public function save($filename) {}

  /**
   * Save the public key to the specified file.
   * 
   * @param string $filename Public key filename.
  */
  public function save_public($filename) {}

  /**
   * Save the secret key to the specified file.
   * 
   * @param string $filename Secret key filename.
  */
  public function save_secret($filename) {}

  /**
   * Apply the certificate to the specified socket.
   * 
   * @param \IZSocket &$socket Socket that will got the certificate applied.
  */
  public function apply(\IZSocket &$socket) {}

  /**
   * Dump the object to console.
   * 
  */
  public function dump() {}

}


/**
 * IZDescriptor
 *
 * Basic interface for File Descriptor support.
 */
interface IZDescriptor {

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() ;

}


/**
 * IZSocket
 *
 * Basic interface for ZSocket support.
 */
interface IZSocket extends \IZDescriptor {

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() ;

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() ;

}


/**
 * IZActor
 *
 * ...
 */
interface IZActor extends \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
  */
  public function start() ;

  /**
   * ...
   * 
  */
  static public function run() ;

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() ;

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() ;

}


/**
 * IZEmitter
 *
 * ...
 */
interface IZEmitter {

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) ;

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) ;

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) ;

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) ;

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) ;

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) ;

}


/**
 * ZSocket
 *
 * ZeroMQ Socket
 * @property int $handshake_ivl Get/Set maximum handshake interval. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc15)
 * @property-write string $rid Set the next outbound connection id. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc5) (write only)
 * @property-write bool $conflate Enable/Disable keep only last message. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc6) (write only)
 * @property-write bool $router_handover Enable/Disable handle duplicate client identities on ROUTER sockets. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc35) (write only)
 * @property-write bool $router_mandatory Enable/Disable accept only routable messages on ROUTER sockets. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc36) (write only)
 * @property-write bool $probe_router Enable/Disable bootstrap connections to ROUTER sockets. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc25) (write only)
 * @property-write bool $req_relaxed Enable/Disable relax strict alternation between request and reply. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc34) (write only)
 * @property-write bool $req_correlate Enable/Disable match replies with requests. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc33) (write only)
 * @property-write bool $router_raw Enable/Disable switch ROUTER socket to raw mode (This option is deprecated, please use ZMQ_STREAM sockets instead). [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc37) (write only)
 * @property-write bool $delay_attach_on_connect Enable/Disable  [more..](http://api.zeromq.org/4-1:zmq-setsockopt) (write only)
 * @property-write bool $xpub_verbose Enable/Disable provide all subscription messages on XPUB sockets. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc48) (write only)
 * @property bool $ipv4only Enable/Disable Use IPv4-only on socket (This option is deprecated. Please use the ZMQ_IPV6 option). [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc54)
 * @property int $sndhwm Get/Set high water mark for outbound messages. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc39)
 * @property int $rcvhwm Get/Set high water mark for inbound messages. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc28)
 * @property int $affinity Get/Set I/O thread affinity. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc3)
 * @property string $identity Get/Set socket identity. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc16)
 * @property int $rate Get/Set multicast data rate. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc26)
 * @property int $recovery_ivl Get/Set multicast recovery interval. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc32)
 * @property int $sndbuf Get/Set kernel transmit buffer size. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc38)
 * @property int $rcvbuf Get/Set kernel receive buffer size. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc27)
 * @property int $linger Get/Set linger period for socket shutdown. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc19)
 * @property int $reconnect_ivl Get/Set reconnection interval. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc30)
 * @property int $reconnect_ivl_max Get/Set maximum reconnection interval. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc31)
 * @property int $backlog Get/Set maximum length of the queue of outstanding connections. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc4)
 * @property int $maxmsgsize Get/Set Maximum acceptable inbound message size. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc20)
 * @property int $multicast_hops Get/Set Maximum network hops for multicast packets. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc21)
 * @property int $rcvtimeo Get/Set Maximum time before a recv operation returns with EAGAIN. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc29)
 * @property int $sndtimeo Get/Set Maximum time before a send operation returns with EAGAIN. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc40)
 * @property int $tcp_keepalive Get/Set Override SO_KEEPALIVE socket option [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc42)
 * @property int $tcp_keepalive_idle Get/Set Override TCP_KEEPCNT (or TCP_KEEPALIVE on some OS). [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc44)
 * @property int $tcp_keepalive_cnt Get/Set Override TCP_KEEPCNT socket option. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc43)
 * @property int $tcp_keepalive_intvl Get/Set Override TCP_KEEPINTVL socket option. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc45)
 * @property string $tcp_accept_filter Get/Set filters to allow new TCP connections (This option is deprecated, please use authentication via the ZAP API and IP address whitelisting / blacklisting). [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc50)
 * @property-read string $type Get ZSocket type. (read only)
 * @property-read string $mechanism Get current security mechanism configured for socket. (read only)
 * @property-read string $last_endpoint Get the last known connected/binded endpoint. (read only)
 * @property-read int $events Get the current events for socket. (read only)
 * @property-read bool $rcvmore Get More message data parts to follow. (read only)
 * @property int $tos Get/Set the Type-of-Service on socket. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc46)
 * @property string $zap_domain Get/Set RFC 27 authentication domain. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc49)
 * @property bool $plain_server Enable/Disable PLAIN server role. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc23)
 * @property string $plain_username Get/Set PLAIN security username. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc24)
 * @property string $plain_password Get/Set PLAIN security password. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc22)
 * @property bool $curve_server Enable/Disable CURVE server role. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc9)
 * @property string $curve_publickey Set CURVE public key. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc7)
 * @property string $curve_secretkey Set CURVE secret key. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc8)
 * @property string $curve_serverkey Set CURVE server key. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc10)
 * @property bool $gssapi_server Enable/Disable GSSAPI server role. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc13)
 * @property bool $gssapi_plaintext Enable/Disable GSSAPI encryption. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc11)
 * @property string $gssapi_principal Get/Set name of GSSAPI principal. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc12)
 * @property string $gssapi_service_principal Get/Set name of GSSAPI service principal. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc14)
 * @property bool $ipv6 Enable/Disable IPv6 on socket. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc18)
 * @property bool $immediate Enable/Disable queue messages only to completed connections. [more..](http://api.zeromq.org/4-1:zmq-setsockopt#toc17)
 */
class ZSocket implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param mixed $type The socket type to be created.
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  public function __construct($type, $endpoint = null) {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * Set socket to use unbounded pipes (HWM=0); use this in cases when you are totally certain the message volume can fit in memory
   * 
  */
  public function set_unbounded() {}

  /**
   * Bind to the specified endpoint(s).
   * 
   * @param string|array $endpoint Endpoint(s) to bind. (see [Endpoint Format](http://www.google.com))
   * @return bool
  */
  public function bind($endpoint) {}

  /**
   * Unbind from the specified endpoint(s).
   * 
   * @param string $endpoint Endpoint(s) to unbind from.
  */
  public function unbind($endpoint) {}

  /**
   * Connect to the specified endpoint(s).
   * 
   * @param string|array $endpoint Endpoint(s) to connect to. (see [Endpoint Format](http://www.google.com))
   * @return bool
  */
  public function connect($endpoint) {}

  /**
   * Disconnect from the specified endpoint(s).
   * 
   * @param string $endpoint Endpoint(s) to disconnect from.
  */
  public function disconnect($endpoint) {}

  /**
   *  Send a signal over a socket. A signal is a short message carrying a success/failure code (by convention, 0 means OK).
   * * Signals are encoded to be distinguishable from 'normal' messages
   * 
   * @param int $byte ...
   * @return bool
  */
  public function signal($byte) {}

  /**
   * Wait on a signal. Use this to coordinate between threads, over pipe pairs. Blocks until the signal is received.
   * 
   * @return bool
  */
  public function wait() {}

  /**
   * If there is a partial message still waiting on the socket, remove and discard it. This is useful
   * * when reading partial messages, to get specific message types.
   * 
  */
  public function flush() {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param string $data The string to send
  */
  public function send_string($data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function send_picture($picture) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $data The data to send.
  */
  public function send_msgpack($data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function send_bson($data) {}

  /**
   * Create a PUB socket. Default action is bind.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function pub($endpoint = null) {}

  /**
   * Create a SUB socket, and optionally subscribe to some prefix string. Default action is connect.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @param string $topic Topic to subscribe. (optional)
   * @return \ZSocket
  */
  static public function sub($endpoint = null, $topic = null) {}

  /**
   * Create a REP socket. Default action is bind.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function rep($endpoint = null) {}

  /**
   * Create a REQ socket. Default action is connect.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function req($endpoint = null) {}

  /**
   * Create a DEALER socket. Default action is connect.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function dealer($endpoint = null) {}

  /**
   * Create a ROUTER socket. Default action is bind.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function router($endpoint = null) {}

  /**
   * Create a PUSH socket. Default action is connect.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function push($endpoint = null) {}

  /**
   * Create a PULL socket. Default action is bind.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function pull($endpoint = null) {}

  /**
   * Create an XPUB socket. Default action is bind.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function xpub($endpoint = null) {}

  /**
   * Create an XSUB socket. Default action is connect.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function xsub($endpoint = null) {}

  /**
   * Alias for ROUTER socket. Default action is bind.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function xreq($endpoint = null) {}

  /**
   * Alias for DEALER socket. Default action is connect.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function xrep($endpoint = null) {}

  /**
   * Create a PAIR socket. Default action is connect.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function pair($endpoint = null) {}

  /**
   * Create a STREAM socket. Default action is connect.
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function stream($endpoint = null) {}

  /**
   * Create a SERVER socket. Default action is bind. (Requires ZMQ > 4.2.0)
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function server($endpoint = null) {}

  /**
   * Create a CLIENT socket. Default action is connect. (Requires ZMQ > 4.2.0)
   * 
   * @param string $endpoint Endpoint to connect or bind. (see [Endpoint Format](http://www.google.com)) (optional)
   * @return \ZSocket
  */
  static public function client($endpoint = null) {}

  /**
   * Return a map of socket options values.
   * 
   * @return array
  */
  public function get_options() {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * Subscribe a specific topic. (only ZMQ_SUB socket type).
   * 
   * @param string $topic Topic name.
  */
  public function subscribe($topic) {}

  /**
   * Unsubscribe a specific topic. (only ZMQ_SUB socket type).
   * 
   * @param string $topic Topic name.
  */
  public function unsubscribe($topic) {}

}


/**
 * ZProxy
 *
 * Run a steerable proxy in background. The proxy switches messages between a frontend socket and a backend socket. Supports pause / resume.
 */
class ZProxy implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   *  
   * 
   * @param mixed $verbose ... (optional)
   * @return \ZProxy
  */
  public function __construct($verbose) {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * Put the proxy in pause.
   * 
  */
  public function pause() {}

  /**
   * Resume the proxy activity.
   * 
  */
  public function resume() {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Set frontend socket type and endpoint.
   * 
   * @param string $type Frontend socket type.
   * @param string $endpoint Frontend endpoint.
  */
  public function set_frontend($type, $endpoint) {}

  /**
   * Set backend socket type and endpoint.
   * 
   * @param string $type Backend socket type.
   * @param string $endpoint Backend endpoint.
  */
  public function set_backend($type, $endpoint) {}

  /**
   * Capture all proxied messages; these are delivered to the application via an inproc PULL socket
   * * that you have already bound to the specified endpoint
   * 
   * @param string $endpoint Capture endpoint.
  */
  public function set_capture($endpoint) {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * Start the proxy in it's own loop.
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}


/**
 * ZBeacon
 *
 * ...
 */
class ZBeacon implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * ...
   * 
   * @param mixed $verbose ... (optional)
   * @return \ZBeacon
  */
  public function __construct($verbose) {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * Configure Udp port number. Return hostname or false if cannot bind.
   * 
   * @param int $port ...
   * @return string
  */
  public function set_port($port) {}

  /**
   * ...
   * 
   * @param string $filter ...
  */
  public function subscribe($filter) {}

  /**
   * ...
   * 
  */
  public function unsubscribe() {}

  /**
   * ...
   * 
   * @param string $data ...
   * @param int $interval ... (optional)
  */
  public function publish($data, $interval) {}

  /**
   * ...
   * 
  */
  public function silence() {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}


/**
 * ZAuth
 *
 * Authentication for ZeroMQ security mechanisms.
 */
class ZAuth implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {
  const AUTH_PLAIN = "PLAIN";
  const AUTH_CURVE = "CURVE";
  const AUTH_GSSAPI = "GSSAPI";


  /**
   *  
   * 
   * @param mixed $verbose ... (optional)
   * @return \ZAuth
  */
  public function __construct($verbose) {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Allow (whitelist) a list of IP addresses. For NULL, all clients from
   * these addresses will be accepted. For PLAIN and CURVE, they will be
   * allowed to continue with authentication. You can call this method
   * multiple times to whitelist more IP addresses. If you whitelist one
   * or nmore addresses, any non-whitelisted addresses are treated as
   * blacklisted
   * 
   * @param string $ip ip address
  */
  public function allow($ip) {}

  /**
   * Deny (blacklist) a list of IP addresses. For all security mechanisms,
   * this rejects the connection without any further authentication. Use
   * either a whitelist, or a blacklist, not not both. If you define both
   * a whitelist and a blacklist, only the whitelist takes effect
   * 
   * @param string $ip ip address
  */
  public function deny($ip) {}

  /**
   *  
   * 
   * @param string $mode ...
   * @param string $path ... (optional)
  */
  public function configure($mode, $path) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

}


/**
 * ZGossip
 *
 * Decentralized configuration management.
 */
class ZGossip implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   *  
   * 
   * @param bool $verbose Enable verbose mode debug outputs are shown. (optional)
   * @return \ZGossip
  */
  public function __construct($verbose = false) {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
   * @param string $filename ...
  */
  public function configure($filename) {}

  /**
   * Bind to the specified endpoint(s).
   * 
   * @param string|array $endpoint Endpoint(s) to bind. (see [Endpoint Format](http://www.google.com))
   * @return bool
  */
  public function bind($endpoint) {}

  /**
   * Connect to the specified endpoint(s).
   * 
   * @param string|array $endpoint Endpoint(s) to connect to. (see [Endpoint Format](http://www.google.com))
   * @return bool
  */
  public function connect($endpoint) {}

  /**
   * ...
   * 
   * @param string $property ...
   * @param string $value ...
  */
  public function set($property, $value) {}

  /**
   * ...
   * 
   * @param string $property ...
   * @param string $value ...
  */
  public function publish($property, $value) {}

  /**
   * ...
   * 
  */
  public function count() {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}


/**
 * ZInotify
 *
 * Inotify watcher.
 */
class ZInotify implements \IZDescriptor {
  const IN_ACCESS = 0x00000001;
  const IN_MODIFY = 0x00000002;
  const IN_ATTRIB = 0x00000004;
  const IN_CLOSE_WRITE = 0x00000008;
  const IN_CLOSE_NOWRITE = 0x00000010;
  const IN_OPEN = 0x00000020;
  const IN_MOVED_FROM = 0x00000040;
  const IN_MOVED_TO = 0x00000080;
  const IN_CREATE = 0x00000100;
  const IN_DELETE = 0x00000200;
  const IN_DELETE_SELF = 0x00000400;
  const IN_MOVE_SELF = 0x00000800;
  const IN_UNMOUNT = 0x00002000;
  const IN_Q_OVERFLOW = 0x00004000;
  const IN_IGNORED = 0x00008000;
  const IN_CLOSE = 0x00000018;
  const IN_MOVE = 0x000000c0;
  const IN_ONLYDIR = 0x01000000;
  const IN_DONT_FOLLOW = 0x02000000;
  const IN_EXCL_UNLINK = 0x04000000;
  const IN_MASK_ADD = 0x20000000;
  const IN_ISDIR = 0x40000000;
  const IN_ONESHOT = 0x80000000;
  const IN_ALL_EVENTS = 0x00000fff;


  /**
   * Start watching and inode for events. Return a watch_id.
   * 
   * @param string $file The inode to watch.
   * @param int $events Bitwise mask of events to watch.
   * @return int
  */
  public function watch($file, $events) {}

  /**
   * Stop watching watch_id.
   * 
   * @param int $watch_id The watch_id returned from previous 'watch' call.
  */
  public function remove($watch_id) {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

}


/**
 * ZStdIn
 *
 * Simple wrap for StdIn.
 */
class ZStdIn implements \IZDescriptor {

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

}


/**
 * ZStdOut
 *
 * Simple wrap for StdOut.
 */
class ZStdOut implements \IZDescriptor {

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

}


/**
 * ZStdErr
 *
 * Simple wrap for StdErr.
 */
class ZStdErr implements \IZDescriptor {

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

}

}

namespace Zyre {

/**
 * Zyre
 *
 * Zyre does local area discovery and clustering. A Zyre node broadcasts UDP beacons, and connects to peers that it finds.
 */
class Zyre implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * Creates a new Zyre node. Note that until you start the node it is silent and invisible to other nodes on the network.
   * 
   * @param string $name Zyre node name. (optional)
   * @return \Zyre\Zyre
  */
  public function __construct($name = null) {}

  /**
   * Connect to the specified endpoint(s).
   * 
   * @return bool
  */
  public function connect() {}

  /**
   * Disconnect from the specified endpoint(s).
   * 
  */
  public function disconnect() {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Dump the object to console.
   * 
  */
  public function dump() {}

  /**
   * Get the UUID of the Zyre node
   * 
   * @return string
  */
  public function get_uuid() {}

  /**
   * Get then Zyre node name.
   * 
   * @return string
  */
  public function get_name() {}

  /**
   * Return a list of known peers.
   * 
   * @return array
  */
  public function get_peers() {}

  /**
   * Return a list of known groups.
   * 
   * @return array
  */
  public function get_groups() {}

  /**
   * ...
   * 
  */
  public function get_peer_groups() {}

  /**
   * By default, Zyre binds to an ephemeral TCP port and broadcasts the local
   * host name using UDP beaconing. When you call this method, Zyre will use
   * gossip discovery instead of UDP beaconing. You MUST set-up the gossip
   * service separately using zyre_gossip_bind() and _connect(). Note that the
   * endpoint MUST be valid for both bind and connect operations. You can use
   * inproc://, ipc://, or tcp:// transports (for tcp://, use an IP address
   * that is meaningful to remote as well as local nodes). Returns true if
   * the bind was successful.
   * 
   * @param string $endpoint  
  */
  public function set_endpoint($endpoint) {}

  /**
   * Set UDP beacon discovery port; defaults to 5670, this call overrides that so you can create independent clusters on the same network, for e.g. development vs. production. Has no effect after node start.
   * 
   * @param int $port ...
  */
  public function set_port($port) {}

  /**
   * Set network interface for UDP beacons. If you do not set this, CZMQ will
   * choose an interface for you. On boxes with several interfaces you should
   * specify which one you want to use, or strange things can happen.
   * 
   * @param string $interface  
  */
  public function set_interface($interface) {}

  /**
   * Set UDP beacon discovery interval, in milliseconds. Default is instant beacon exploration followed by pinging every 1,000 msecs.
   * 
   * @param int $interval ...
  */
  public function set_interval($interval) {}

  /**
   * Set-up gossip discovery of other nodes. At least one node in the cluster
   * must bind to a well-known gossip endpoint, so other nodes can connect to
   * it. Note that gossip endpoints are completely distinct from Zyre node
   * endpoints, and should not overlap (they can use the same transport).   
   * 
   * @param string $endpoint  
  */
  public function gossip_bind($endpoint) {}

  /**
   * Set-up gossip discovery of other nodes. A node may connect to multiple
   * other nodes, for redundancy paths. For details of the gossip network
   * design, see the CZMQ zgossip class.      
   * 
   * @param string $endpoint  
  */
  public function gossip_connect($endpoint) {}

  /**
   * Return the value of a header of a conected peer.
   * 
   * @param string $name  
   * @return mixed
  */
  public function get_peer_header($name) {}

  /**
   * Get Zyre version.
   * 
   * @return string
  */
  static public function get_version() {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * Set node header; these are provided to other nodes during discovery and come in each ENTER message.
   * 
   * @param string $name ...
   * @param string $value ...
  */
  public function set_header($name, $value) {}

  /**
   * Join a named group; after joining a group you can send messages to the group and all Zyre nodes in that group will receive them.
   * 
   * @param string $group Group name to join.
  */
  public function join($group) {}

  /**
   * Leave a joined group
   * 
   * @param string $group Group name to leave.
  */
  public function leave($group) {}

  /**
   * Send message to single peer, specified as a UUID string.
   * 
   * @param string $peer Peer UUID.
   * @param mixed $data ...
  */
  public function send_peer($peer, $data) {}

  /**
   * Send message to a named group.
   * 
   * @param string $group Group name.
   * @param mixed $data ...
  */
  public function send_group($group, $data) {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * Start node, after setting header values. When you start a node it begins discovery and connection.
   * 
   * @return bool
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}

}

namespace Majordomo {

/**
 * Broker
 *
 * Majordomo Broker
 */
class Broker implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
   * @param mixed $verbose ... (optional)
   * @return \Majordomo\Broker
  */
  public function __construct($endpoint, $verbose) {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * Bind to the specified endpoint(s).
   * 
   * @param string|array $endpoint Endpoint(s) to bind. (see [Endpoint Format](http://www.google.com))
   * @return bool
  */
  public function bind($endpoint) {}

  /**
   * Load the configuration data from a file.
   * 
   * @param string $filename File name.
  */
  public function load_config($filename) {}

  /**
   * Save the configuration data to a file.
   * 
   * @param string $filename File name.
  */
  public function save_config($filename) {}

  /**
   * Set a config key to a specific value.
   * 
   * @param string $key Configuration key.
   * @param string $value Configuration value.
  */
  public function set_config($key, $value) {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param string $data The string to send
  */
  public function send_string($data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function send_picture($picture) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $data The data to send.
  */
  public function send_msgpack($data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function send_bson($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}


/**
 * Worker
 *
 * ...
 */
class Worker implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * ...
   * 
   * @param mixed $name ...
   * @param mixed $broker_endpoint ...
   * @return \Majordomo\Worker
  */
  public function __construct($name, $broker_endpoint) {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param string $data The string to send
  */
  public function send_string($data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function send_picture($picture) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $data The data to send.
  */
  public function send_msgpack($data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function send_bson($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}


/**
 * Client
 *
 * ...
 */
class Client implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param string $broker_endpoint ...
   * @return \Majordomo\Client
  */
  public function __construct($broker_endpoint) {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
   * @param string $service_name ...
   * @return \ZMsg
  */
  public function call($service_name) {}

  /**
   * ...
   * 
   * @param string $service_name ...
   * @return bool
  */
  public function call_async($service_name) {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param string $data The string to send
  */
  public function send_string($data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function send_picture($picture) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $data The data to send.
  */
  public function send_msgpack($data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function send_bson($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

}


/**
 * Titanic
 *
 * ...
 */
class Titanic implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * ...
   * 
   * @param string $endpoint ...
   * @param ITitanicStorage $storage ... (optional)
   * @param int $threads ... (optional)
   * @return \Majordomo\Titanic
  */
  public function __construct($endpoint, ITitanicStorage $storage = null, $threads) {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param string $data The string to send
  */
  public function send_string($data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function send_picture($picture) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $data The data to send.
  */
  public function send_msgpack($data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function send_bson($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}


/**
 * ITitanicStorage
 *
 * ...
 */
interface ITitanicStorage {

  /**
   * ...
   * 
   * @param string $what ...
   * @param string $uuid ...
   * @return \ZMsg
  */
  public function read($what, $uuid) ;

  /**
   * ...
   * 
   * @param string $what ...
   * @param string $uuid ...
   * @param \ZMsg $msg ...
  */
  public function store($what, $uuid, \ZMsg $msg) ;

  /**
   * ...
   * 
   * @param string $uuid ...
  */
  public function close($uuid) ;

  /**
   * ...
   * 
   * @param string $uuid ...
  */
  public function status($uuid) ;

  /**
   * ...
   * 
   * @return string|null
  */
  public function process() ;

}

}

namespace Malamute {

/**
 * Broker
 *
 * ...
 */
class Broker implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * ...
   * 
   * @param mixed $endpoint ...
   * @param array $options ... (optional)
   * @return \Malamute\Broker
  */
  public function __construct($endpoint, array $options) {}

  /**
   * Bind to the specified endpoint(s).
   * 
   * @param string|array $endpoint Endpoint(s) to bind. (see [Endpoint Format](http://www.google.com))
   * @return bool
  */
  public function bind($endpoint) {}

  /**
   * Load the configuration data from a file.
   * 
   * @param string $filename File name.
  */
  public function load_config($filename) {}

  /**
   * Save the configuration data to a file.
   * 
   * @param string $filename File name.
  */
  public function save_config($filename) {}

  /**
   * Set a config key to a specific value.
   * 
   * @param string $key Configuration key.
   * @param string $value Configuration value.
  */
  public function set_config($key, $value) {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param string $data The string to send
  */
  public function send_string($data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function send_picture($picture) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $data The data to send.
  */
  public function send_msgpack($data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function send_bson($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}


/**
 * Worker
 *
 * ...
 */
class Worker implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * ...
   * 
   * @param string $endpoint ...
   * @param mixed $name ...
   * @return \Malamute\Worker
  */
  public function __construct($endpoint, $name) {}

  /**
   * ...
   * 
   * @param mixed $header ... (optional)
  */
  public function headers($header) {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param string $data The string to send
  */
  public function send_string($data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function send_picture($picture) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $data The data to send.
  */
  public function send_msgpack($data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function send_bson($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}


/**
 * Client
 *
 * ...
 */
class Client implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param string $endpoint ...
   * @param string $address ... (optional)
   * @param mixed $username ... (optional)
   * @param mixed $password ... (optional)
   * @return \Malamute\Client
  */
  public function __construct($endpoint = null, $address = null, $username, $password) {}

  /**
   * ...
   * 
   * @param mixed $service ...
   * @param mixed $data ...
  */
  public function call_async($service, $data) {}

  /**
   * ...
   * 
   * @param mixed $service ...
   * @param mixed $data ...
  */
  public function call($service, $data) {}

  /**
   * ...
   * 
  */
  public function headers() {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

}


/**
 * Producer
 *
 * ...
 */
class Producer implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * ...
   * 
   * @param string $endpoint ...
   * @param string $stream ...
   * @return \Malamute\Producer
  */
  public function __construct($endpoint, $stream) {}

  /**
   * Send message.
   * 
   * @param mixed $subject ...
   * @param mixed $data Data to send.
  */
  public function send($subject, $data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param mixed $subject ...
   * @param string $data The string to send
  */
  public function send_string($subject, $data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param mixed $subject ...
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
   * @param mixed $data ...
  */
  public function send_picture($subject, $picture, $data) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $subject ...
   * @param mixed $data The data to send.
  */
  public function send_msgpack($subject, $data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $subject ...
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($subject, $data) {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}


/**
 * Consumer
 *
 * ...
 */
class Consumer implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * ...
   * 
   * @param string $endpoint ...
   * @param string $stream ... (optional)
   * @return \Malamute\Consumer
  */
  public function __construct($endpoint, $stream) {}

  /**
   * ...
   * 
   * @param mixed $stream ...
  */
  public function consume($stream) {}

  /**
   * ...
   * 
   * @param mixed $header ... (optional)
  */
  public function headers($header) {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}

}

namespace FileMq {

/**
 * Server
 *
 * ...
 */
class Server implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * ...
   * 
   * @param mixed $endpoint ...
   * @param array $options ... (optional)
   * @return \FileMq\Server
  */
  public function __construct($endpoint, array $options) {}

  /**
   * Enable verbose mode, debug outputs are shown.
   * 
  */
  public function set_verbose() {}

  /**
   * Bind to the specified endpoint(s).
   * 
   * @param string|array $endpoint Endpoint(s) to bind. (see [Endpoint Format](http://www.google.com))
   * @return bool
  */
  public function bind($endpoint) {}

  /**
   * ...
   * 
   * @param string $local_path ...
   * @param string $alias ...
  */
  public function publish($local_path, $alias) {}

  /**
   * Load the configuration data from a file.
   * 
   * @param string $filename File name.
  */
  public function load_config($filename) {}

  /**
   * Save the configuration data to a file.
   * 
   * @param string $filename File name.
  */
  public function save_config($filename) {}

  /**
   * Set a config key to a specific value.
   * 
   * @param string $key Configuration key.
   * @param string $value Configuration value.
  */
  public function set_config($key, $value) {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param string $data The string to send
  */
  public function send_string($data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function send_picture($picture) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $data The data to send.
  */
  public function send_msgpack($data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function send_bson($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}


/**
 * Client
 *
 * FileMQ Client
 */
class Client implements \IZActor, \IZDescriptor, \IZSocket, \IZEmitter {

  /**
   * Create e new instance.
   * 
   * @param string $endpoint FileMQ Server endpoint.
   * @param string $local_path Local folder to sync with server.
   * @param int $timeout Connect timeout. 0 means infinite. (optional)
   * @return \FileMq\Client
  */
  public function __construct($endpoint, $local_path, $timeout = 0) {}

  /**
   * ...
   * 
   * @param string $remote_path ...
  */
  public function subscribe($remote_path) {}

  /**
   * Register an event listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Callback.
  */
  public function on($event, callable $listener) {}

  /**
   * Register an event listener to be executed once.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function once($event, callable $listener) {}

  /**
   * Remove a registered listener.
   * 
   * @param string $event Event name.
   * @param callable $listener Event callback.
  */
  public function remove_listener($event, callable $listener) {}

  /**
   * Remove all registered listeners for the event.
   * 
   * @param string $event Event name. (optional)
  */
  public function remove_all_listeners($event) {}

  /**
   * Return the listeners registered for the event.
   * 
   * @param string $event Event name.
   * @return array|null
  */
  public function listeners($event) {}

  /**
   * Emit an event.
   * 
   * @param string $event Event name.
   * @param array $arguments Event arguments.
  */
  public function emit($event, array $arguments = []) {}

  /**
   * Recieve next message from the socket.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Recieve a message and pop first frame as string.
   * 
   * @return string
  */
  public function recv_string() {}

  /**
   * Recieve a message and pop frames as indicated in the picture format specified.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to extract from message.
   * @return mixed
  */
  public function recv_picture($picture) {}

  /**
   * Recieve a message and pop first frame decoding with MsgPack.
   * 
   * @return mixed
  */
  public function recv_msgpack() {}

  /**
   * Recieve a message and pop first frame decoding with ZLib.
   * 
   * @return mixed
  */
  public function recv_zipped() {}

  /**
   * ...
   * 
  */
  public function recv_bson() {}

  /**
   * Send message.
   * 
   * @param mixed $data Data to send.
  */
  public function send($data) {}

  /**
   * Send a one frame only message with a string.
   * 
   * @param string $data The string to send
  */
  public function send_string($data) {}

  /**
   * Send a message composed by data frames as specified in the picture format.
   * 
   * @param string $picture Positional string indicating the sequence and data type(s) to push in message.
  */
  public function send_picture($picture) {}

  /**
   * Send a one frame only message encoded with MsgPack.
   * 
   * @param mixed $data The data to send.
  */
  public function send_msgpack($data) {}

  /**
   * Send a one frame only message encoded with ZLib.
   * 
   * @param mixed $data The data to be encoded.
  */
  public function send_zipped($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
  */
  public function send_bson($data) {}

  /**
   * Get the underlying File Descriptor.
   * 
   * @return int
  */
  public function get_fd() {}

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * ...
   * 
  */
  static public function run() {}

}

}

namespace MsgPack {

/**
 * MsgPack
 *
 * MsgPack is a static class which offers customizable encoding/decoding support for msgpack format.
 * Supports basic php types and objects (only public properties).
 */
class MsgPack {

  /**
   * Encode the specified data.
   * 
   * @param mixed $data The data to be encoded.
   * @param callable $encoder An encoder callback used to custom encode objects. (optional)
   * @return mixed
  */
  static public function encode($data, callable $encoder = null) {}

  /**
   * Decode the specified msgpack data.
   * 
   * @param mixed $data The data to be decoded.
   * @param callable $decoder A decode callback used to custom decode objects. (optional)
   * @return mixed
  */
  static public function decode($data, callable $decoder = null) {}

}

}

namespace Bson {

/**
 * Bson
 *
 * ...
 */
class Bson {

  /**
   * ...
   * 
   * @param mixed $data ...
   * @return mixed
  */
  static public function encode($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
   * @return mixed
  */
  static public function decode($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
   * @return mixed
  */
  static public function json_to_bson($data) {}

  /**
   * ...
   * 
   * @param mixed $data ...
   * @return mixed
  */
  static public function bson_to_json($data) {}

}

}
