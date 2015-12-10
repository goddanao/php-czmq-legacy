#pragma once

#include "../common.h"

class MajordomoWorkerV2 : public ZHandle, public Php::Base  {
private:
    std::string _name;
    std::string _broker_endpoint;
    Php::Value _callback;

    static mdp_worker_t *new_worker(std::string name, std::string endpoint) {
        return mdp_worker_new(endpoint.c_str(), name.c_str());
    }

public:

    MajordomoWorkerV2() : ZHandle(), Php::Base() {};
    MajordomoWorkerV2(mdp_worker_t *handle, bool owned) : ZHandle(handle, owned, "mdp_worker_v2"), Php::Base() {}
    mdp_worker_t *mdpworker_handle() const { return (mdp_worker_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        _name = param[0].stringValue();
        _broker_endpoint = param[1].stringValue();
        _callback = param[2];
        set_handle(new_worker(_name, _broker_endpoint), true, "mdp_worker_v2");
    }

    void set_verbose() {
        mdp_worker_set_verbose(mdpworker_handle());
    }

    Php::Value process() {
        char *command;
        zframe_t *address;
        zmsg_t *body;
        int rc = zsock_recv(mdp_worker_msgpipe(mdpworker_handle()), "sfm", &command, &address, &body);
        if(rc == 0) {
            Php::Value result = _callback(Php::Object("ZMsg", new ZMsg(body, true)));
            zmsg_t *zmsg = ZUtils::phpvalue_to_zmsg(result);
            mdp_worker_send_final(mdpworker_handle(), &address, &zmsg);
            zstr_free(&command);
            return true;
        }
        return false;
    }


    static void run(Php::Parameters &param) {
        std::string _name = param[0].stringValue();
        std::string _broker_endpoint = param[1].stringValue();

        mdp_worker_t *worker = new_worker(_name, _broker_endpoint);
        zclock_sleep(100);

        zpoller_t *poller = zpoller_new(mdp_worker_msgpipe(worker));

        while (!zsys_interrupted) {
            void *socket = zpoller_wait(poller, -1);
            if(zpoller_terminated(poller)) {
                break;
            }
            if(socket == mdp_worker_msgpipe(worker)) {
                char *command;
                zframe_t *address;
                zmsg_t *body;
                int rc = zsock_recv(socket, "sfm", &command, &address, &body);
                if(rc == 0) {
                    Php::Value result = param[2](Php::Object("ZMsg", new ZMsg(body, true)));
                    zmsg_t *zmsg = ZUtils::phpvalue_to_zmsg(result);
                    mdp_worker_send_final(worker, &address, &zmsg);
                    zstr_free(&command);
                }
            }
        }
        zpoller_destroy(&poller);
        mdp_worker_destroy(&worker);
    }

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
        o.method("process", &MajordomoWorkerV2::process);

        // IZSocket intf support
        o.method("get_fd", &MajordomoWorkerV2::get_fd);
        o.method("get_socket", &MajordomoWorkerV2::_get_socket);

        return o;
    }

};
