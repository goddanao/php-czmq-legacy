#pragma once

#include "../common.h"

class MajordomoWorkerV2 : public ZActor, public Php::Base  {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        mdp_worker_t *worker = mdp_worker_new(param[1].stringValue().c_str(), param[0].stringValue().c_str());
        if(poller)
            zpoller_add(poller, mdp_worker_msgpipe(worker));
        return worker;
    }

public:

    MajordomoWorkerV2() : ZActor(&MajordomoWorkerV2::new_actor), Php::Base() { _type = "mdp_worker_v2"; };
    mdp_worker_t *mdpworker_handle() const { return (mdp_worker_t *) get_handle(); }

    void set_verbose() {
        mdp_worker_set_verbose(mdpworker_handle());
    }

//    Php::Value process() {
//        char *command;
//        zframe_t *address;
//        zmsg_t *body;
//        int rc = zsock_recv(mdp_worker_msgpipe(mdpworker_handle()), "sfm", &command, &address, &body);
//        if(rc == 0) {
//            Php::Value result = _callback(Php::Object("ZMsg", new ZMsg(body, true)));
//            zmsg_t *zmsg = ZUtils::phpvalue_to_zmsg(result);
//            mdp_worker_send_final(mdpworker_handle(), &address, &zmsg);
//            zstr_free(&command);
//            return true;
//        }
//        return false;
//    }

    static void run(Php::Parameters &param) {
        _run(&MajordomoWorkerV2::new_actor,
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
                zmsg_t *zmsg = ZUtils::phpvalue_to_zmsg(result);
                mdp_worker_send_final((mdp_worker_t*) actor, &address, &zmsg);
            }
        },
        param);
    }

//    static void run(Php::Parameters &param) {
//
//
//        std::string _name = param[0].stringValue();
//        std::string _broker_endpoint = param[1].stringValue();
//
//        mdp_worker_t *worker = new_worker(_name, _broker_endpoint);
//        zclock_sleep(100);
//
//        zpoller_t *poller = zpoller_new(mdp_worker_msgpipe(worker));
//
//        while (!zsys_interrupted) {
//            void *socket = zpoller_wait(poller, -1);
//            if(zpoller_terminated(poller)) {
//                break;
//            }
//            if(socket == mdp_worker_msgpipe(worker)) {
//                char *command;
//                zframe_t *address;
//                zmsg_t *body;
//                int rc = zsock_recv(socket, "sfm", &command, &address, &body);
//                if(rc == 0) {
//                    Php::Value result = param[2](Php::Object("ZMsg", new ZMsg(body, true)));
//                    zmsg_t *zmsg = ZUtils::phpvalue_to_zmsg(result);
//                    mdp_worker_send_final(worker, &address, &zmsg);
//                    zstr_free(&command);
//                }
//            }
//        }
//        zpoller_destroy(&poller);
//        mdp_worker_destroy(&worker);
//    }

    static Php::Class<MajordomoWorkerV2> php_register() {
        Php::Class<MajordomoWorkerV2> o("Worker");
        o.method("__construct", &MajordomoWorkerV2::__construct, {
            Php::ByVal("name", Php::Type::String, true),
            Php::ByVal("broker_endpoint", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true)
        });
        o.method("set_verbose", &MajordomoWorkerV2::set_verbose);
        o.method("run", &MajordomoWorkerV2::run, {
            Php::ByVal("name", Php::Type::String, true),
            Php::ByVal("broker_endpoint", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true)
        });
//        o.method("process", &MajordomoWorkerV2::process);

        // IZSocket intf support
        o.method("get_fd", &MajordomoWorkerV2::get_fd);
        o.method("get_socket", &MajordomoWorkerV2::_get_socket);

        return o;
    }

};
