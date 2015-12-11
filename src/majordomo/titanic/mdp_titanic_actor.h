#pragma once

/*  =========================================================================
    mdp_titanic - Titanic Pattern Actor

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for ØMQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#include "../../common.h"
#include "mdp_titanic_process.h"
#include "mdp_titanic_request.h"
#include "mdp_titanic_reply.h"
#include "mdp_titanic_close.h"

//  --------------------------------------------------------------------------
//  The mdp_titanic_t structure holds the state for one actor instance

typedef struct {
    zsock_t *pipe;              //  Actor command pipe
    zpoller_t *poller;          //  Socket poller
    
    std::vector<zactor_t *> actors;
        
    //  ... you'll be adding other stuff here
    bool terminated;            //  Did caller ask us to quit?
    bool verbose;               //  Verbose logging enabled?
} mdp_titanic_t;

static mdp_titanic_t *
s_self_new (zsock_t *pipe, _actor_data *data)
{
    mdp_titanic_t *self = (mdp_titanic_t *) zmalloc (sizeof (mdp_titanic_t));
    self->actors = std::vector<zactor_t *>();
    self->pipe = pipe;
    self->poller = zpoller_new (self->pipe, NULL);

    // Process 1 thread
    self->actors.push_back(zactor_new(zmdp_titanic_process, (void*) data));

    // Request / Reply / Close multi-threaded
    int _threads = data->threads;
    while(_threads > 0) {
        self->actors.push_back(zactor_new(zmdp_titanic_request, (void*) data));
        self->actors.push_back(zactor_new(zmdp_titanic_reply, (void*) data));
        self->actors.push_back(zactor_new(zmdp_titanic_close, (void*) data));
        _threads--;
    }

    // Add all the actors to the msgpipe
    for(zactor_t *v : self->actors) {
        zpoller_add(self->poller, v);
    }

    return self;
}

static void
s_self_destroy (mdp_titanic_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        mdp_titanic_t *self = *self_p;
        //  ... destroy your own state here

        for(zactor_t *v : self->actors) {
            zactor_destroy((_zactor_t**) &(v));
        }

        zpoller_destroy (&self->poller);

        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Handle a command from calling application

static int
s_self_handle_pipe (mdp_titanic_t *self)
{
    //  Get the whole message off the pipe in one go
    zmsg_t *request = zmsg_recv (self->pipe);
    if (!request)
        return -1;                  //  Interrupted

    char *command = zmsg_popstr (request);
    if (self->verbose)
        zsys_info ("mdp_titanic: API command=%s", command);
    if (streq (command, "VERBOSE"))
        self->verbose = true;
    else
    //  An example of a command that the caller would wait for
    //  via a signal, so that the two threads synchronize
    if (streq (command, "WAIT"))
        zsock_signal (self->pipe, 0);
    else
    if (streq (command, "$TERM"))
        self->terminated = true;
    else {
        zsys_error ("mdp_titanic: - invalid command: %s", command);
        assert (false);
    }
    zstr_free (&command);
    zmsg_destroy (&request);
    return 0;
}


//  --------------------------------------------------------------------------
//  mdp_titanic() implements the mdp_titanic actor interface

void
mdp_titanic (zsock_t *pipe, void *args)
{
    mdp_titanic_t *self = s_self_new (pipe, (_actor_data *) args);
    //  Signal successful initialization
    zsock_signal (pipe, 0);

    while (!self->terminated) {
        zsock_t *which = (zsock_t *) zpoller_wait (self->poller, -1);
        if (which == self->pipe)
            s_self_handle_pipe (self);
        else
        if (zpoller_terminated (self->poller))
            break;          //  Interrupted
    }

    zstr_free(&(((_actor_data *) args)->ep));
    delete (_actor_data *) args;

    s_self_destroy (&self);
}


//  --------------------------------------------------------------------------
//  Selftest

void
mdp_titanic_test (bool verbose)
{
    printf (" * mdp_titanic: ");
    if (verbose)
        printf ("\n");

    //  @selftest
    zactor_t *xxx = zactor_new (mdp_titanic, NULL);
    assert (xxx);
    if (verbose)
        zstr_sendx (xxx, "VERBOSE", NULL);

    zactor_destroy (&xxx);
    //  @end
    printf ("OK\n");
}