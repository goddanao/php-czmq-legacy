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
   * ZSys::set_io_threads
   *
   * Configure the number of I/O threads that ZeroMQ will use. A good
   * rule of thumb is one thread per gigabit of traffic in or out. The
   * default is 1, sufficient for most applications. If the environment
   * variable ZSYS_IO_THREADS is defined, that provides the default.
   * Note that this method is valid only before any socket is created.
   * @param int $threads  
  */
  static public function set_io_threads($threads) {}

  /**
   * ZSys::set_ipv6
   *
   * Configure use of IPv6 for new zsock instances. By default sockets accept
   * and make only IPv4 connections. When you enable IPv6, sockets will accept
   * and connect to both IPv4 and IPv6 peers. You can override the setting on
   * each zsock_t instance. The default is IPv4 only (ipv6 set to 0). If the
   * environment variable ZSYS_IPV6 is defined (as 1 or 0), this provides the
   * default. Note: has no effect on ZMQ v2.
   * @param bool $enable  
  */
  static public function set_ipv6($enable) {}

  /**
   * ZSys::set_default_linger
   *
   * Configure the default linger timeout in msecs for new zsock instances.
   * You can also set this separately on each zsock_t instance. The default
   * linger time is zero, i.e. any pending messages will be dropped. If the
   * environment variable ZSYS_LINGER is defined, that provides the default.
   * Note that process exit will typically be delayed by the linger time.
   * @param int $linger  
  */
  static public function set_default_linger($linger) {}

  /**
   * ZSys::set_default_sndhwm
   *
   * Configure the default outgoing pipe limit (HWM) for new zsock instances.
   * You can also set this separately on each zsock_t instance. The default
   * HWM is 1,000, on all versions of ZeroMQ. If the environment variable
   * ZSYS_SNDHWM is defined, that provides the default. Note that a value of
   * zero means no limit, i.e. infinite memory consumption.
   * @param int $sndhwm  
  */
  static public function set_default_sndhwm($sndhwm) {}

  /**
   * ZSys::set_default_rcvhwm
   *
   * Configure the default incoming pipe limit (HWM) for new zsock instances.
   * You can also set this separately on each zsock_t instance. The default
   * HWM is 1,000, on all versions of ZeroMQ. If the environment variable
   * ZSYS_RCVHWM is defined, that provides the default. Note that a value of
   * zero means no limit, i.e. infinite memory consumption.
   * @param int $rcvhwm  
  */
  static public function set_default_rcvhwm($rcvhwm) {}

  /**
   * ZSys::set_pipehwm
   *
   * Configure the default HWM for zactor internal pipes; this is set on both
   * ends of the pipe, for outgoing messages only (sndhwm). The default HWM is
   * 1,000, on all versions of ZeroMQ. If the environment var ZSYS_ACTORHWM is
   * defined, that provides the default. Note that a value of zero means no
   * limit, i.e. infinite memory consumption.
   * @param int $pipehwm  
  */
  static public function set_pipehwm($pipehwm) {}

  /**
   * ZSys::get_pipehwm
   *
   * Return the HWM for zactor internal pipes.
   * @return int
  */
  static public function get_pipehwm() {}

  /**
   * ZSys::has_curve
   *
   * Returns true if the underlying libzmq supports CURVE security.
   * @return bool
  */
  static public function has_curve() {}

  /**
   * ZSys::get_socket_limit
   *
   * Return maximum number of ZeroMQ sockets that the system will support.
   * @return int
  */
  static public function get_socket_limit() {}

  /**
   * ZSys::set_max_sockets
   *
   * Configure the number of sockets that ZeroMQ will allow. The default
   * is 1024. The actual limit depends on the system, and you can query it
   * by using get_socket_limit (). A value of zero means 'maximum'.
   * Note that this method is valid only before any socket is created.
   * @param int $max_sockets  
  */
  static public function set_max_sockets($max_sockets) {}

  /**
   * ZSys::hostname
   *
   * Return current host name, for use in public tcp:// endpoints.
   * @return string
  */
  static public function hostname() {}

  /**
   * ZSys::set_interface
   *
   * Set network interface name to use for broadcasts, particularly zbeacon.
   * This lets the interface be configured for test environments where required.
   * For example, on Mac OS X, zbeacon cannot bind to 255.255.255.255 which is
   * the default when there is no specified interface. If the environment
   * variable ZSYS_INTERFACE is set, use that as the default interface name.
   * Setting the interface to '*' means 'use all available interfaces'.
   * @param string $interface  
  */
  static public function set_interface($interface) {}

  /**
   * ZSys::get_interface
   *
   * Return network interface to use for broadcasts, or '' if none was set.
   * @return string
  */
  static public function get_interface() {}

  /**
   * ZSys::list_interfaces
   *
   * Return network interfaces
   * @return array
  */
  static public function list_interfaces() {}

  /**
   * ZSys::set_log_ident
   *
   * Set log identity, which is a string that prefixes all log messages sent
   * by this process. The log identity defaults to the environment variable
   * ZSYS_LOGIDENT, if that is set.
   * @param string $log_ident  
  */
  static public function set_log_ident($log_ident) {}

  /**
   * ZSys::set_log_endpoint
   *
   * Sends log output to a PUB socket bound to the specified endpoint. To
   * collect such log output, create a SUB socket, subscribe to the traffic
   * you care about, and connect to the endpoint. Log traffic is sent as a
   * single string frame, in the same format as when sent to stdout. The
   * log system supports a single sender; multiple calls to this method will
   * bind the same sender to multiple endpoints. To disable the sender, call
   * this method with a null argument.
   * @param string $log_endpoint  
  */
  static public function set_log_endpoint($log_endpoint) {}

  /**
   * ZSys::set_log_system
   *
   * Enable or disable logging to the system facility (syslog on POSIX boxes,
   * event log on Windows). By default this is enabled.
   * @param bool $enable  
  */
  static public function set_log_system($enable) {}

  /**
   * ZSys::libzmq_version
   *
   * Return ZMQ version
   * @return string
  */
  static public function libzmq_version() {}

  /**
   * ZSys::libczmq_version
   *
   * Return CZMQ version
   * @return string
  */
  static public function libczmq_version() {}

  /**
   * ZSys::libzyre_version
   *
   * Return Zyre version
   * @return string
  */
  static public function libzyre_version() {}

  /**
   * ZSys::libmdp_version
   *
   * Return Majordomo Protocol version
   * @return string
  */
  static public function libmdp_version() {}

  /**
   * ZSys::libmlm_version
   *
   * Return Malamute version
   * @return string
  */
  static public function libmlm_version() {}

  /**
   * ZSys::libfmq_version
   *
   * Return FileMq version
   * @return string
  */
  static public function libfmq_version() {}

  /**
   * ZSys::info
   *
   * Log message as Info
   * @param string $message  
  */
  static public function info($message) {}

  /**
   * ZSys::debug
   *
   * Log message as Debug
   * @param string $message  
  */
  static public function debug($message) {}

  /**
   * ZSys::warning
   *
   * Log message as Warning
   * @param string $message  
  */
  static public function warning($message) {}

  /**
   * ZSys::error
   *
   * Log message as Error
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
   * ZUdp::__construct
   *
   *  
   * @param string $interface The interface name to bind (optional)
   * @param int $port The port number to bind (optional)
   * @param bool $routable uses multicast (not yet implemented), else uses broadcast (default) (optional)
  */
  public function __construct($interface, $port, $routable) {}

  /**
   * ZUdp::set_verbose
   *
   * Verbose logging
  */
  public function set_verbose() {}

  /**
   * ZUdp::send
   *
   * Send a ZMsg.
  */
  public function send() {}

  /**
   * ZUdp::recv
   *
   * Recieve a ZMsg.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ZUdp::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

}


/**
 * ZMsg
 *
 * ...
 */
class ZMsg {

  /**
   * ZMsg::__construct
   *
   * ...
  */
  public function __construct() {}

  /**
   * ZMsg::append_picture
   *
   * ...
  */
  public function append_picture() {}

  /**
   * ZMsg::prepend_picture
   *
   * ...
  */
  public function prepend_picture() {}

  /**
   * ZMsg::pop_picture
   *
   * ...
  */
  public function pop_picture() {}

  /**
   * ZMsg::append
   *
   * ...
  */
  public function append() {}

  /**
   * ZMsg::prepend
   *
   * ...
  */
  public function prepend() {}

  /**
   * ZMsg::pop
   *
   * ...
  */
  public function pop() {}

  /**
   * ZMsg::append_string
   *
   * ...
  */
  public function append_string() {}

  /**
   * ZMsg::prepend_string
   *
   * ...
  */
  public function prepend_string() {}

  /**
   * ZMsg::pop_string
   *
   * ...
  */
  public function pop_string() {}

  /**
   * ZMsg::send
   *
   * ...
  */
  public function send() {}

  /**
   * ZMsg::remove
   *
   * ...
  */
  public function remove() {}

  /**
   * ZMsg::first
   *
   * ...
  */
  public function first() {}

  /**
   * ZMsg::next
   *
   * ...
  */
  public function next() {}

  /**
   * ZMsg::last
   *
   * ...
  */
  public function last() {}

  /**
   * ZMsg::get_size
   *
   * ...
  */
  public function get_size() {}

  /**
   * ZMsg::get_content_size
   *
   * ...
  */
  public function get_content_size() {}

  /**
   * ZMsg::dump
   *
   * ...
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
   * ZFrame::__construct
   *
   * ...
  */
  public function __construct() {}

  /**
   * ZFrame::dump
   *
   * ...
  */
  public function dump() {}

}


/**
 * ZLoop
 *
 * ...
 */
class ZLoop {

  /**
   * ZLoop::__construct
   *
   * ...
  */
  public function __construct() {}

  /**
   * ZLoop::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * ZLoop::set_max_timers
   *
   * ...
  */
  public function set_max_timers() {}

  /**
   * ZLoop::start
   *
   * ...
  */
  public function start() {}

  /**
   * ZLoop::stop
   *
   * ...
  */
  public function stop() {}

  /**
   * ZLoop::add
   *
   * ...
   * @param \IZDescriptor $socket ...
   * @param mixed $mode ... (optional)
  */
  public function add($socket = null, $mode) {}

  /**
   * ZLoop::remove
   *
   * ...
   * @param \IZDescriptor $socket ...
  */
  public function remove($socket = null) {}

  /**
   * ZLoop::add_timer
   *
   * ...
  */
  public function add_timer() {}

  /**
   * ZLoop::remove_timer
   *
   * ...
   * @param mixed $timer_id ...
  */
  public function remove_timer($timer_id) {}

  /**
   * ZLoop::ignore_interrupts
   *
   * ...
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
   * ZPoll::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * ZPoll::add
   *
   * ...
   * @param \IZDescriptor $socket ...
   * @param mixed $mode ... (optional)
  */
  public function add($socket = null, $mode) {}

  /**
   * ZPoll::has
   *
   * ...
   * @param \IZDescriptor $socket ...
  */
  public function has($socket = null) {}

  /**
   * ZPoll::remove
   *
   * ...
   * @param \IZDescriptor $socket ...
  */
  public function remove($socket = null) {}

  /**
   * ZPoll::check_for
   *
   * ...
  */
  public function check_for() {}

  /**
   * ZPoll::events
   *
   * ...
  */
  public function events() {}

  /**
   * ZPoll::poll
   *
   * ...
  */
  public function poll() {}

  /**
   * ZPoll::has_input
   *
   * ...
  */
  public function has_input() {}

  /**
   * ZPoll::has_output
   *
   * ...
  */
  public function has_output() {}

  /**
   * ZPoll::has_error
   *
   * ...
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
   * ZCert::__construct
   *
   * ...
   * @param mixed $filename ... (optional)
  */
  public function __construct($filename) {}

  /**
   * ZCert::get_public_key
   *
   * ...
  */
  public function get_public_key() {}

  /**
   * ZCert::get_secret_key
   *
   * ...
  */
  public function get_secret_key() {}

  /**
   * ZCert::get_public_key_txt
   *
   * ...
  */
  public function get_public_key_txt() {}

  /**
   * ZCert::get_secret_key_txt
   *
   * ...
  */
  public function get_secret_key_txt() {}

  /**
   * ZCert::get_meta
   *
   * ...
   * @param mixed $name ...
  */
  public function get_meta($name) {}

  /**
   * ZCert::get_meta_keys
   *
   * ...
  */
  public function get_meta_keys() {}

  /**
   * ZCert::set_meta
   *
   * ...
   * @param mixed $name ...
   * @param mixed $value ...
  */
  public function set_meta($name, $value) {}

  /**
   * ZCert::save
   *
   * ...
   * @param mixed $filename ...
  */
  public function save($filename) {}

  /**
   * ZCert::save_public
   *
   * ...
   * @param mixed $filename ...
  */
  public function save_public($filename) {}

  /**
   * ZCert::save_secret
   *
   * ...
   * @param mixed $filename ...
  */
  public function save_secret($filename) {}

  /**
   * ZCert::apply
   *
   * ...
  */
  public function apply() {}

  /**
   * ZCert::dump
   *
   * ...
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
   * ZCertStore::__construct
   *
   * ...
   * @param mixed $certificates_dir ... (optional)
  */
  public function __construct($certificates_dir) {}

  /**
   * ZCertStore::lookup
   *
   * ...
   * @param mixed $pubkey ...
  */
  public function lookup($pubkey) {}

  /**
   * ZCertStore::insert
   *
   * ...
   * @param mixed $cert ...
  */
  public function insert($cert) {}

  /**
   * ZCertStore::dump
   *
   * ...
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
   * ZMonitor::__construct
   *
   * ...
   * @param \IZSocket $socket ...
  */
  public function __construct($socket = null) {}

  /**
   * ZMonitor::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * ZMonitor::listen
   *
   * ...
   * @param mixed $event ...
  */
  public function listen($event) {}

  /**
   * ZMonitor::start
   *
   * ...
  */
  public function start() {}

  /**
   * ZMonitor::recv
   *
   * Recieve a ZMsg.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ZMonitor::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * ZMonitor::get_socket
   *
   * Get the underlying ZSocket.
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
   * IZDescriptor::get_fd
   *
   * ...
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
   * IZSocket::get_socket
   *
   * ...
  */
  public function get_socket() ;

  /**
   * IZSocket::get_fd
   *
   * ...
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
   * ZSocket::__construct
   *
   * ...
   * @param mixed $socket_type ...
   * @param mixed $endpoint ... (optional)
  */
  public function __construct($socket_type, $endpoint) {}

  /**
   * ZSocket::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * ZSocket::set_unbounded
   *
   * ...
  */
  public function set_unbounded() {}

  /**
   * ZSocket::bind
   *
   * ...
   * @param mixed $endpoint ...
  */
  public function bind($endpoint) {}

  /**
   * ZSocket::unbind
   *
   * ...
   * @param mixed $endpoint ...
  */
  public function unbind($endpoint) {}

  /**
   * ZSocket::connect
   *
   * ...
   * @param mixed $endpoint ...
  */
  public function connect($endpoint) {}

  /**
   * ZSocket::disconnect
   *
   * ...
   * @param mixed $endpoint ...
  */
  public function disconnect($endpoint) {}

  /**
   * ZSocket::attach
   *
   * ...
   * @param mixed $endpoints ...
   * @param mixed $serverish ... (optional)
  */
  public function attach($endpoints, $serverish) {}

  /**
   * ZSocket::signal
   *
   * ...
   * @param mixed $byte ...
  */
  public function signal($byte) {}

  /**
   * ZSocket::wait
   *
   * ...
  */
  public function wait() {}

  /**
   * ZSocket::flush
   *
   * ...
  */
  public function flush() {}

  /**
   * ZSocket::get_socket_type
   *
   * ...
  */
  public function get_socket_type() {}

  /**
   * ZSocket::send
   *
   * ...
  */
  public function send() {}

  /**
   * ZSocket::recv
   *
   * ...
  */
  public function recv() {}

  /**
   * ZSocket::send_string
   *
   * ...
   * @param mixed $value ...
  */
  public function send_string($value) {}

  /**
   * ZSocket::recv_string
   *
   * ...
  */
  public function recv_string() {}

  /**
   * ZSocket::send_picture
   *
   * ...
   * @param mixed $picture ...
  */
  public function send_picture($picture) {}

  /**
   * ZSocket::recv_picture
   *
   * ...
   * @param mixed $picture ...
  */
  public function recv_picture($picture) {}

  /**
   * ZSocket::pub
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function pub($endpoint) {}

  /**
   * ZSocket::sub
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function sub($endpoint) {}

  /**
   * ZSocket::rep
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function rep($endpoint) {}

  /**
   * ZSocket::req
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function req($endpoint) {}

  /**
   * ZSocket::dealer
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function dealer($endpoint) {}

  /**
   * ZSocket::router
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function router($endpoint) {}

  /**
   * ZSocket::push
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function push($endpoint) {}

  /**
   * ZSocket::pull
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function pull($endpoint) {}

  /**
   * ZSocket::xpub
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function xpub($endpoint) {}

  /**
   * ZSocket::xsub
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function xsub($endpoint) {}

  /**
   * ZSocket::xreq
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function xreq($endpoint) {}

  /**
   * ZSocket::xrep
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function xrep($endpoint) {}

  /**
   * ZSocket::stream
   *
   * ...
   * @param mixed $endpoint ... (optional)
  */
  static public function stream($endpoint) {}

  /**
   * ZSocket::get_options
   *
   * ...
  */
  public function get_options() {}

  /**
   * ZSocket::get_fd
   *
   * ...
  */
  public function get_fd() {}

  /**
   * ZSocket::get_socket
   *
   * ...
  */
  public function get_socket() {}

  /**
   * ZSocket::get_tos
   *
   * ...
  */
  public function get_tos() {}

  /**
   * ZSocket::get_zap_domain
   *
   * ...
  */
  public function get_zap_domain() {}

  /**
   * ZSocket::get_mechanism
   *
   * ...
  */
  public function get_mechanism() {}

  /**
   * ZSocket::get_plain_server
   *
   * ...
  */
  public function get_plain_server() {}

  /**
   * ZSocket::get_plain_username
   *
   * ...
  */
  public function get_plain_username() {}

  /**
   * ZSocket::get_plain_password
   *
   * ...
  */
  public function get_plain_password() {}

  /**
   * ZSocket::get_curve_server
   *
   * ...
  */
  public function get_curve_server() {}

  /**
   * ZSocket::get_curve_publickey
   *
   * ...
  */
  public function get_curve_publickey() {}

  /**
   * ZSocket::get_curve_secretkey
   *
   * ...
  */
  public function get_curve_secretkey() {}

  /**
   * ZSocket::get_curve_serverkey
   *
   * ...
  */
  public function get_curve_serverkey() {}

  /**
   * ZSocket::get_gssapi_server
   *
   * ...
  */
  public function get_gssapi_server() {}

  /**
   * ZSocket::get_gssapi_plaintext
   *
   * ...
  */
  public function get_gssapi_plaintext() {}

  /**
   * ZSocket::get_gssapi_principal
   *
   * ...
  */
  public function get_gssapi_principal() {}

  /**
   * ZSocket::get_gssapi_service_principal
   *
   * ...
  */
  public function get_gssapi_service_principal() {}

  /**
   * ZSocket::get_ipv6
   *
   * ...
  */
  public function get_ipv6() {}

  /**
   * ZSocket::get_immediate
   *
   * ...
  */
  public function get_immediate() {}

  /**
   * ZSocket::get_ipv4only
   *
   * ...
  */
  public function get_ipv4only() {}

  /**
   * ZSocket::get_type
   *
   * ...
  */
  public function get_type() {}

  /**
   * ZSocket::get_sndhwm
   *
   * ...
  */
  public function get_sndhwm() {}

  /**
   * ZSocket::get_rcvhwm
   *
   * ...
  */
  public function get_rcvhwm() {}

  /**
   * ZSocket::get_affinity
   *
   * ...
  */
  public function get_affinity() {}

  /**
   * ZSocket::get_identity
   *
   * ...
  */
  public function get_identity() {}

  /**
   * ZSocket::get_rate
   *
   * ...
  */
  public function get_rate() {}

  /**
   * ZSocket::get_recovery_ivl
   *
   * ...
  */
  public function get_recovery_ivl() {}

  /**
   * ZSocket::get_sndbuf
   *
   * ...
  */
  public function get_sndbuf() {}

  /**
   * ZSocket::get_rcvbuf
   *
   * ...
  */
  public function get_rcvbuf() {}

  /**
   * ZSocket::get_linger
   *
   * ...
  */
  public function get_linger() {}

  /**
   * ZSocket::get_reconnect_ivl
   *
   * ...
  */
  public function get_reconnect_ivl() {}

  /**
   * ZSocket::get_reconnect_ivl_max
   *
   * ...
  */
  public function get_reconnect_ivl_max() {}

  /**
   * ZSocket::get_backlog
   *
   * ...
  */
  public function get_backlog() {}

  /**
   * ZSocket::get_maxmsgsize
   *
   * ...
  */
  public function get_maxmsgsize() {}

  /**
   * ZSocket::get_multicast_hops
   *
   * ...
  */
  public function get_multicast_hops() {}

  /**
   * ZSocket::get_rcvtimeo
   *
   * ...
  */
  public function get_rcvtimeo() {}

  /**
   * ZSocket::get_sndtimeo
   *
   * ...
  */
  public function get_sndtimeo() {}

  /**
   * ZSocket::get_tcp_keepalive
   *
   * ...
  */
  public function get_tcp_keepalive() {}

  /**
   * ZSocket::get_tcp_keepalive_idle
   *
   * ...
  */
  public function get_tcp_keepalive_idle() {}

  /**
   * ZSocket::get_tcp_keepalive_cnt
   *
   * ...
  */
  public function get_tcp_keepalive_cnt() {}

  /**
   * ZSocket::get_tcp_keepalive_intvl
   *
   * ...
  */
  public function get_tcp_keepalive_intvl() {}

  /**
   * ZSocket::get_tcp_accept_filter
   *
   * ...
  */
  public function get_tcp_accept_filter() {}

  /**
   * ZSocket::get_rcvmore
   *
   * ...
  */
  public function get_rcvmore() {}

  /**
   * ZSocket::get_events
   *
   * ...
  */
  public function get_events() {}

  /**
   * ZSocket::get_last_endpoint
   *
   * ...
  */
  public function get_last_endpoint() {}

  /**
   * ZSocket::set_tos
   *
   * ...
  */
  public function set_tos() {}

  /**
   * ZSocket::set_router_handover
   *
   * ...
  */
  public function set_router_handover() {}

  /**
   * ZSocket::set_router_mandatory
   *
   * ...
  */
  public function set_router_mandatory() {}

  /**
   * ZSocket::set_probe_router
   *
   * ...
  */
  public function set_probe_router() {}

  /**
   * ZSocket::set_req_relaxed
   *
   * ...
  */
  public function set_req_relaxed() {}

  /**
   * ZSocket::set_req_correlate
   *
   * ...
  */
  public function set_req_correlate() {}

  /**
   * ZSocket::set_conflate
   *
   * ...
  */
  public function set_conflate() {}

  /**
   * ZSocket::set_zap_domain
   *
   * ...
  */
  public function set_zap_domain() {}

  /**
   * ZSocket::set_plain_server
   *
   * ...
  */
  public function set_plain_server() {}

  /**
   * ZSocket::set_plain_username
   *
   * ...
  */
  public function set_plain_username() {}

  /**
   * ZSocket::set_plain_password
   *
   * ...
  */
  public function set_plain_password() {}

  /**
   * ZSocket::set_curve_server
   *
   * ...
  */
  public function set_curve_server() {}

  /**
   * ZSocket::set_curve_publickey
   *
   * ...
  */
  public function set_curve_publickey() {}

  /**
   * ZSocket::set_curve_publickey_bin
   *
   * ...
  */
  public function set_curve_publickey_bin() {}

  /**
   * ZSocket::set_curve_secretkey
   *
   * ...
  */
  public function set_curve_secretkey() {}

  /**
   * ZSocket::set_curve_secretkey_bin
   *
   * ...
  */
  public function set_curve_secretkey_bin() {}

  /**
   * ZSocket::set_curve_serverkey
   *
   * ...
  */
  public function set_curve_serverkey() {}

  /**
   * ZSocket::set_curve_serverkey_bin
   *
   * ...
  */
  public function set_curve_serverkey_bin() {}

  /**
   * ZSocket::set_gssapi_server
   *
   * ...
  */
  public function set_gssapi_server() {}

  /**
   * ZSocket::set_gssapi_plaintext
   *
   * ...
  */
  public function set_gssapi_plaintext() {}

  /**
   * ZSocket::set_gssapi_principal
   *
   * ...
  */
  public function set_gssapi_principal() {}

  /**
   * ZSocket::set_gssapi_service_principal
   *
   * ...
  */
  public function set_gssapi_service_principal() {}

  /**
   * ZSocket::set_ipv6
   *
   * ...
  */
  public function set_ipv6() {}

  /**
   * ZSocket::set_immediate
   *
   * ...
  */
  public function set_immediate() {}

  /**
   * ZSocket::set_router_raw
   *
   * ...
  */
  public function set_router_raw() {}

  /**
   * ZSocket::set_ipv4only
   *
   * ...
  */
  public function set_ipv4only() {}

  /**
   * ZSocket::set_delay_attach_on_connect
   *
   * ...
  */
  public function set_delay_attach_on_connect() {}

  /**
   * ZSocket::set_sndhwm
   *
   * ...
  */
  public function set_sndhwm() {}

  /**
   * ZSocket::set_rcvhwm
   *
   * ...
  */
  public function set_rcvhwm() {}

  /**
   * ZSocket::set_affinity
   *
   * ...
  */
  public function set_affinity() {}

  /**
   * ZSocket::set_subscribe
   *
   * ...
  */
  public function set_subscribe() {}

  /**
   * ZSocket::set_unsubscribe
   *
   * ...
  */
  public function set_unsubscribe() {}

  /**
   * ZSocket::set_identity
   *
   * ...
  */
  public function set_identity() {}

  /**
   * ZSocket::set_rate
   *
   * ...
  */
  public function set_rate() {}

  /**
   * ZSocket::set_recovery_ivl
   *
   * ...
  */
  public function set_recovery_ivl() {}

  /**
   * ZSocket::set_sndbuf
   *
   * ...
  */
  public function set_sndbuf() {}

  /**
   * ZSocket::set_rcvbuf
   *
   * ...
  */
  public function set_rcvbuf() {}

  /**
   * ZSocket::set_linger
   *
   * ...
  */
  public function set_linger() {}

  /**
   * ZSocket::set_reconnect_ivl
   *
   * ...
  */
  public function set_reconnect_ivl() {}

  /**
   * ZSocket::set_reconnect_ivl_max
   *
   * ...
  */
  public function set_reconnect_ivl_max() {}

  /**
   * ZSocket::set_backlog
   *
   * ...
  */
  public function set_backlog() {}

  /**
   * ZSocket::set_maxmsgsize
   *
   * ...
  */
  public function set_maxmsgsize() {}

  /**
   * ZSocket::set_multicast_hops
   *
   * ...
  */
  public function set_multicast_hops() {}

  /**
   * ZSocket::set_rcvtimeo
   *
   * ...
  */
  public function set_rcvtimeo() {}

  /**
   * ZSocket::set_sndtimeo
   *
   * ...
  */
  public function set_sndtimeo() {}

  /**
   * ZSocket::set_xpub_verbose
   *
   * ...
  */
  public function set_xpub_verbose() {}

  /**
   * ZSocket::set_tcp_keepalive
   *
   * ...
  */
  public function set_tcp_keepalive() {}

  /**
   * ZSocket::set_tcp_keepalive_idle
   *
   * ...
  */
  public function set_tcp_keepalive_idle() {}

  /**
   * ZSocket::set_tcp_keepalive_cnt
   *
   * ...
  */
  public function set_tcp_keepalive_cnt() {}

  /**
   * ZSocket::set_tcp_keepalive_intvl
   *
   * ...
  */
  public function set_tcp_keepalive_intvl() {}

  /**
   * ZSocket::set_tcp_accept_filter
   *
   * ...
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
   * ZProxy::__construct
   *
   * ...
  */
  public function __construct() {}

  /**
   * ZProxy::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * ZProxy::pause
   *
   * ...
  */
  public function pause() {}

  /**
   * ZProxy::resume
   *
   * ...
  */
  public function resume() {}

  /**
   * ZProxy::recv
   *
   * Recieve a ZMsg.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ZProxy::set_frontend
   *
   * ...
   * @param mixed $socket_type ...
   * @param mixed $socket_endpoint ...
  */
  public function set_frontend($socket_type, $socket_endpoint) {}

  /**
   * ZProxy::set_backend
   *
   * ...
   * @param mixed $socket_type ...
   * @param mixed $socket_endpoint ...
  */
  public function set_backend($socket_type, $socket_endpoint) {}

  /**
   * ZProxy::set_capture
   *
   * ...
   * @param mixed $socket_endpoint ...
  */
  public function set_capture($socket_endpoint) {}

  /**
   * ZProxy::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * ZProxy::get_socket
   *
   * Get the underlying ZSocket.
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
   * ZBeacon::__construct
   *
   * ...
  */
  public function __construct() {}

  /**
   * ZBeacon::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * ZBeacon::set_port
   *
   * ...
   * @param mixed $port ...
  */
  public function set_port($port) {}

  /**
   * ZBeacon::subscribe
   *
   * ...
   * @param mixed $filter ...
  */
  public function subscribe($filter) {}

  /**
   * ZBeacon::unsubscribe
   *
   * ...
  */
  public function unsubscribe() {}

  /**
   * ZBeacon::publish
   *
   * ...
   * @param mixed $data ...
   * @param mixed $interval ... (optional)
  */
  public function publish($data, $interval) {}

  /**
   * ZBeacon::silence
   *
   * ...
  */
  public function silence() {}

  /**
   * ZBeacon::recv
   *
   * Recieve a ZMsg.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ZBeacon::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * ZBeacon::get_socket
   *
   * Get the underlying ZSocket.
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
   * ZAuth::__construct
   *
   *  
  */
  public function __construct() {}

  /**
   * ZAuth::set_verbose
   *
   * Enable verbose logging of commands and activity. Verbose logging can help
   * debug non-trivial authentication policies
  */
  public function set_verbose() {}

  /**
   * ZAuth::recv
   *
   * Recieve a ZMsg.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ZAuth::allow
   *
   * Allow (whitelist) a list of IP addresses. For NULL, all clients from
   * these addresses will be accepted. For PLAIN and CURVE, they will be
   * allowed to continue with authentication. You can call this method
   * multiple times to whitelist more IP addresses. If you whitelist one
   * or nmore addresses, any non-whitelisted addresses are treated as
   * blacklisted
   * @param string $ip ip address
  */
  public function allow($ip) {}

  /**
   * ZAuth::deny
   *
   * Deny (blacklist) a list of IP addresses. For all security mechanisms,
   * this rejects the connection without any further authentication. Use
   * either a whitelist, or a blacklist, not not both. If you define both
   * a whitelist and a blacklist, only the whitelist takes effect
   * @param string $ip ip address
  */
  public function deny($ip) {}

  /**
   * ZAuth::configure
   *
   *  
  */
  public function configure() {}

  /**
   * ZAuth::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * ZAuth::get_socket
   *
   * Get the underlying ZSocket.
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
   * ZGossip::__construct
   *
   *  
  */
  public function __construct() {}

  /**
   * ZGossip::set_verbose
   *
   * Enable verbose logging of commands and activity.
  */
  public function set_verbose() {}

  /**
   * ZGossip::configure
   *
   * ...
   * @param mixed $filename ...
  */
  public function configure($filename) {}

  /**
   * ZGossip::bind
   *
   * ...
   * @param mixed $endpoint ...
  */
  public function bind($endpoint) {}

  /**
   * ZGossip::connect
   *
   * ...
   * @param mixed $endpoint ...
  */
  public function connect($endpoint) {}

  /**
   * ZGossip::set
   *
   * ...
   * @param mixed $property ...
   * @param mixed $value ...
  */
  public function set($property, $value) {}

  /**
   * ZGossip::publish
   *
   * ...
   * @param mixed $property ...
   * @param mixed $value ...
  */
  public function publish($property, $value) {}

  /**
   * ZGossip::count
   *
   * ...
  */
  public function count() {}

  /**
   * ZGossip::recv
   *
   * Recieve a ZMsg.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ZGossip::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * ZGossip::get_socket
   *
   * Get the underlying ZSocket.
   * @return \ZSocket
  */
  public function get_socket() {}

}


/**
 * Zyre
 *
 * Zyre does local area discovery and clustering. A Zyre node broadcasts UDP beacons, and connects to peers that it finds.
 */
class Zyre implements \IZSocket, \IZDescriptor {

  /**
   * Zyre::__construct
   *
   * Creates a new Zyre node. Note that until you start the node it is silent and invisible to other nodes on the network.
   * @param string $name Zyre node name. (optional)
  */
  public function __construct($name) {}

  /**
   * Zyre::start
   *
   * Start node, after setting header values. When you start a node it begins discovery and connection.
  */
  public function start() {}

  /**
   * Zyre::stop
   *
   * Stop node, this signals to other peers that this node will go away. This is polite; however you can also just destroy the node without stopping it.
  */
  public function stop() {}

  /**
   * Zyre::recv
   *
   * Receive next message from network. The message may be a control message (ENTER, EXIT, JOIN, LEAVE) or data (WHISPER, SHOUT). Returns ZMsg object, or NULL if interrupted.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Zyre::dump
   *
   * Dump the Zyre node configuration.
  */
  public function dump() {}

  /**
   * Zyre::get_uuid
   *
   * Get the UUID of the Zyre node
   * @return string
  */
  public function get_uuid() {}

  /**
   * Zyre::get_name
   *
   * Get then Zyre node name.
   * @return string
  */
  public function get_name() {}

  /**
   * Zyre::get_peers
   *
   * Return a list of known peers.
   * @return array
  */
  public function get_peers() {}

  /**
   * Zyre::get_groups
   *
   * Return a list of known groups.
   * @return array
  */
  public function get_groups() {}

  /**
   * Zyre::get_peer_groups
   *
   * ...
  */
  public function get_peer_groups() {}

  /**
   * Zyre::set_endpoint
   *
   * By default, Zyre binds to an ephemeral TCP port and broadcasts the local
   * host name using UDP beaconing. When you call this method, Zyre will use
   * gossip discovery instead of UDP beaconing. You MUST set-up the gossip
   * service separately using zyre_gossip_bind() and _connect(). Note that the
   * endpoint MUST be valid for both bind and connect operations. You can use
   * inproc://, ipc://, or tcp:// transports (for tcp://, use an IP address
   * that is meaningful to remote as well as local nodes). Returns true if
   * the bind was successful.
   * @param string $endpoint  
  */
  public function set_endpoint($endpoint) {}

  /**
   * Zyre::set_port
   *
   * Set UDP beacon discovery port; defaults to 5670, this call overrides that so you can create independent clusters on the same network, for e.g. development vs. production. Has no effect after node start.
   * @param int $port ...
  */
  public function set_port($port) {}

  /**
   * Zyre::set_interface
   *
   * Set network interface for UDP beacons. If you do not set this, CZMQ will
   * choose an interface for you. On boxes with several interfaces you should
   * specify which one you want to use, or strange things can happen.
   * @param string $interface  
  */
  public function set_interface($interface) {}

  /**
   * Zyre::set_interval
   *
   * Set UDP beacon discovery interval, in milliseconds. Default is instant beacon exploration followed by pinging every 1,000 msecs.
   * @param int $interval ...
  */
  public function set_interval($interval) {}

  /**
   * Zyre::gossip_bind
   *
   * Set-up gossip discovery of other nodes. At least one node in the cluster
   * must bind to a well-known gossip endpoint, so other nodes can connect to
   * it. Note that gossip endpoints are completely distinct from Zyre node
   * endpoints, and should not overlap (they can use the same transport).   
   * @param string $endpoint  
  */
  public function gossip_bind($endpoint) {}

  /**
   * Zyre::gossip_connect
   *
   * Set-up gossip discovery of other nodes. A node may connect to multiple
   * other nodes, for redundancy paths. For details of the gossip network
   * design, see the CZMQ zgossip class.      
   * @param string $endpoint  
  */
  public function gossip_connect($endpoint) {}

  /**
   * Zyre::get_peer_header
   *
   * Return the value of a header of a conected peer.
   * @param string $name  
   * @return mixed
  */
  public function get_peer_header($name) {}

  /**
   * Zyre::get_version
   *
   * Get Zyre version.
   * @return string
  */
  static public function get_version() {}

  /**
   * Zyre::set_verbose
   *
   * Set verbose mode; this tells the node to log all traffic as well as all major events.
  */
  public function set_verbose() {}

  /**
   * Zyre::set_header
   *
   * Set node header; these are provided to other nodes during discovery and come in each ENTER message.
   * @param string $name ...
   * @param mixed $value ...
  */
  public function set_header($name, $value) {}

  /**
   * Zyre::join
   *
   * Join a named group; after joining a group you can send messages to the group and all Zyre nodes in that group will receive them.
   * @param string $group Group name to join.
  */
  public function join($group) {}

  /**
   * Zyre::leave
   *
   * Leave a joined group
   * @param string $group Group name to leave.
  */
  public function leave($group) {}

  /**
   * Zyre::send_peer
   *
   * Send message to single peer, specified as a UUID string.
   * @param string $peer Peer UUID.
   * @param mixed $data ...
  */
  public function send_peer($peer, $data) {}

  /**
   * Zyre::send_group
   *
   * Send message to a named group.
   * @param string $group Group name.
   * @param mixed $data ...
  */
  public function send_group($group, $data) {}

  /**
   * Zyre::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Zyre::get_socket
   *
   * Get the underlying ZSocket.
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
   * ZInotify::watch
   *
   * ...
  */
  public function watch() {}

  /**
   * ZInotify::remove
   *
   * ...
  */
  public function remove() {}

  /**
   * ZInotify::recv
   *
   * Recieve a ZMsg.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * ZInotify::get_fd
   *
   * ...
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
   * ZStdIn::recv
   *
   * ...
   * @return string
  */
  public function recv() {}

  /**
   * ZStdIn::send
   *
   * ...
  */
  public function send() {}

  /**
   * ZStdIn::get_fd
   *
   * ...
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
   * ZStdOut::recv
   *
   * ...
   * @return string
  */
  public function recv() {}

  /**
   * ZStdOut::send
   *
   * ...
  */
  public function send() {}

  /**
   * ZStdOut::get_fd
   *
   * ...
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
   * ZStdErr::recv
   *
   * ...
   * @return string
  */
  public function recv() {}

  /**
   * ZStdErr::send
   *
   * ...
  */
  public function send() {}

  /**
   * ZStdErr::get_fd
   *
   * ...
  */
  public function get_fd() {}

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
   * Broker::__construct
   *
   * ...
   * @param mixed $endpoint ... (optional)
   * @param mixed $verbose ... (optional)
  */
  public function __construct($endpoint, $verbose) {}

  /**
   * Broker::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * Broker::load_config
   *
   * ...
  */
  public function load_config() {}

  /**
   * Broker::save_config
   *
   * ...
  */
  public function save_config() {}

  /**
   * Broker::set_config
   *
   * ...
  */
  public function set_config() {}

  /**
   * Broker::bind
   *
   * ...
  */
  public function bind() {}

  /**
   * Broker::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Broker::get_socket
   *
   * Get the underlying ZSocket.
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
   * Worker::__construct
   *
   * ...
   * @param mixed $name ...
   * @param mixed $broker_endpoint ...
   * @param callable $callback ...
  */
  public function __construct($name, $broker_endpoint, $callback) {}

  /**
   * Worker::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * Worker::run
   *
   * ...
  */
  public function run() {}

  /**
   * Worker::process
   *
   * ...
  */
  public function process() {}

  /**
   * Worker::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Worker::get_socket
   *
   * Get the underlying ZSocket.
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
   * Client::__construct
   *
   * ...
   * @param mixed $broker_endpoint ...
  */
  public function __construct($broker_endpoint) {}

  /**
   * Client::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * Client::recv
   *
   * Recieve a ZMsg.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Client::call
   *
   * ...
   * @param mixed $service_name ...
  */
  public function call($service_name) {}

  /**
   * Client::call_async
   *
   * ...
   * @param mixed $service_name ...
  */
  public function call_async($service_name) {}

  /**
   * Client::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Client::get_socket
   *
   * Get the underlying ZSocket.
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
   * Broker::__construct
   *
   * ...
  */
  public function __construct() {}

  /**
   * Broker::bind
   *
   * ...
  */
  public function bind() {}

  /**
   * Broker::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * Broker::get_status
   *
   * ...
  */
  public function get_status() {}

  /**
   * Broker::set_capture
   *
   * ...
   * @param mixed $socket_endpoint ...
  */
  public function set_capture($socket_endpoint) {}

  /**
   * Broker::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Broker::get_socket
   *
   * Get the underlying ZSocket.
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
   * Worker::__construct
   *
   * ...
   * @param mixed $broker_endpoint ...
   * @param mixed $name ...
   * @param mixed $verbose ... (optional)
  */
  public function __construct($broker_endpoint, $name, $verbose) {}

  /**
   * Worker::run
   *
   * ...
   * @param callable $callback ...
  */
  public function run($callback) {}

  /**
   * Worker::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Worker::get_socket
   *
   * Get the underlying ZSocket.
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
   * Client::__construct
   *
   * ...
  */
  public function __construct() {}

  /**
   * Client::call
   *
   * ...
  */
  public function call() {}

  /**
   * Client::call_async
   *
   * ...
  */
  public function call_async() {}

  /**
   * Client::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Client::get_socket
   *
   * Get the underlying ZSocket.
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
   * Broker::__construct
   *
   * ...
  */
  public function __construct() {}

  /**
   * Broker::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * Broker::bind
   *
   * ...
  */
  public function bind() {}

  /**
   * Broker::load_config
   *
   * ...
  */
  public function load_config() {}

  /**
   * Broker::save_config
   *
   * ...
  */
  public function save_config() {}

  /**
   * Broker::set_config
   *
   * ...
  */
  public function set_config() {}

  /**
   * Broker::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Broker::get_socket
   *
   * Get the underlying ZSocket.
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
   * Worker::__construct
   *
   * ...
   * @param mixed $endpoint ...
   * @param mixed $address ...
   * @param mixed $pattern ... (optional)
  */
  public function __construct($endpoint, $address, $pattern) {}

  /**
   * Worker::set_timeout
   *
   * ...
   * @param mixed $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * Worker::run
   *
   * ...
   * @param callable $callback ...
  */
  public function run($callback) {}

  /**
   * Worker::get_client
   *
   * Get the underlying Malamute Client.
   * @return Malamute\Client
  */
  public function get_client() {}

  /**
   * Worker::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Worker::get_socket
   *
   * Get the underlying ZSocket.
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
   * Client::__construct
   *
   * ...
   * @param mixed $endpoint ...
   * @param mixed $address ... (optional)
   * @param mixed $timeout ... (optional)
  */
  public function __construct($endpoint, $address, $timeout) {}

  /**
   * Client::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * Client::connect
   *
   * ...
   * @param mixed $endpoint ... (optional)
   * @param mixed $address ... (optional)
   * @param mixed $timeout ... (optional)
  */
  public function connect($endpoint, $address, $timeout) {}

  /**
   * Client::header
   *
   * ...
  */
  public function header() {}

  /**
   * Client::content
   *
   * ...
  */
  public function content() {}

  /**
   * Client::set_producer
   *
   * ...
   * @param mixed $stream ...
  */
  public function set_producer($stream) {}

  /**
   * Client::set_worker
   *
   * ...
   * @param mixed $address ...
   * @param mixed $patern ...
  */
  public function set_worker($address, $patern) {}

  /**
   * Client::set_consumer
   *
   * ...
   * @param mixed $stream ...
   * @param mixed $patern ...
  */
  public function set_consumer($stream, $patern) {}

  /**
   * Client::send_stream
   *
   * ...
   * @param mixed $subject ...
  */
  public function send_stream($subject) {}

  /**
   * Client::send_mailbox
   *
   * ...
   * @param mixed $address ...
   * @param mixed $payload ... (optional)
   * @param mixed $timeout ... (optional)
   * @param mixed $subject ... (optional)
   * @param mixed $tracker ... (optional)
  */
  public function send_mailbox($address, $payload, $timeout, $subject, $tracker) {}

  /**
   * Client::send_service
   *
   * ...
   * @param mixed $address ...
   * @param mixed $subject ...
   * @param mixed $payload ... (optional)
   * @param mixed $timeout ... (optional)
   * @param mixed $tracker ... (optional)
  */
  public function send_service($address, $subject, $payload, $timeout, $tracker) {}

  /**
   * Client::recv
   *
   * Recieve a ZMsg.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Client::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Client::get_socket
   *
   * Get the underlying ZSocket.
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
   * Producer::__construct
   *
   * ...
   * @param mixed $endpoint ...
   * @param mixed $stream ...
  */
  public function __construct($endpoint, $stream) {}

  /**
   * Producer::set_timeout
   *
   * ...
   * @param mixed $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * Producer::run
   *
   * ...
   * @param mixed $subject ...
   * @param callable $callback ...
  */
  public function run($subject, $callback) {}

  /**
   * Producer::get_client
   *
   * Get the underlying Malamute Client.
   * @return Malamute\Client
  */
  public function get_client() {}

  /**
   * Producer::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Producer::get_socket
   *
   * Get the underlying ZSocket.
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
   * Consumer::__construct
   *
   * ...
   * @param mixed $endpoint ...
   * @param mixed $stream ...
  */
  public function __construct($endpoint, $stream) {}

  /**
   * Consumer::set_timeout
   *
   * ...
   * @param mixed $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * Consumer::header
   *
   * ...
   * @param mixed $header ... (optional)
  */
  public function header($header) {}

  /**
   * Consumer::run
   *
   * ...
   * @param mixed $pattern ...
   * @param callable $callback ...
  */
  public function run($pattern, $callback) {}

  /**
   * Consumer::get_client
   *
   * Get the underlying Malamute Client.
   * @return Malamute\Client
  */
  public function get_client() {}

  /**
   * Consumer::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Consumer::get_socket
   *
   * Get the underlying ZSocket.
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
   * Server::__construct
   *
   * ...
  */
  public function __construct() {}

  /**
   * Server::set_verbose
   *
   * ...
  */
  public function set_verbose() {}

  /**
   * Server::load_config
   *
   * ...
  */
  public function load_config() {}

  /**
   * Server::set_config
   *
   * ...
  */
  public function set_config() {}

  /**
   * Server::save_config
   *
   * ...
  */
  public function save_config() {}

  /**
   * Server::bind
   *
   * ...
  */
  public function bind() {}

  /**
   * Server::publish
   *
   * ...
   * @param mixed $local_path ...
   * @param mixed $alias ...
  */
  public function publish($local_path, $alias) {}

  /**
   * Server::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Server::get_socket
   *
   * Get the underlying ZSocket.
   * @return \ZSocket
  */
  public function get_socket() {}

  /**
   * Server::recv
   *
   * Recieve a ZMsg.
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
   * Client::__construct
   *
   * ...
   * @param mixed $endpoint ...
   * @param mixed $local_path ...
   * @param mixed $timeout ... (optional)
  */
  public function __construct($endpoint, $local_path, $timeout) {}

  /**
   * Client::set_timeout
   *
   * ...
   * @param mixed $timeout ...
  */
  public function set_timeout($timeout) {}

  /**
   * Client::connect
   *
   * ...
  */
  public function connect() {}

  /**
   * Client::subscribe
   *
   * ...
   * @param mixed $remote_path ...
  */
  public function subscribe($remote_path) {}

  /**
   * Client::recv
   *
   * Recieve a ZMsg.
   * @return \ZMsg
  */
  public function recv() {}

  /**
   * Client::get_fd
   *
   * Get the underlying File Descriptor.
   * @return int
  */
  public function get_fd() {}

  /**
   * Client::get_socket
   *
   * Get the underlying ZSocket.
   * @return \ZSocket
  */
  public function get_socket() {}

}

}
