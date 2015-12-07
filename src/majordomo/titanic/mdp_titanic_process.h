#pragma once

#include "mdp_titanic_common.h"

static void zmdp_titanic_process(zsock_t *pipe, void *args) {

    _actor_data *data = (_actor_data *)(args);
    TitanicStorage *storage = data->st();
    char *ep = (char *) data->ep;

    zpoller_t *poller = zpoller_new(pipe, NULL);
    zmsg_t *reply = NULL;

    zsock_signal (pipe, 0);

    while (!zsys_interrupted) {
       zsock_t *socket = (zsock_t *) zpoller_wait(poller, 1000);
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

        // Send next request if available
        char *process = storage->process();
        if(process != nullptr) {
            int result = s_service_success(process, ep, storage);
            zstr_free(&process);
        }

    }

    delete storage;
    zpoller_destroy(&poller);
}