
#include "../common.h"
#include "../czmq/zmsg.h"

void ZActor::on_start() {
    emit("start", {});
}

void ZActor::on_end() {
    emit("end", {});
}

void ZActor::on_idle() {
    emit("idle", {});
}

void ZActor::on_data(zmsg_t *msg) {
    if(msg)
        emit("data", { Php::Object("ZMsg", new ZMsg(msg, false)) });
}

void ZActor::start(Php::Parameters &param) {
    zpoller_t *poller = zpoller_new(NULL);
    on_start();
    zpoller_add(poller, get_socket());
    while (!zsys_interrupted) {
        void *socket = zpoller_wait(poller, 1);
        if(socket) {
            zsys_info("got socket data");
            zmsg_t *msg = zmsg_recv(socket);
            if(msg) {
                on_data(msg);
                zmsg_destroy(&msg);
            } else
                break;
        }
        else
        if(zpoller_terminated(poller)) {
            break;
        }
        else
        if(zpoller_expired(poller)) {
            on_idle();
        }
        else
            break;

    }
    on_end();
    zpoller_destroy(&poller);
}