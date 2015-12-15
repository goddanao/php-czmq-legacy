#pragma once

#include "zhandle.h"

class ZActor : public ZHandle {
protected:
    std::function<void *(Php::Parameters &param, zpoller_t *)> _new;
    std::function<void (void *)> _destroy;
    std::function<bool (void *, void *)> _poll;
    std::function<bool (void *)> _expired;

    static void _run(Php::Parameters &param,
        std::function<void *(Php::Parameters &param, zpoller_t *)> __new,
        std::function<void (void *)> __destroy = NULL,
        std::function<bool (void *, void *)> __poll = NULL,
        std::function<bool (void *)> __expired = NULL) {
        zpoller_t *poller = zpoller_new(NULL);
        void *actor = __new(param, poller);
        while (!zsys_interrupted) {
            void *socket = zpoller_wait(poller, 1);
            if(zpoller_terminated(poller)) {
                break;
            }
            if(zpoller_expired(poller)) {
                if(__expired && !__expired(actor))
                    break;
            }
            if(socket) {
                if(__poll) {
                    if(!__poll(actor, socket))
                        break;
                } else {
                    zmsg_t *msg = zmsg_recv(socket);
                    if(!msg) break;
                    zsys_info("msg incoming");
                    zmsg_dump(msg);
                    zmsg_destroy(&msg);
                }
            }
        }
        zpoller_destroy(&poller);

        if(__destroy) {
            __destroy(actor);
        } else {
            if(zactor_is(actor)){
                zactor_destroy((zactor_t **) &actor);
            }
        }
    }

public:

    ZActor(
        std::function<void *(Php::Parameters &param, zpoller_t *)> __new,
        std::function<void (void *)> __destroy = NULL,
        std::function<bool (void *, void *)> __poll = NULL,
        std::function<bool (void *)> __expired = NULL) : ZHandle(), _new(__new), _destroy(__destroy), _poll(__poll), _expired(__expired) { _type = "zactor"; }

    ZActor(void *handle, bool owned,
        std::function<void *(Php::Parameters &param, zpoller_t *)> __new,
        std::function<void (void *)> __destroy = NULL,
        std::function<bool (void *, void *)> __poll = NULL,
        std::function<bool (void *)> __expired = NULL
        ) : ZHandle(handle, owned, "zactor"), _new(__new), _destroy(__destroy), _poll(__poll), _expired(__expired) { _type = "zactor"; }

    virtual void __construct(Php::Parameters &param) {
        set_handle(_new(param, NULL), true, (_type != "unknown") ? _type : "zactor");
    }

};