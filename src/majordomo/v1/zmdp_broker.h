#pragma once

#include <czmq.h>
#include "zmdp_common.h"

typedef struct {
    zsock_t *pipe;              //  Actor command pipe
    zpoller_t *poller;          //  Socket poller
    zsock_t *socket;            //  Frontend socket
    zsock_t *capture;           //  Capture socket
    bool terminated;            //  Did caller ask us to quit?
    bool verbose;               //  Verbose logging enabled?

    zhash_t *services;          //  Hash of known services
	zhash_t *workers;           //  Hash of known workers
	zlist_t *waiting;           //  List of waiting workers
	uint64_t heartbeat_at;      //  When to send HEARTBEAT

} broker_t;

typedef struct {
    broker_t *broker;           //  Broker instance
    char *name;                 //  Service name
    zlist_t *requests;          //  List of client requests
    zlist_t *waiting;           //  List of waiting workers
    size_t workers;             //  How many workers we have
    zlist_t *blacklist;
} service_t;

typedef struct {
    broker_t *broker;           //  Broker instance
    char *identity;             //  Identity of worker
    zframe_t *address;          //  Address frame to route to
    service_t *service;         //  Owning service, if known
    int64_t expiry;             //  Expires at unless heartbeat
} worker_t;

static void
    s_broker_worker_msg (broker_t *self, zframe_t *sender, zmsg_t *msg);
static void
    s_broker_client_msg (broker_t *self, zframe_t *sender, zmsg_t *msg);
static void
    s_broker_purge (broker_t *self);

static service_t *
    s_service_require (broker_t *self, zframe_t *service_frame);
static void
    s_service_destroy (void *argument);
static void
    s_service_dispatch (service_t *service);
static void
    s_service_enable_command (service_t *self, const char *command);
static void
    s_service_disable_command (service_t *self, const char *command);
static int
    s_service_is_command_enabled (service_t *self, const char *command);

static worker_t *
    s_worker_require (broker_t *self, zframe_t *address);
static void
    s_worker_delete (worker_t *self, int disconnect);
static void
    s_worker_destroy (void *argument);
static void
    s_worker_send (worker_t *self, char *command, char *option, zmsg_t *msg);
static void
    s_worker_waiting (worker_t *self);


static void
s_self_destroy (broker_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        broker_t *self = *self_p;
        zsock_destroy (&self->socket);
        zsock_destroy (&self->capture);
        zhash_destroy (&self->services);
		zhash_destroy (&self->workers);
		zlist_destroy (&self->waiting);
		zpoller_destroy (&self->poller);
		free (self);
        *self_p = NULL;
    }
}

static broker_t *
s_self_new (zsock_t *pipe)
{
    broker_t *self = (broker_t *) zmalloc (sizeof (broker_t));
    if (self) {
        self->pipe = pipe;
        self->services = zhash_new ();
		self->workers = zhash_new ();
		self->waiting = zlist_new ();
		self->poller = zpoller_new (self->pipe, NULL);
        if (!self->poller)
            s_self_destroy (&self);
        self->heartbeat_at = zclock_time () + HEARTBEAT_INTERVAL;
    }
    return self;
}


static zsock_t *
s_create_socket (char *type_name, char *endpoints)
{
    //  This array matches ZMQ_XXX type definitions
    assert (ZMQ_PAIR == 0);
    char *type_names [] = {
        "PAIR", "PUB", "SUB", "REQ", "REP",
        "DEALER", "ROUTER", "PULL", "PUSH",
        "XPUB", "XSUB", type_name
    };
    //  We always match type at least at end of table
    int index;
    for (index = 0; strneq (type_name, type_names [index]); index++) ;
    if (index > ZMQ_XSUB) {
        zsys_error ("zmdpbroker: invalid socket type '%s'", type_name);
        return NULL;
    }
    zsock_t *sock = zsock_new (index);
    if (sock) {
        if (zsock_attach (sock, endpoints, true)) {
            zsys_error ("zmdpbroker: invalid endpoints '%s'", endpoints);
            zsock_destroy (&sock);
        }
    }
    return sock;
}

static void
s_self_configure (broker_t *self, zsock_t **sock_p, zmsg_t *request, char *name)
{
    char *endpoints = zmsg_popstr (request);
    assert (endpoints);
    if (self->verbose) {
        zsys_info ("zmonitor: - %s type=%s attach=%s", name, "ROUTER", endpoints);
    }
    assert (*sock_p == NULL);
    *sock_p = s_create_socket ("ROUTER", endpoints);
    assert (*sock_p);
    zpoller_add (self->poller, *sock_p);
    zstr_free (&endpoints);
}

//  --------------------------------------------------------------------------
//  Handle a command from calling application

static int
s_self_handle_pipe (broker_t *self)
{
    //  Get the whole message off the pipe in one go
    zmsg_t *request = zmsg_recv (self->pipe);
    if (!request)
        return -1;                  //  Interrupted

    char *command = zmsg_popstr (request);
    assert (command);
    if (self->verbose)
        zsys_info ("zmdpbroker: API command=%s", command);

    if (streq (command, "BIND")) {
        s_self_configure (self, &self->socket, request, "mdpbroker");
        zsock_signal (self->pipe, 0);
    }
    else
    if (streq (command, "CAPTURE")) {
        self->capture = zsock_new (ZMQ_PUSH);
        assert (self->capture);
        char *endpoint = zmsg_popstr (request);
        assert (endpoint);
        int rc = zsock_connect (self->capture, "%s", endpoint);
        assert (rc == 0);
        zstr_free (&endpoint);
        zsock_signal (self->pipe, 0);
    }
    else
    if (streq (command, "PAUSE")) {
        zpoller_destroy (&self->poller);
        self->poller = zpoller_new (self->pipe, NULL);
        assert (self->poller);
        zsock_signal (self->pipe, 0);
    }
    else
    if (streq (command, "RESUME")) {
        zpoller_destroy (&self->poller);
        self->poller = zpoller_new (self->pipe, self->socket, NULL);
        assert (self->poller);
        zsock_signal (self->pipe, 0);
    }
    else
     if (streq (command, "STATUS")) {
         zsock_signal (self->pipe, 0);
         zsock_send(self->pipe, "ppp", self->services, self->workers, self->waiting);
         zsock_signal (self->pipe, 0);
     }
    else
    if (streq (command, "VERBOSE")) {
        self->verbose = true;
        zsock_signal (self->pipe, 0);
    }
    else
    if (streq (command, "$TERM"))
        self->terminated = true;
    else {
        zsys_error ("zmdpbroker: - invalid command: %s", command);
        assert (false);
    }
    zstr_free (&command);
    zmsg_destroy (&request);
    return 0;
}


//  --------------------------------------------------------------------------
//  Switch messages from an input socket to an output socket until there are
//  no messages left waiting. We use this loop rather than zmq_poll, to reduce
//  the cost of polling, which is non-trivial on some boxes (OS/X, mainly).

//static void
//s_self_switch (broker_t *self, zsock_t *input, zsock_t *output)
//{
//    //  We use the low-level libzmq API for best performance
//    void *zmq_input = zsock_resolve (input);
//    void *zmq_output = zsock_resolve (output);
//    void *zmq_capture = self->capture ? zsock_resolve (self->capture) : NULL;
//
//    zmq_msg_t msg;
//    zmq_msg_init (&msg);
//    while (true) {
//        if (zmq_recvmsg (zmq_input, &msg, ZMQ_DONTWAIT) == -1)
//            break;      //  Presumably EAGAIN
//        int send_flags = zsock_rcvmore (zmq_input) ? ZMQ_SNDMORE : 0;
//        if (zmq_capture) {
//            zmq_msg_t dup;
//            zmq_msg_init (&dup);
//            zmq_msg_copy (&dup, &msg);
//            if (zmq_sendmsg (zmq_capture, &dup, send_flags) == -1)
//                zmq_msg_close (&dup);
//        }
//        if (zmq_sendmsg (zmq_output, &msg, send_flags) == -1) {
//            zmq_msg_close (&msg);
//            break;
//        }
//    }
//}

static void s_self_broker (broker_t *self, zsock_t *input)
{
	zmsg_t *msg = zmsg_recv (self->socket);
	if (self->verbose) {
		zclock_log ("I: received message:");
		zmsg_dump (msg);
	}
	zframe_t *sender = zmsg_pop (msg);
	zframe_t *empty  = zmsg_pop (msg);
	zframe_t *header = zmsg_pop (msg);

	if (zframe_streq (header, MDPC_CLIENT))
		s_broker_client_msg (self, sender, msg);
	else
	if (zframe_streq (header, MDPW_WORKER))
		s_broker_worker_msg (self, sender, msg);
	else {
		zclock_log ("E: invalid message:");
		zmsg_dump (msg);
		zmsg_destroy (&msg);
	}
	zframe_destroy (&sender);
	zframe_destroy (&empty);
	zframe_destroy (&header);
}


//  --------------------------------------------------------------------------
//  zmdpbroker() implements the zmdpbroker actor interface

void
zmdpbroker (zsock_t *pipe, void *unused)
{
    broker_t *self = s_self_new (pipe);
    assert (self);
    //  Signal successful initialization
    zsock_signal (pipe, 0);

    int64_t last_tick = zclock_mono();
    while (!self->terminated) {
        zsock_t *which = (zsock_t *) zpoller_wait (self->poller, 1000 * ZMQ_POLL_MSEC);

        if (zpoller_expired(self->poller)) {

        	//  Disconnect and delete any expired workers
			//  Send heartbeats to idle workers if needed
			if (zclock_time () > self->heartbeat_at) {
				s_broker_purge (self);
				worker_t *worker = (worker_t *) zlist_first (self->waiting);
				while (worker) {
					s_worker_send (worker, MDPW_HEARTBEAT, NULL, NULL);
					worker = (worker_t *) zlist_next (self->waiting);
				}
				self->heartbeat_at = zclock_time () + HEARTBEAT_INTERVAL;
			}

        }
        else
        if (zpoller_terminated (self->poller)) {
            zstr_sendx(pipe, "$TERM", "", NULL);
            break;          //  Interrupted
        }
        else
        if (which == self->pipe)
            s_self_handle_pipe (self);
        else
        if (which == self->socket)
        	s_self_broker (self, self->socket);
    }
    s_self_destroy (&self);
}
















static void
s_broker_worker_msg (broker_t *self, zframe_t *sender, zmsg_t *msg)
{
    assert (zmsg_size (msg) >= 1);     //  At least, command

    zframe_t *command = zmsg_pop (msg);
    char *identity = zframe_strhex (sender);
    int worker_ready = (zhash_lookup (self->workers, identity) != NULL);
    zstr_free (&identity);
    worker_t *worker = s_worker_require (self, sender);

    if (zframe_streq (command, MDPW_READY)) {
        if (worker_ready)               //  Not first command in session
            s_worker_delete (worker, 1);
        else
        if (zframe_size (sender) >= 4  //  Reserved service name
        &&  memcmp (zframe_data (sender), "mmi.", 4) == 0)
            s_worker_delete (worker, 1);
        else {
            //  Attach worker to service and mark as idle
            zframe_t *service_frame = zmsg_pop (msg);
            worker->service = s_service_require (self, service_frame);
            zlist_append (self->waiting, worker);
            zlist_append (worker->service->waiting, worker);
            worker->service->workers++;
            worker->expiry = zclock_time () + HEARTBEAT_EXPIRY;
            s_service_dispatch (worker->service);
            zframe_destroy (&service_frame);
            //if(self->verbose)
            //    zclock_log ("worker created");
        }
    }
    else
    if (zframe_streq (command, MDPW_REPORT)) {
        if (worker_ready) {
            //  Remove & save client return envelope and insert the
            //  protocol header and service name, then rewrap envelope.
            zframe_t *client = zmsg_unwrap (msg);
            zmsg_pushstr (msg, worker->service->name);
            zmsg_pushstr (msg, MDPC_REPORT);
            zmsg_pushstr (msg, MDPC_CLIENT);
            zmsg_wrap (msg, client);
            zmsg_send (&msg, self->socket);
        }
        else
            s_worker_delete (worker, 1);
    }
    else
    if (zframe_streq (command, MDPW_HEARTBEAT)) {
        if (worker_ready) {
            if (zlist_size (self->waiting) > 1) {
                // Move worker to the end of the waiting queue,
                // so s_broker_purge will only check old worker(s)
                zlist_remove (self->waiting, worker);
                zlist_append (self->waiting, worker);
            }
            worker->expiry = zclock_time () + HEARTBEAT_EXPIRY;
        }
        else
            s_worker_delete (worker, 1);
    }
    else
    if (zframe_streq (command, MDPW_DISCONNECT))
        s_worker_delete (worker, 0);
    else {
        zclock_log ("E: invalid input message");
        zmsg_dump (msg);
    }
    zframe_destroy (&command);
    zmsg_destroy (&msg);
}

//  Process a request coming from a client. We implement MMI requests
//  directly here (at present, we implement only the mmi.service request)

static void
s_broker_client_msg (broker_t *self, zframe_t *sender, zmsg_t *msg)
{
    assert (zmsg_size (msg) >= 2);     //  Service name + body

    zframe_t *service_frame = zmsg_pop (msg);
    service_t *service = s_service_require (self, service_frame);

    //  If we got a MMI service request, process that internally
    if (zframe_size (service_frame) >= 4
    &&  memcmp (zframe_data (service_frame), "mmi.", 4) == 0) {
        char *return_code;
        if (zframe_streq (service_frame, "mmi.service")) {
            char *name = zframe_strdup (zmsg_last (msg));
            service_t *service =
                (service_t *) zhash_lookup (self->services, name);
            return_code = (char *) (service && service->workers? "200": "404");
            zstr_free (&name);
        }
        else
        // The filter service that can be used to manipulate
        // the command filter table.
        if (zframe_streq (service_frame, "mmi.filter")
        && zmsg_size (msg) == 3) {
            zframe_t *operation = zmsg_pop (msg);
            zframe_t *service_frame = zmsg_pop (msg);
            zframe_t *command_frame = zmsg_pop (msg);
            char *command_str = zframe_strdup (command_frame);

            if (zframe_streq (operation, "enable")) {
                service_t *service = s_service_require (self, service_frame);
                s_service_enable_command (service, command_str);
                return_code = "200";
            }
            else
            if (zframe_streq (operation, "disable")) {
                service_t *service = s_service_require (self, service_frame);
                s_service_disable_command (service, command_str);
                return_code = "200";
            }
            else
                return_code = "400";

            zframe_destroy (&operation);
            zframe_destroy (&service_frame);
            zframe_destroy (&command_frame);
            zstr_free (&command_str);
            //  Add an empty frame; it will be replaced by the return code.
            zmsg_pushstr (msg, "");
        }
        else
            return_code = "501";

        zframe_reset (zmsg_last (msg), return_code, strlen (return_code));

        //  Insert the protocol header and service name, then rewrap envelope.
        zmsg_push (msg, zframe_dup (service_frame));
        zmsg_pushstr (msg, MDPC_REPORT);
        zmsg_pushstr (msg, MDPC_CLIENT);
        zmsg_wrap (msg, zframe_dup (sender));
        zmsg_send (&msg, self->socket);
    }
    else {
        int enabled = 1;
        if (zmsg_size (msg) >= 1) {
            zframe_t *cmd_frame = zmsg_first (msg);
            char *cmd = zframe_strdup (cmd_frame);
            enabled = s_service_is_command_enabled (service, cmd);
            zstr_free (&cmd);
        }

        //  Forward the message to the worker.
        if (enabled) {
            zmsg_wrap (msg, zframe_dup (sender));
            zlist_append (service->requests, msg);
            s_service_dispatch (service);
            // zsys_info("Forwardin client request to worker!");

        }
        //  Send a NAK message back to the client.
        else {
            // zsys_info("NAK worker not enabled!");

            zmsg_push (msg, zframe_dup (service_frame));
            zmsg_pushstr (msg, MDPC_NAK);
            zmsg_pushstr (msg, MDPC_CLIENT);
            zmsg_wrap (msg, zframe_dup (sender));
            zmsg_send (&msg, self->socket);
        }
    }

    zframe_destroy (&service_frame);
}

//  The purge method deletes any idle workers that haven't pinged us in a
//  while. We hold workers from oldest to most recent, so we can stop
//  scanning whenever we find a live worker. This means we'll mainly stop
//  at the first worker, which is essential when we have large numbers of
//  workers (since we call this method in our critical path)

static void
s_broker_purge (broker_t *self)
{
    worker_t *worker = (worker_t *) zlist_first (self->waiting);
    while (worker) {
        if (zclock_time () < worker->expiry)
            break;                  //  Worker is alive, we're done here
        if (self->verbose)
            zclock_log ("I: deleting expired worker: %s",
                        worker->identity);

        s_worker_delete (worker, 0);
        worker = (worker_t *) zlist_first (self->waiting);
    }
}

//  Here is the implementation of the methods that work on a service.
//  Lazy constructor that locates a service by name, or creates a new
//  service if there is no service already with that name.

static service_t *
s_service_require (broker_t *self, zframe_t *service_frame)
{
    assert (service_frame);
    char *name = zframe_strdup (service_frame);

    service_t *service =
        (service_t *) zhash_lookup (self->services, name);
    if (service == NULL) {
        service = (service_t *) zmalloc (sizeof (service_t));
        service->broker = self;
        service->name = name;
        service->requests = zlist_new ();
        service->waiting = zlist_new ();
        service->blacklist = zlist_new ();
        zhash_insert (self->services, name, service);
        zhash_freefn (self->services, name, s_service_destroy);
        if (self->verbose)
            zclock_log ("I: added service: %s", name);
    }
    else
        zstr_free (&name);

    return service;
}

//  Service destructor is called automatically whenever the service is
//  removed from broker->services.

static void
s_service_destroy (void *argument)
{
    service_t *service = (service_t *) argument;
    while (zlist_size (service->requests)) {
        zmsg_t *msg = (zmsg_t*)zlist_pop (service->requests);
        zmsg_destroy (&msg);
    }
    //  Free memory keeping  blacklisted commands.
    char *command = (char *) zlist_first (service->blacklist);
    while (command) {
        zlist_remove (service->blacklist, command);
        zstr_free (&command);
    }
    zlist_destroy (&service->requests);
    zlist_destroy (&service->waiting);
    zlist_destroy (&service->blacklist);
    zstr_free (&service->name);
    free (service);
}

//  The dispatch method sends request to the worker.
static void
s_service_dispatch (service_t *self)
{
    assert (self);

    s_broker_purge (self->broker);
    if (zlist_size (self->waiting) == 0)
        return;

    while (zlist_size (self->requests) > 0) {
        worker_t *worker = (worker_t*)zlist_pop (self->waiting);
        zlist_remove (self->waiting, worker);
        zmsg_t *msg = (zmsg_t*)zlist_pop (self->requests);
        s_worker_send (worker, MDPW_REQUEST, NULL, msg);
        //  Workers are scheduled in the round-robin fashion
        zlist_append (self->waiting, worker);
        zmsg_destroy (&msg);
    }
}

static void
s_service_enable_command (service_t *self, const char *command)
{
    char *item = (char *) zlist_first (self->blacklist);
    while (item && !streq (item, command))
        item = (char *) zlist_next (self->blacklist);
    if (item) {
        zlist_remove (self->blacklist, item);
        zstr_free (&item);
    }
}

static void
s_service_disable_command (service_t *self, const char *command)
{
    char *item = (char *) zlist_first (self->blacklist);
    while (item && !streq (item, command))
        item = (char *) zlist_next (self->blacklist);
    if (!item)
        zlist_push (self->blacklist, strdup (command));
}

static int
s_service_is_command_enabled (service_t *self, const char *command)
{
    char *item = (char *) zlist_first (self->blacklist);
    while (item && !streq (item, command))
        item = (char *) zlist_next (self->blacklist);
    return item? 0: 1;
}

//  Here is the implementation of the methods that work on a worker.
//  Lazy constructor that locates a worker by identity, or creates a new
//  worker if there is no worker already with that identity.

static worker_t *
s_worker_require (broker_t *self, zframe_t *address)
{
    assert (address);

    //  self->workers is keyed off worker identity
    char *identity = zframe_strhex (address);
    worker_t *worker =
        (worker_t *) zhash_lookup (self->workers, identity);

    if (worker == NULL) {
        worker = (worker_t *) zmalloc (sizeof (worker_t));
        worker->broker = self;
        worker->identity = identity;
        worker->address = zframe_dup (address);
        zhash_insert (self->workers, identity, worker);
        zhash_freefn (self->workers, identity, s_worker_destroy);
        if (self->verbose)
            zclock_log ("I: registering new worker: %s", identity);
    }
    else
        zstr_free (&identity);
    return worker;
}

//  The delete method deletes the current worker.

static void
s_worker_delete (worker_t *self, int disconnect)
{
    assert (self);
    if (disconnect)
        s_worker_send (self, MDPW_DISCONNECT, NULL, NULL);

    if (self->service) {
        zlist_remove (self->service->waiting, self);
        self->service->workers--;
    }
    zlist_remove (self->broker->waiting, self);
    //  This implicitly calls s_worker_destroy
    zhash_delete (self->broker->workers, self->identity);
}

//  Worker destructor is called automatically whenever the worker is
//  removed from broker->workers.

static void
s_worker_destroy (void *argument)
{
    worker_t *self = (worker_t *) argument;
    zframe_destroy (&self->address);
    zstr_free (&self->identity);
    free (self);
}

//  The send method formats and sends a command to a worker. The caller may
//  also provide a command option, and a message payload.

static void
s_worker_send (worker_t *self, char *command, char *option, zmsg_t *msg)
{
    msg = msg? zmsg_dup (msg): zmsg_new ();

    //  Stack protocol envelope to start of message
    if (option)
        zmsg_pushstr (msg, option);
    zmsg_pushstr (msg, command);
    zmsg_pushstr (msg, MDPW_WORKER);

    //  Stack routing envelope to start of message
    zmsg_wrap (msg, zframe_dup (self->address));

    if (self->broker->verbose)
        zclock_log ("I: sending %s to worker", mdpw_commands [(int) *command]);

    zmsg_send (&msg, self->broker->socket);
}









//  --------------------------------------------------------------------------
//  Selftest

void
zmdpbroker_test (bool verbose)
{
    printf (" * zmdpbroker: ");
    if (verbose)
        printf ("\n");

    //  @selftest
    //  Create and configure our proxy
    zactor_t *proxy = zactor_new (zmdpbroker, NULL);
    assert (proxy);
    if (verbose) {
        zstr_sendx (proxy, "VERBOSE", NULL);
        zsock_wait (proxy);
    }
    zstr_sendx (proxy, "BIND", "inproc://broker", NULL);
    zsock_wait (proxy);

    //  Test pause/resume functionality
    zstr_sendx (proxy, "PAUSE", NULL);
    zsock_wait (proxy);

    zstr_sendx (proxy, "RESUME", NULL);
    zsock_wait (proxy);

    //  Test capture functionality
    zsock_t *capture = zsock_new_pull ("inproc://capture");
    assert (capture);

    //  Switch on capturing, check that it works
    zstr_sendx (proxy, "CAPTURE", "inproc://capture", NULL);
    zsock_wait (proxy);

    zsock_destroy (&capture);
    zactor_destroy (&proxy);
    //  @end
    printf ("OK\n");
}
