#pragma once

#include "../common.h"

class MajordomoWorkerV2 : public ZActor, public Php::Base  {
private:
    zframe_t *address = nullptr; // Address to respond at

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        mdp_worker_t *worker = mdp_worker_new(param[1].stringValue().c_str(), param[0].stringValue().c_str());
        if(poller)
            zpoller_add(poller, mdp_worker_msgpipe(worker));
        return worker;
    }

public:

    MajordomoWorkerV2() : ZActor("mdp_worker_v2", &MajordomoWorkerV2::new_actor), Php::Base() { };
    mdp_worker_t *mdpworker_handle() const { return (mdp_worker_t *) get_handle(); }

    void set_verbose() {
        mdp_worker_set_verbose(mdpworker_handle());
    }

    bool _send(zmsg_t *msg) override {
        bool success = mdp_worker_send_final(mdpworker_handle(), &address, &msg) == 0;
        address = nullptr;
        return success;
    }

    zmsg_t *_recv() override {
        char *command;
        zmsg_t *body;
        if(address != nullptr) {
            zframe_destroy(&address);
            address = nullptr;
        }

        int rc = zsock_recv(zsock_resolve(mdp_worker_msgpipe(mdpworker_handle())), "sfm", &command, &address, &body);
        if(rc == 0) {
            zstr_free(&command);
            return body;
        }
        return nullptr;
    }

    static void run(Php::Parameters &param) {
        _run(param, &MajordomoWorkerV2::new_actor,
        [](void *actor){
            mdp_worker_destroy((mdp_worker_t **) &actor);
        },
        [param](void *actor, void *socket){
            char *command;
            zframe_t *address;
            zmsg_t *body;
            int rc = zsock_recv(socket, "sfm", &command, &address, &body);
            if(rc == 0) {
                zstr_free(&command);
                Php::Value result = param[2](Php::Object("ZMsg", new ZMsg(body, true)));
                if(result.isBool() && !result.boolValue())
                    return false;
                zmsg_t *zmsg = ZUtils::phpvalue_to_zmsg(result);
                if(mdp_worker_send_final((mdp_worker_t*) actor, &address, &zmsg) != 0)
                    return false;
            }
            return true;
        });
    }

    static Php::Class<MajordomoWorkerV2> php_register() {
        Php::Class<MajordomoWorkerV2> o("Worker");
        o.method("__construct", &MajordomoWorkerV2::__construct, {
            Php::ByVal("name", Php::Type::String, true),
            Php::ByVal("broker_endpoint", Php::Type::String, true)
        });
        o.method("set_verbose", &MajordomoWorkerV2::set_verbose);

        // ZEmitter
        ZHandle::register_izemitter((Php::Class<MajordomoWorkerV2> *) &o);

        // Send / Recv
        ZHandle::register_recv((Php::Class<MajordomoWorkerV2> *) &o);
        ZHandle::register_send((Php::Class<MajordomoWorkerV2> *) &o);

        // IZActor intf support
        ZHandle::register_izactor((Php::Class<MajordomoWorkerV2> *) &o);

//        o.method("run", &MajordomoWorkerV2::run, {
//            Php::ByVal("name", Php::Type::String, true),
//            Php::ByVal("broker_endpoint", Php::Type::String, true),
//            Php::ByVal("callback", Php::Type::Callable, true)
//        });

        return o;
    }

};
