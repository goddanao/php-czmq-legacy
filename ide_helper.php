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
   * Return Malamute version
   * 
   * @return string
  */
  static public function libmlm_version() {}

  /**
   * Return FileMq version
   * 
   * @return string
  */
  static public function libfmq_version() {}

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
  public function __construct($interface, $port, $routable) {}

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
  */
  public function append_picture() {}

  /**
   * ...
   * 
  */
  public function prepend_picture() {}

  /**
   * ...
   * 
  */
  public function pop_picture() {}

  /**
   * ...
   * 
  */
  public function append() {}

  /**
   * ...
   * 
  */
  public function prepend() {}

  /**
   * ...
   * 
  */
  public function pop() {}

  /**
   * ...
   * 
  */
  public function append_string() {}

  /**
   * ...
   * 
  */
  public function prepend_string() {}

  /**
   * ...
   * 
  */
  public function pop_string() {}

  /**
   * Send a ZMsg
   * 
  */
  public function send() {}

  /**
   * ...
   * 
  */
  public function remove() {}

  /**
   * ...
   * 
  */
  public function first() {}

  /**
   * ...
   * 
  */
  public function next() {}

  /**
   * ...
   * 
  */
  public function last() {}

  /**
   * ...
   * 
  */
  public function get_size() {}

  /**
   * ...
   * 
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
   * @param mixed $format ...
  */
  public function pack($format) {}

  /**
   * ...
   * 
   * @param mixed $format ...
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
  */
  public function set_max_timers() {}

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
   * @param mixed $mode ... (optional)
  */
  public function add($socket = null, $mode) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
  */
  public function remove($socket = null) {}

  /**
   * ...
   * 
  */
  public function add_timer() {}

  /**
   * ...
   * 
   * @param mixed $timer_id ...
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
  */
  public function set_verbose() {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
   * @param mixed $mode ... (optional)
  */
  public function add($socket = null, $mode) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
  */
  public function has($socket = null) {}

  /**
   * ...
   * 
   * @param \IZDescriptor $socket ...
  */
  public function remove($socket = null) {}

  /**
   * ...
   * 
  */
  public function check_for() {}

  /**
   * ...
   * 
  */
  public function events() {}

  /**
   * ...
   * 
  */
  public function poll() {}

  /**
   * ...
   * 
  */
  public function has_input() {}

  /**
   * ...
   * 
  */
  public function has_output() {}

  /**
   * ...
   * 
  */
  public function has_error() {}

}


/**
 * ZCert
 *
 * ...
 */
class ZCert {

  /**
   * ...
   * 
   * @param mixed $filename ... (optional)
   * @return \ZCert
  */
  public function __construct($filename) {}

  /**
   * ...
   * 
  */
  public function get_public_key() {}

  /**
   * ...
   * 
  */
  public function get_secret_key() {}

  /**
   * ...
   * 
  */
  public function get_public_key_txt() {}

  /**
   * ...
   * 
  */
  public function get_secret_key_txt() {}

  /**
   * ...
   * 
   * @param mixed $name ...
  */
  public function get_meta($name) {}

  /**
   * ...
   * 
  */
  public function get_meta_keys() {}

  /**
   * ...
   * 
   * @param mixed $name ...
   * @param mixed $value ...
  */
  public function set_meta($name, $value) {}

  /**
   * ...
   * 
   * @param mixed $filename ...
  */
  public function save($filename) {}

  /**
   * ...
   * 
   * @param mixed $filename ...
  */
  public function save_public($filename) {}

  /**
   * ...
   * 
   * @param mixed $filename ...
  */
  public function save_secret($filename) {}

  /**
   * ...
   * 
  */
  public function apply() {}

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
   * @param mixed $certificates_dir ... (optional)
   * @return \ZCertStore
  */
  public function __construct($certificates_dir) {}

  /**
   * ...
   * 
   * @param mixed $pubkey ...
  */
  public function lookup($pubkey) {}

  /**
   * ...
   * 
   * @param mixed $cert ...
  */
  public function insert($cert) {}

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
  public function __construct($socket = null) {}

  /**
   * ...
   * 
  */
  public function set_verbose() {}

  /**
   * ...
   * 
   * @param mixed $event ...
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
  */
  public function get_socket() ;

  /**
   * ...
   * 
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
   * @param mixed $socket_type ...
   * @param mixed $endpoint ... (optional)
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
   * @param mixed $endpoint ...
  */
  public function bind($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ...
  */
  public function unbind($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ...
  */
  public function connect($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ...
  */
  public function disconnect($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoints ...
   * @param mixed $serverish ... (optional)
  */
  public function attach($endpoints, $serverish) {}

  /**
   * ...
   * 
   * @param mixed $byte ...
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
  */
  public function send() {}

  /**
   * ...
   * 
  */
  public function recv() {}

  /**
   * ...
   * 
   * @param mixed $value ...
  */
  public function send_string($value) {}

  /**
   * ...
   * 
  */
  public function recv_string() {}

  /**
   * ...
   * 
   * @param mixed $picture ...
  */
  public function send_picture($picture) {}

  /**
   * ...
   * 
   * @param mixed $picture ...
  */
  public function recv_picture($picture) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function pub($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function sub($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function rep($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function req($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function dealer($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function router($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function push($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function pull($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function xpub($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function xsub($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function xreq($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function xrep($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function stream($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ... (optional)
  */
  static public function server($endpoint) {}

  /**
   * ...
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
  public function get_tos() {}

  /**
   * ...
   * 
  */
  public function get_zap_domain() {}

  /**
   * ...
   * 
  */
  public function get_mechanism() {}

  /**
   * ...
   * 
  */
  public function get_plain_server() {}

  /**
   * ...
   * 
  */
  public function get_plain_username() {}

  /**
   * ...
   * 
  */
  public function get_plain_password() {}

  /**
   * ...
   * 
  */
  public function get_curve_server() {}

  /**
   * ...
   * 
  */
  public function get_curve_publickey() {}

  /**
   * ...
   * 
  */
  public function get_curve_secretkey() {}

  /**
   * ...
   * 
  */
  public function get_curve_serverkey() {}

  /**
   * ...
   * 
  */
  public function get_gssapi_server() {}

  /**
   * ...
   * 
  */
  public function get_gssapi_plaintext() {}

  /**
   * ...
   * 
  */
  public function get_gssapi_principal() {}

  /**
   * ...
   * 
  */
  public function get_gssapi_service_principal() {}

  /**
   * ...
   * 
  */
  public function get_ipv6() {}

  /**
   * ...
   * 
  */
  public function get_immediate() {}

  /**
   * ...
   * 
  */
  public function get_ipv4only() {}

  /**
   * ...
   * 
  */
  public function get_type() {}

  /**
   * ...
   * 
  */
  public function get_sndhwm() {}

  /**
   * ...
   * 
  */
  public function get_rcvhwm() {}

  /**
   * ...
   * 
  */
  public function get_affinity() {}

  /**
   * ...
   * 
  */
  public function get_identity() {}

  /**
   * ...
   * 
  */
  public function get_rate() {}

  /**
   * ...
   * 
  */
  public function get_recovery_ivl() {}

  /**
   * ...
   * 
  */
  public function get_sndbuf() {}

  /**
   * ...
   * 
  */
  public function get_rcvbuf() {}

  /**
   * ...
   * 
  */
  public function get_linger() {}

  /**
   * ...
   * 
  */
  public function get_reconnect_ivl() {}

  /**
   * ...
   * 
  */
  public function get_reconnect_ivl_max() {}

  /**
   * ...
   * 
  */
  public function get_backlog() {}

  /**
   * ...
   * 
  */
  public function get_maxmsgsize() {}

  /**
   * ...
   * 
  */
  public function get_multicast_hops() {}

  /**
   * ...
   * 
  */
  public function get_rcvtimeo() {}

  /**
   * ...
   * 
  */
  public function get_sndtimeo() {}

  /**
   * ...
   * 
  */
  public function get_tcp_keepalive() {}

  /**
   * ...
   * 
  */
  public function get_tcp_keepalive_idle() {}

  /**
   * ...
   * 
  */
  public function get_tcp_keepalive_cnt() {}

  /**
   * ...
   * 
  */
  public function get_tcp_keepalive_intvl() {}

  /**
   * ...
   * 
  */
  public function get_tcp_accept_filter() {}

  /**
   * ...
   * 
  */
  public function get_rcvmore() {}

  /**
   * ...
   * 
  */
  public function get_events() {}

  /**
   * ...
   * 
  */
  public function get_last_endpoint() {}

  /**
   * ...
   * 
  */
  public function set_tos() {}

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
  public function set_zap_domain() {}

  /**
   * ...
   * 
  */
  public function set_plain_server() {}

  /**
   * ...
   * 
  */
  public function set_plain_username() {}

  /**
   * ...
   * 
  */
  public function set_plain_password() {}

  /**
   * ...
   * 
  */
  public function set_curve_server() {}

  /**
   * ...
   * 
  */
  public function set_curve_publickey() {}

  /**
   * ...
   * 
  */
  public function set_curve_publickey_bin() {}

  /**
   * ...
   * 
  */
  public function set_curve_secretkey() {}

  /**
   * ...
   * 
  */
  public function set_curve_secretkey_bin() {}

  /**
   * ...
   * 
  */
  public function set_curve_serverkey() {}

  /**
   * ...
   * 
  */
  public function set_curve_serverkey_bin() {}

  /**
   * ...
   * 
  */
  public function set_gssapi_server() {}

  /**
   * ...
   * 
  */
  public function set_gssapi_plaintext() {}

  /**
   * ...
   * 
  */
  public function set_gssapi_principal() {}

  /**
   * ...
   * 
  */
  public function set_gssapi_service_principal() {}

  /**
   * ...
   * 
  */
  public function set_ipv6() {}

  /**
   * ...
   * 
  */
  public function set_immediate() {}

  /**
   * ...
   * 
  */
  public function set_router_raw() {}

  /**
   * ...
   * 
  */
  public function set_ipv4only() {}

  /**
   * ...
   * 
  */
  public function set_delay_attach_on_connect() {}

  /**
   * ...
   * 
  */
  public function set_sndhwm() {}

  /**
   * ...
   * 
  */
  public function set_rcvhwm() {}

  /**
   * ...
   * 
  */
  public function set_affinity() {}

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
  public function set_identity() {}

  /**
   * ...
   * 
  */
  public function set_rate() {}

  /**
   * ...
   * 
  */
  public function set_recovery_ivl() {}

  /**
   * ...
   * 
  */
  public function set_sndbuf() {}

  /**
   * ...
   * 
  */
  public function set_rcvbuf() {}

  /**
   * ...
   * 
  */
  public function set_linger() {}

  /**
   * ...
   * 
  */
  public function set_reconnect_ivl() {}

  /**
   * ...
   * 
  */
  public function set_reconnect_ivl_max() {}

  /**
   * ...
   * 
  */
  public function set_backlog() {}

  /**
   * ...
   * 
  */
  public function set_maxmsgsize() {}

  /**
   * ...
   * 
  */
  public function set_multicast_hops() {}

  /**
   * ...
   * 
  */
  public function set_rcvtimeo() {}

  /**
   * ...
   * 
  */
  public function set_sndtimeo() {}

  /**
   * ...
   * 
  */
  public function set_xpub_verbose() {}

  /**
   * ...
   * 
  */
  public function set_tcp_keepalive() {}

  /**
   * ...
   * 
  */
  public function set_tcp_keepalive_idle() {}

  /**
   * ...
   * 
  */
  public function set_tcp_keepalive_cnt() {}

  /**
   * ...
   * 
  */
  public function set_tcp_keepalive_intvl() {}

  /**
   * ...
   * 
  */
  public function set_tcp_accept_filter() {}

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
   * @param mixed $socket_type ...
   * @param mixed $socket_endpoint ...
  */
  public function set_frontend($socket_type, $socket_endpoint) {}

  /**
   * ...
   * 
   * @param mixed $socket_type ...
   * @param mixed $socket_endpoint ...
  */
  public function set_backend($socket_type, $socket_endpoint) {}

  /**
   * ...
   * 
   * @param mixed $socket_endpoint ...
  */
  public function set_capture($socket_endpoint) {}

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
   * ...
   * 
   * @param mixed $port ...
  */
  public function set_port($port) {}

  /**
   * ...
   * 
   * @param mixed $filter ...
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
   * @param mixed $data ...
   * @param mixed $interval ... (optional)
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
  */
  public function configure() {}

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
   * @param mixed $filename ...
  */
  public function configure($filename) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ...
  */
  public function bind($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $endpoint ...
  */
  public function connect($endpoint) {}

  /**
   * ...
   * 
   * @param mixed $property ...
   * @param mixed $value ...
  */
  public function set($property, $value) {}

  /**
   * ...
   * 
   * @param mixed $property ...
   * @param mixed $value ...
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
  */
  public function watch() {}

  /**
   * ...
   * 
  */
  public function remove() {}

  /**
   * Recieve a ZMsg.
   * 
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ...
   * 
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
  */
  public function send() {}

  /**
   * ...
   * 
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
  */
  public function send() {}

  /**
   * ...
   * 
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
  */
  public function send() {}

  /**
   * ...
   * 
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
  public function __construct($name) {}

  /**
   * Start node, after setting header values. When you start a node it begins discovery and connection.
   * 
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
   * @param mixed $value ...
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
   * @param mixed $endpoint ... (optional)
   * @param mixed $verbose ... (optional)
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
  */
  public function load_config() {}

  /**
   * ...
   * 
  */
  public function save_config() {}

  /**
   * ...
   * 
  */
  public function set_config() {}

  /**
   * ...
   * 
  */
  public function bind() {}

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
   * @param mixed $name ...
   * @param mixed $broker_endpoint ...
   * @param callable $callback ...
   * @return \Majordomo\V2\Worker
  */
  public function __construct($name, $broker_endpoint, $callback) {}

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
   * @param mixed $broker_endpoint ...
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
   * @param mixed $service_name ...
  */
  public function call($service_name) {}

  /**
   * ...
   * 
   * @param mixed $service_name ...
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
  */
  public function bind() {}

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
   * @param mixed $socket_endpoint ...
  */
  public function set_capture($socket_endpoint) {}

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
   * @param mixed $broker_endpoint ...
   * @param mixed $name ...
   * @param mixed $verbose ... (optional)
   * @return \Majordomo\V1\Worker
  */
  public function __construct($broker_endpoint, $name, $verbose) {}

  /**
   * ...
   * 
   * @param callable $callback ...
  */
  public function run($callback) {}

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
  */
  public function call() {}

  /**
   * ...
   * 
  */
  public function call_async() {}

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
  */
  public function bind() {}

  /**
   * ...
   * 
  */
  public function load_config() {}

  /**
   * ...
   * 
  */
  public function save_config() {}

  /**
   * ...
   * 
  */
  public function set_config() {}

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
   * @param mixed $endpoint ...
   * @param mixed $address ...
   * @param mixed $pattern ... (optional)
   * @return \Malamute\Worker
  */
  public function __construct($endpoint, $address, $pattern) {}

  /**
   * ...
   * 
   * @param mixed $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * ...
   * 
   * @param callable $callback ...
  */
  public function run($callback) {}

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
   * @param mixed $endpoint ...
   * @param mixed $address ... (optional)
   * @param mixed $timeout ... (optional)
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
   * @param mixed $endpoint ... (optional)
   * @param mixed $address ... (optional)
   * @param mixed $timeout ... (optional)
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
   * @param mixed $stream ...
  */
  public function set_producer($stream) {}

  /**
   * ...
   * 
   * @param mixed $address ...
   * @param mixed $patern ...
  */
  public function set_worker($address, $patern) {}

  /**
   * ...
   * 
   * @param mixed $stream ...
   * @param mixed $patern ...
  */
  public function set_consumer($stream, $patern) {}

  /**
   * ...
   * 
   * @param mixed $subject ...
  */
  public function send_stream($subject) {}

  /**
   * ...
   * 
   * @param mixed $address ...
   * @param mixed $payload ... (optional)
   * @param mixed $timeout ... (optional)
   * @param mixed $subject ... (optional)
   * @param mixed $tracker ... (optional)
  */
  public function send_mailbox($address, $payload, $timeout, $subject, $tracker) {}

  /**
   * ...
   * 
   * @param mixed $address ...
   * @param mixed $subject ...
   * @param mixed $payload ... (optional)
   * @param mixed $timeout ... (optional)
   * @param mixed $tracker ... (optional)
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
   * @param mixed $endpoint ...
   * @param mixed $stream ...
   * @return \Malamute\Producer
  */
  public function __construct($endpoint, $stream) {}

  /**
   * ...
   * 
   * @param mixed $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * ...
   * 
   * @param mixed $subject ...
   * @param callable $callback ...
  */
  public function run($subject, $callback) {}

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
   * @param mixed $endpoint ...
   * @param mixed $stream ...
   * @return \Malamute\Consumer
  */
  public function __construct($endpoint, $stream) {}

  /**
   * ...
   * 
   * @param mixed $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * ...
   * 
   * @param mixed $header ... (optional)
  */
  public function header($header) {}

  /**
   * ...
   * 
   * @param mixed $pattern ...
   * @param callable $callback ...
  */
  public function run($pattern, $callback) {}

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
   * ...
   * 
  */
  public function load_config() {}

  /**
   * ...
   * 
  */
  public function set_config() {}

  /**
   * ...
   * 
  */
  public function save_config() {}

  /**
   * ...
   * 
  */
  public function bind() {}

  /**
   * ...
   * 
   * @param mixed $local_path ...
   * @param mixed $alias ...
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
 * ...
 */
class Client implements \IZSocket, \IZDescriptor {

  /**
   * ...
   * 
   * @param mixed $endpoint ...
   * @param mixed $local_path ...
   * @param mixed $timeout ... (optional)
   * @return \FileMq\Client
  */
  public function __construct($endpoint, $local_path, $timeout) {}

  /**
   * ...
   * 
   * @param mixed $timeout ...
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
   * @param mixed $remote_path ...
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
