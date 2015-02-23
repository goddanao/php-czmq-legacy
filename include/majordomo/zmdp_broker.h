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

void zmdpbroker (zsock_t *pipe, void *unused);