<?php

namespace {

/**
 * ZSys
 *
 * ZMQ System
 */
class ZSys {
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
  const EVENT_CLOSED = 128;
  const EVENT_CONNECTED = 1;
  const EVENT_CONNECT_DELAYED = 2;
  const EVENT_CONNECT_RETRIED = 4;
  const EVENT_LISTENING = 8;
  const EVENT_BIND_FAILED = 16;
  const EVENT_ACCEPTED = 32;
  const EVENT_ACCEPT_FAILED = 64;
  const EVENT_CLOSE_FAILED = 256;
  const EVENT_DISCONNECTED = 512;
  const EVENT_MONITOR_STOPPED = 1024;
  const EVENT_ALL = 65535;
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
   * Return Malamute version
   * 
   * @return string
  */
  static public function libmlm_version() {}

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
   * Verbose logging
   * 
  */
  public function set_verbose() {}

  /**
   * Send a ZMsg.
   * 
  */
  public function send() {}

  /**
   * Recieve a ZMsg.
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
 * ZMsg
 *
 * Multipart message handling
 */
class ZMsg {

  /**
   *  
   * 
   * @return \ZMsg
  */
  public function __construct() {}

  /**
   * ...
   * 
   * @param string $picture ...
  */
  public function append_picture($picture) {}

  /**
   * ...
   * 
   * @param string $picture ...
  */
  public function prepend_picture($picture) {}

  /**
   * ...
   * 
   * @param string $picture ...
   * @return array
  */
  public function pop_picture($picture) {}

  /**
   * ...
   * 
   * @param \ZFrame $frame ...
  */
  public function append(\ZFrame $frame) {}

  /**
   * ...
   * 
   * @param \ZFrame $frame ...
  */
  public function prepend(\ZFrame $frame) {}

  /**
   * ...
   * 
   * @return \ZFrame
  */
  public function pop() {}

  /**
   * ...
   * 
   * @param string $data ...
  */
  public function append_string($data) {}

  /**
   * ...
   * 
   * @param string $data ...
  */
  public function prepend_string($data) {}

  /**
   * ...
   * 
   * @return string
  */
  public function pop_string() {}

  /**
   * Send a ZMsg
   * 
   * @param \IZSocket $socket ...
  */
  public function send(\IZSocket $socket) {}

  /**
   * ...
   * 
   * @param \ZFrame $frame ...
  */
  public function remove(\ZFrame $frame) {}

  /**
   * ...
   * 
   * @return \ZFrame
  */
  public function first() {}

  /**
   * ...
   * 
   * @return \ZFrame
  */
  public function next() {}

  /**
   * ...
   * 
   * @return \ZFrame
  */
  public function last() {}

  /**
   * ...
   * 
   * @return int
  */
  public function get_size() {}

  /**
   * ...
   * 
   * @return int
  */
  public function get_content_size() {}

  /**
   * ...
   * 
  */
  public function dump() {}

}


/**
 * ZFrame
 *
 * ...
 */
class ZFrame {

  /**
   * ...
   * 
   * @return \ZFrame
  */
  public function __construct() {}

  /**
   * ...
   * 
  */
  public function dump() {}

  /**
   * ...
   * 
   * @param string $format ...
  */
  public function pack($format) {}

  /**
   * ...
   * 
   * @param string $format ...
  */
  public function unpack($format) {}

}


/**
 * ZLoop
 *
 * ...
 */
class ZLoop {

  /**
   * ...
   * 
   * @return \ZLoop
  */
  public function __construct() {}

  /**
   * ...
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
   * @param \IZDescriptor $socket ...
   * @param int $mode ... (optional)
  */
  public function add(\IZDescriptor $socket, $mode = \ZSys::POLL_IN) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
  */
  public function remove(\IZDescriptor $socket) {}

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
 * ...
 */
class ZPoll {

  /**
   * ...
   * 
   * @param bool $verbose ... (optional)
  */
  public function set_verbose($verbose) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
   * @param int $mode ... (optional)
  */
  public function add(\IZDescriptor $socket, $mode = \ZSys::POLL_IN) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
  */
  public function has(\IZDescriptor $socket) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
  */
  public function remove(\IZDescriptor $socket) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
   * @param int $event ... (optional)
  */
  public function check_for(\IZDescriptor $socket, $event = \ZSys::POLL_IN) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
  */
  public function events(\IZDescriptor $socket) {}

  /**
   * ...
   * 
   * @param int $timeout ... (optional)
  */
  public function poll($timeout = \ZSys::POLL_WAIT_FOREVER) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
   * @return bool
  */
  public function has_input(\IZDescriptor $socket) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
   * @return bool
  */
  public function has_output(\IZDescriptor $socket) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
   * @return bool
  */
  public function has_error(\IZDescriptor $socket) {}

}


/**
 * ZCert
 *
 * Certificate Holder Class
 */
class ZCert {

  /**
   * ...
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
   * Return the public key.
   * 
   * @return string
  */
  public function get_public_key_txt() {}

  /**
   * Return the secret key.
   * 
   * @return string
  */
  public function get_secret_key_txt() {}

  /**
   * ...
   * 
   * @param string $name ...
   * @return string
  */
  public function get_meta($name) {}

  /**
   * ...
   * 
   * @return array
  */
  public function get_meta_keys() {}

  /**
   * ...
   * 
   * @param string $name ...
   * @param string $value ...
  */
  public function set_meta($name, $value) {}

  /**
   * ...
   * 
   * @param string $filename ...
  */
  public function save($filename) {}

  /**
   * ...
   * 
   * @param string $filename ...
  */
  public function save_public($filename) {}

  /**
   * ...
   * 
   * @param string $filename ...
  */
  public function save_secret($filename) {}

  /**
   * ...
   * 
   * @param \IZSocket $socket ...
  */
  public function apply(\IZSocket $socket) {}

  /**
   * ...
   * 
  */
  public function dump() {}

}


/**
 * ZCertStore
 *
 * ...
 */
class ZCertStore {

  /**
   * ...
   * 
   * @param string $certificates_dir ... (optional)
   * @return \ZCertStore
  */
  public function __construct($certificates_dir = null) {}

  /**
   * ...
   * 
   * @param string $pubkey ...
   * @return \ZCert
  */
  public function lookup($pubkey) {}

  /**
   * ...
   * 
   * @param \ZCert $cert ...
  */
  public function insert(\ZCert $cert) {}

  /**
   * ...
   * 
  */
  public function dump() {}

}


/**
 * ZMonitor
 *
 * ...
 */
class ZMonitor implements \IZSocket, \IZDescriptor {
  const EVT_CONNECTED = "CONNECTED";
  const EVT_CONNECT_DELAYED = "CONNECT_DELAYED";
  const EVT_CONNECT_RETRIED = "CONNECT_RETRIED";
  const EVT_LISTENING = "LISTENING";
  const EVT_BIND_FAILED = "BIND_FAILED";
  const EVT_ACCEPTED = "ACCEPTED";
  const EVT_ACCEPT_FAILED = "ACCEPT_FAILED";
  const EVT_CLOSED = "CLOSED";
  const EVT_CLOSE_FAILED = "CLOSE_FAILED";
  const EVT_DISCONNECTED = "DISCONNECTED";
  const EVT_MONITOR_STOPPED = "MONITOR_STOPPED";
  const EVT_ALL = "ALL";


  /**
   * ...
   * 
   * @param \IZSocket $socket ...
   * @return \ZMonitor
  */
  public function __construct(\IZSocket $socket) {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
   * @param int $event ...
  */
  public function listen($event) {}

  /**
   * ...
   * 
  */
  public function start() {}

  /**
   * Recieve a ZMsg.
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

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

}


/**
 * IZDescriptor
 *
 * ...
 */
interface IZDescriptor {

  /**
   * ...
   * 
   * @return int
  */
  public function get_fd() ;

}


/**
 * IZSocket
 *
 * ...
 */
interface IZSocket extends \IZDescriptor {

  /**
   * ...
   * 
   * @return \ZSocket
  */
  public function get_socket() ;

  /**
   * ...
   * 
   * @return int
  */
  public function get_fd() ;

}


/**
 * ZSocket
 *
 * ...
 */
class ZSocket implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param string $socket_type ...
   * @param string $endpoint ... (optional)
   * @return \ZSocket
  */
  public function __construct($socket_type, $endpoint) {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
  */
  public function set_unbounded() {}

  /**
   * ...
   * 
   * @param string $endpoint ...
  */
  public function bind($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ...
  */
  public function unbind($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ...
  */
  public function connect($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ...
  */
  public function disconnect($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoints ...
   * @param bool $serverish ... (optional)
  */
  public function attach($endpoints, $serverish = false) {}

  /**
   * ...
   * 
   * @param int $byte ...
  */
  public function signal($byte) {}

  /**
   * ...
   * 
  */
  public function wait() {}

  /**
   * ...
   * 
  */
  public function flush() {}

  /**
   * ...
   * 
  */
  public function get_socket_type() {}

  /**
   * ...
   * 
   * @param string $data ...
  */
  public function send($data) {}

  /**
   * ...
   * 
  */
  public function recv() {}

  /**
   * ...
   * 
   * @param string $data ...
  */
  public function send_string($data) {}

  /**
   * ...
   * 
  */
  public function recv_string() {}

  /**
   * ...
   * 
   * @param string $picture ...
  */
  public function send_picture($picture) {}

  /**
   * ...
   * 
   * @param string $picture ...
  */
  public function recv_picture($picture) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function pub($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function sub($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function rep($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function req($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function dealer($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function router($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function push($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function pull($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function xpub($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function xsub($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function xreq($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
  */
  static public function xrep($endpoint) {}

  /**
   * Create a ZMQ_STREAM socket.
   * 
   * @param string $endpoint ... (optional)
  */
  static public function stream($endpoint) {}

  /**
   * Create a ZMQ_SERVER socket. (Requires ZMQ > 4.2.0)
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function server($endpoint) {}

  /**
   * Create a ZMQ_CLIENT socket. (Requires ZMQ > 4.2.0)
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function client($endpoint) {}

  /**
   * ...
   * 
  */
  public function get_options() {}

  /**
   * ...
   * 
  */
  public function get_fd() {}

  /**
   * ...
   * 
  */
  public function get_socket() {}

  /**
   * ...
   * 
  */
  public function set_router_handover() {}

  /**
   * ...
   * 
  */
  public function set_router_mandatory() {}

  /**
   * ...
   * 
  */
  public function set_probe_router() {}

  /**
   * ...
   * 
  */
  public function set_req_relaxed() {}

  /**
   * ...
   * 
  */
  public function set_req_correlate() {}

  /**
   * ...
   * 
  */
  public function set_conflate() {}

  /**
   * ...
   * 
  */
  public function set_curve_publickey_bin() {}

  /**
   * ...
   * 
  */
  public function set_curve_secretkey_bin() {}

  /**
   * ...
   * 
  */
  public function set_curve_serverkey_bin() {}

  /**
   * ...
   * 
  */
  public function set_router_raw() {}

  /**
   * ...
   * 
  */
  public function set_delay_attach_on_connect() {}

  /**
   * ...
   * 
  */
  public function set_subscribe() {}

  /**
   * ...
   * 
  */
  public function set_unsubscribe() {}

  /**
   * ...
   * 
  */
  public function set_xpub_verbose() {}

}


/**
 * ZProxy
 *
 * ...
 */
class ZProxy implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @return \ZProxy
  */
  public function __construct() {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
  */
  public function pause() {}

  /**
   * ...
   * 
  */
  public function resume() {}

  /**
   * Recieve a ZMsg.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ...
   * 
   * @param string $type ...
   * @param string $endpoint ...
  */
  public function set_frontend($type, $endpoint) {}

  /**
   * ...
   * 
   * @param string $type ...
   * @param string $endpoint ...
  */
  public function set_backend($type, $endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ...
  */
  public function set_capture($endpoint) {}

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
 * ZBeacon
 *
 * ...
 */
class ZBeacon implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @return \ZBeacon
  */
  public function __construct() {}

  /**
   * ...
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
   * Recieve a ZMsg.
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

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

}


/**
 * ZAuth
 *
 * Authentication for ZeroMQ security mechanisms.
 */
class ZAuth implements \IZSocket, \IZDescriptor {
  const AUTH_PLAIN = "PLAIN";
  const AUTH_CURVE = "CURVE";
  const AUTH_GSSAPI = "GSSAPI";


  /**
   *  
   * 
   * @return \ZAuth
  */
  public function __construct() {}

  /**
   * Enable verbose logging of commands and activity. Verbose logging can help
   * debug non-trivial authentication policies
   * 
  */
  public function set_verbose() {}

  /**
   * Recieve a ZMsg.
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

}


/**
 * ZGossip
 *
 * Decentralized configuration management.
 */
class ZGossip implements \IZSocket, \IZDescriptor {

  /**
   *  
   * 
   * @return \ZGossip
  */
  public function __construct() {}

  /**
   * Enable verbose logging of commands and activity.
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
   * ...
   * 
   * @param string $endpoint ...
  */
  public function bind($endpoint) {}

  /**
   * ...
   * 
   * @param string $endpoint ...
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
   * Recieve a ZMsg.
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

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

}


/**
 * ZInotify
 *
 * ...
 */
class ZInotify implements \IZDescriptor {
  const IN_ACCESS = 1;
  const IN_MODIFY = 2;
  const IN_ATTRIB = 4;
  const IN_CLOSE_WRITE = 8;
  const IN_CLOSE_NOWRITE = 16;
  const IN_OPEN = 32;
  const IN_MOVED_FROM = 64;
  const IN_MOVED_TO = 128;
  const IN_CREATE = 256;
  const IN_DELETE = 512;
  const IN_DELETE_SELF = 1024;
  const IN_MOVE_SELF = 2048;
  const IN_UNMOUNT = 8192;
  const IN_Q_OVERFLOW = 16384;
  const IN_IGNORED = 32768;
  const IN_CLOSE = 24;
  const IN_MOVE = 192;
  const IN_ONLYDIR = 16777216;
  const IN_DONT_FOLLOW = 33554432;
  const IN_EXCL_UNLINK = 67108864;
  const IN_MASK_ADD = 536870912;
  const IN_ISDIR = 1073741824;
  const IN_ALL_EVENTS = 4095;


  /**
   * ...
   * 
   * @param string $file ...
   * @param int $events ...
   * @return int
  */
  public function watch($file, $events) {}

  /**
   * ...
   * 
   * @param int $watch_id ...
  */
  public function remove($watch_id) {}

  /**
   * Recieve a ZMsg.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ...
   * 
   * @return int
  */
  public function get_fd() {}

}


/**
 * ZStdIn
 *
 * ...
 */
class ZStdIn implements \IZDescriptor {

  /**
   * ...
   * 
   * @return string
  */
  public function recv() {}

  /**
   * ...
   * 
   * @param array|string|\ZFrame|\ZMsg $data ...
  */
  public function send($data) {}

  /**
   * ...
   * 
   * @return int
  */
  public function get_fd() {}

}


/**
 * ZStdOut
 *
 * ...
 */
class ZStdOut implements \IZDescriptor {

  /**
   * ...
   * 
   * @return string
  */
  public function recv() {}

  /**
   * ...
   * 
   * @param array|string|\ZFrame|\ZMsg $data ...
  */
  public function send($data) {}

  /**
   * ...
   * 
   * @return int
  */
  public function get_fd() {}

}


/**
 * ZStdErr
 *
 * ...
 */
class ZStdErr implements \IZDescriptor {

  /**
   * ...
   * 
   * @return string
  */
  public function recv() {}

  /**
   * ...
   * 
   * @param array|string|\ZFrame|\ZMsg $data ...
  */
  public function send($data) {}

  /**
   * ...
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
class Zyre implements \IZSocket, \IZDescriptor {

  /**
   * Creates a new Zyre node. Note that until you start the node it is silent and invisible to other nodes on the network.
   * 
   * @param string $name Zyre node name. (optional)
   * @return \Zyre\Zyre
  */
  public function __construct($name = null) {}

  /**
   * Start node, after setting header values. When you start a node it begins discovery and connection.
   * 
   * @return bool
  */
  public function start() {}

  /**
   * Stop node, this signals to other peers that this node will go away. This is polite; however you can also just destroy the node without stopping it.
   * 
  */
  public function stop() {}

  /**
   * Receive next message from network. The message may be a control message (ENTER, EXIT, JOIN, LEAVE) or data (WHISPER, SHOUT). Returns ZMsg object, or NULL if interrupted.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Dump the Zyre node configuration.
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
   * Set verbose mode; this tells the node to log all traffic as well as all major events.
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

}

namespace Majordomo\V2 {

/**
 * Broker
 *
 * ...
 */
class Broker implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
   * @param bool $verbose ... (optional)
   * @return \Majordomo\V2\Broker
  */
  public function __construct($endpoint, $verbose) {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
   * @param string $endpoint ...
  */
  public function bind($endpoint) {}

  /**
   * ...
   * 
   * @param string $filename ...
  */
  public function load_config($filename) {}

  /**
   * ...
   * 
   * @param string $filename ...
  */
  public function save_config($filename) {}

  /**
   * ...
   * 
   * @param string $key ...
   * @param string $value ...
  */
  public function set_config($key, $value) {}

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
 * Worker
 *
 * ...
 */
class Worker implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param string $name ...
   * @param string $broker_endpoint ...
   * @param callable $callback ...
   * @return \Majordomo\V2\Worker
  */
  public function __construct($name, $broker_endpoint, callable $callback) {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
  */
  public function run() {}

  /**
   * ...
   * 
  */
  public function process() {}

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
 * Client
 *
 * ...
 */
class Client implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param string $broker_endpoint ...
   * @return \Majordomo\V2\Client
  */
  public function __construct($broker_endpoint) {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * Recieve a ZMsg.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ...
   * 
   * @param string $service_name ...
  */
  public function call($service_name) {}

  /**
   * ...
   * 
   * @param string $service_name ...
  */
  public function call_async($service_name) {}

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

}

namespace Majordomo\V1 {

/**
 * Broker
 *
 * ...
 */
class Broker implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @return \Majordomo\V1\Broker
  */
  public function __construct() {}

  /**
   * ...
   * 
   * @param string $endpoint ...
  */
  public function bind($endpoint) {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
  */
  public function get_status() {}

  /**
   * ...
   * 
   * @param string $endpoint ...
  */
  public function set_capture($endpoint) {}

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
 * Worker
 *
 * ...
 */
class Worker implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param string $broker_endpoint ...
   * @param string $name ...
   * @param bool $verbose ... (optional)
   * @return \Majordomo\V1\Worker
  */
  public function __construct($broker_endpoint, $name, $verbose) {}

  /**
   * ...
   * 
   * @param callable $callback ...
  */
  public function run(callable $callback) {}

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
 * Client
 *
 * ...
 */
class Client implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @return \Majordomo\V1\Client
  */
  public function __construct() {}

  /**
   * ...
   * 
   * @param string $service ...
   * @param array|string|\ZFrame|\ZMsg $data ... (optional)
  */
  public function call($service, $data) {}

  /**
   * ...
   * 
   * @param string $service ...
   * @param array|string|\ZFrame|\ZMsg $data ... (optional)
  */
  public function call_async($service, $data) {}

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

}

namespace Malamute {

/**
 * Broker
 *
 * ...
 */
class Broker implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @return \Malamute\Broker
  */
  public function __construct() {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
   * @param string $endpoint ...
  */
  public function bind($endpoint) {}

  /**
   * ...
   * 
   * @param string $filename ...
  */
  public function load_config($filename) {}

  /**
   * ...
   * 
   * @param string $filename ...
  */
  public function save_config($filename) {}

  /**
   * ...
   * 
   * @param string $key ...
   * @param string $value ...
  */
  public function set_config($key, $value) {}

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
 * Worker
 *
 * ...
 */
class Worker implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param string $endpoint ...
   * @param string $address ...
   * @param string $pattern ... (optional)
   * @return \Malamute\Worker
  */
  public function __construct($endpoint, $address, $pattern) {}

  /**
   * ...
   * 
   * @param int $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * ...
   * 
   * @param callable $callback ...
  */
  public function run(callable $callback) {}

  /**
   * Get the underlying Malamute Client.
   * 
   * @return \Malamute\Client
  */
  public function get_client() {}

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
   * @param int $timeout ... (optional)
   * @return \Malamute\Client
  */
  public function __construct($endpoint, $address, $timeout) {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
   * @param string $endpoint ... (optional)
   * @param string $address ... (optional)
   * @param int $timeout ... (optional)
  */
  public function connect($endpoint, $address, $timeout) {}

  /**
   * ...
   * 
  */
  public function header() {}

  /**
   * ...
   * 
  */
  public function content() {}

  /**
   * ...
   * 
   * @param string $stream ...
  */
  public function set_producer($stream) {}

  /**
   * ...
   * 
   * @param string $address ...
   * @param string $patern ...
  */
  public function set_worker($address, $patern) {}

  /**
   * ...
   * 
   * @param string $stream ...
   * @param string $patern ...
  */
  public function set_consumer($stream, $patern) {}

  /**
   * ...
   * 
   * @param string $subject ...
  */
  public function send_stream($subject) {}

  /**
   * ...
   * 
   * @param string $address ...
   * @param mixed $payload ... (optional)
   * @param int $timeout ... (optional)
   * @param string $subject ... (optional)
   * @param string $tracker ... (optional)
  */
  public function send_mailbox($address, $payload, $timeout, $subject, $tracker) {}

  /**
   * ...
   * 
   * @param string $address ...
   * @param string $subject ...
   * @param mixed $payload ... (optional)
   * @param int $timeout ... (optional)
   * @param string $tracker ... (optional)
  */
  public function send_service($address, $subject, $payload, $timeout, $tracker) {}

  /**
   * Recieve a ZMsg.
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
class Producer implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param string $endpoint ...
   * @param string $stream ...
   * @return \Malamute\Producer
  */
  public function __construct($endpoint, $stream) {}

  /**
   * ...
   * 
   * @param int $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * ...
   * 
   * @param string $subject ...
   * @param callable $callback ...
  */
  public function run($subject, callable $callback) {}

  /**
   * Get the underlying Malamute Client.
   * 
   * @return \Malamute\Client
  */
  public function get_client() {}

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
 * Consumer
 *
 * ...
 */
class Consumer implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param string $endpoint ...
   * @param string $stream ...
   * @return \Malamute\Consumer
  */
  public function __construct($endpoint, $stream) {}

  /**
   * ...
   * 
   * @param int $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * ...
   * 
   * @param string $header ... (optional)
  */
  public function header($header) {}

  /**
   * ...
   * 
   * @param string $pattern ...
   * @param callable $callback ...
  */
  public function run($pattern, callable $callback) {}

  /**
   * Get the underlying Malamute Client.
   * 
   * @return \Malamute\Client
  */
  public function get_client() {}

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

}

namespace FileMq {

/**
 * Server
 *
 * ...
 */
class Server implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @return \FileMq\Server
  */
  public function __construct() {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * FileMQ Server endpoint to bind.
   * 
   * @param string $endpoint ...
  */
  public function bind($endpoint) {}

  /**
   * ...
   * 
   * @param string $filename ...
  */
  public function load_config($filename) {}

  /**
   * ...
   * 
   * @param string $filename ...
  */
  public function save_config($filename) {}

  /**
   * ...
   * 
   * @param string $key ...
   * @param string $value ...
  */
  public function set_config($key, $value) {}

  /**
   * ...
   * 
   * @param string $local_path ...
   * @param string $alias ...
  */
  public function publish($local_path, $alias) {}

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
   * Recieve a ZMsg.
   * 
   * @return \ZMsg
  */
  public function recv() {}

}


/**
 * Client
 *
 * FileMQ Client
 */
class Client implements \IZSocket, \IZDescriptor {

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
   * @param int $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * ...
   * 
  */
  public function connect() {}

  /**
   * ...
   * 
   * @param string $remote_path ...
  */
  public function subscribe($remote_path) {}

  /**
   * Recieve a ZMsg.
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

  /**
   * Get the underlying ZSocket.
   * 
   * @return \ZSocket
  */
  public function get_socket() {}

}

}
