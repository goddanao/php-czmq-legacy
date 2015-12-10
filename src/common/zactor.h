#pragma once

#include "zhandle.h"

class ZActor : public ZHandle {
protected:
    std::function<void *(Php::Parameters &param, zpoller_t *)> _new;
    std::function<void (void *)> _destroy;
    std::function<void (void *, void *)> _poll;
public:

    ZActor(std::function<void *(Php::Parameters &param, zpoller_t *)> __new, std::function<void (void *)> __destroy = NULL, std::function<void (void *, void *)> __poll = NULL) : ZHandle(), _new(__new), _destroy(__destroy), _poll(__poll) { _type = "zactor"; }

    virtual void __construct(Php::Parameters &param) {
        set_handle(_new(param, NULL), true, (_type != "unknown") ? _type : "zactor");
    }

    static void _run(std::function<void *(Php::Parameters &param, zpoller_t *)> __new, std::function<void (void *)> __destroy, std::function<void (void *, void *)> __poll, Php::Parameters &param) {
        zpoller_t *poller = zpoller_new(NULL);
        void *actor = __new(param, poller);
        while (!zsys_interrupted) {
            void *socket = zpoller_wait(poller, -1);
            if(zpoller_terminated(poller)) {
                break;
            }
            if(socket)
                __poll(actor, socket);
        }
        zpoller_destroy(&poller);
        __destroy(actor);
    }

};