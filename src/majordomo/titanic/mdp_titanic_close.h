#pragma once

#include "mdp_titanic_common.h"

static void zmdp_titanic_close(zsock_t *pipe, void *args) {

    _actor_data *data = (_actor_data *)(args);
    TitanicStorage *storage = data->st();
    char *ep = (char *) data->ep;

    mdp_worker_t *worker = mdp_worker_new (ep,  "titanic.close");
    zpoller_t *poller = zpoller_new(pipe, mdp_worker_msgpipe(worker), NULL);
    zmsg_t *reply = NULL;

    zsock_signal (pipe, 0);

    while (!zsys_interrupted) {
       zsock_t *socket = (zsock_t *) zpoller_wait(poller, -1);

       if(socket == mdp_worker_msgpipe(worker)) {
            zmsg_t *request = mdwrk_recv (worker, NULL);
            zframe_t *address = zmsg_pop(request);
            char *uuid = zmsg_popstr (request);
            storage->close(uuid);

            reply = zmsg_new ();
            zmsg_addstr (reply, "200");
            zmsg_addstr (reply, uuid);
            mdp_worker_send_final(worker, &address, &reply);

            zmsg_destroy (&request);
        }
        else
        if(socket == pipe) {
            bool exit = false;
            zmsg_t *msg;
            zsock_recv(pipe, "m", &msg);
            char *command = zmsg_popstr(msg);

            if(streq(command, "$TERM")) {
                exit = true;
            }

            if(command)
                zstr_free(&command);

            if(exit)
                break;

        }
        else
        if(zpoller_terminated(poller))
            break;
    }

    delete storage;
    zpoller_destroy(&poller);
    mdp_worker_destroy (&worker);
}