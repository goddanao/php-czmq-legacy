#pragma once

#include "../../common.h"
#include "mdp_titanic_storage.h"

typedef struct {
    const char *ep;
    std::function<TitanicStorage*()> st;
} _actor_data;

static zmsg_t *mdcli_send(mdp_client_t *client, char *service, zmsg_t* msg) {
    int rc = mdp_client_request(client, service, &msg);
    if(rc == 0) {
        char *command;
        zmsg_t *body;
        rc = zsock_recv(mdp_client_msgpipe(client), "sm", &command, &body);
        if(command)
            zstr_free(&command);
        if(rc == 0)
            return body;
    }
    return nullptr;
}

static zmsg_t *mdwrk_recv(mdp_worker_t *worker, zmsg_t* reply) {
    if(reply != nullptr) {
        zframe_t *address = zmsg_pop(reply);
        mdp_worker_send_final(worker, &address, &reply);
    }
    char *command;
    zmsg_t *body;
    int rc = zsock_recv(mdp_worker_msgpipe(worker), "sm", &command, &body);
    if(rc == 0) {
        zstr_free(&command);
        return body;
    }
    return nullptr;
}

static char *s_generate_uuid (void) {
    zuuid_t *uuid = zuuid_new ();
    char *uuids = strdup(zuuid_str_canonical(uuid));
    zuuid_destroy(&uuid);
    return uuids;
}

static int s_service_success (char *uuid, const char *ep, TitanicStorage *storage) {

    const char *status = storage->status(uuid);
    if(streq(status, "200"))
        return 1;

    zmsg_t *request = storage->read_request(uuid);

    zframe_t *service = zmsg_pop (request);
    char *service_name = zframe_strdup (service);

    //  Create MDP client session with short timeout
    mdp_client_t *client = mdp_client_new (ep);
    // mdp_client_set_timeout (client, 1000);  //  1 sec
    // mdp_client_set_retries (client, 1);     //  only 1 retry

    zclock_sleep (200);

    //  Use MMI protocol to check if service is available
    int service_ok = 0;
    zmsg_t *mmi_request = zmsg_new ();
    zmsg_add (mmi_request, service);
    zmsg_t *mmi_reply = mdcli_send (client, "mmi.service", mmi_request);
    if(mmi_reply) {
        service_ok = (mmi_reply && zframe_streq (zmsg_first (mmi_reply), "200"));
        zmsg_destroy (&mmi_reply);
    }

    int result = 0;
    if (service_ok) {
        zmsg_t *reply = mdcli_send (client, service_name, request);
        if (reply) {
            storage->store_response(uuid, reply);
            zmsg_destroy (&reply);
            result = 1;
        }
    }
    else
        zmsg_destroy (&request);

    mdp_client_destroy (&client);
    zstr_free (&service_name);

    return result;
}