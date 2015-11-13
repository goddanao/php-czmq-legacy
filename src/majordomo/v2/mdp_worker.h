#pragma once

#include "../../common.h"

class MajordomoWorkerV2 : public ZHandle, public Php::Base  {
private:
    std::string _name;
    std::string _broker_endpoint;
    Php::Value _callback;

public:

    MajordomoWorkerV2() : ZHandle(), Php::Base() {};
    MajordomoWorkerV2(mdp_worker_t *handle, bool owned) : ZHandle(handle, owned, "mdp_worker_v2"), Php::Base() {}
    mdp_worker_t *mdpworker_handle() const { return (mdp_worker_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        _name = param[0].stringValue();
        _broker_endpoint = param[1].stringValue();
        _callback = param[2];
        set_handle(mdp_worker_new(_broker_endpoint.c_str(), _name.c_str()), true, "mdp_worker_v2");
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
            zmsg_t *zmsg = zmsg_new();
            std::string result_str = result.stringValue();
            zmsg_pushstr(zmsg, result_str.c_str());

            // zsys_info("returning result : %s", result_str.c_str());
            mdp_worker_send_final(mdpworker_handle(), &address, &zmsg);
            zstr_free(&command);
            return true;
        }
        return false;
    }

    void run() {
        while(process().boolValue()) ;
    }

    static Php::Class<MajordomoWorkerV2> php_register() {
        Php::Class<MajordomoWorkerV2> o("Worker");
        o.method("__construct", &MajordomoWorkerV2::__construct, {
            Php::ByVal("name", Php::Type::String, true),
            Php::ByVal("broker_endpoint", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true)
        });
        o.method("set_verbose", &MajordomoWorkerV2::set_verbose);
        o.method("run", &MajordomoWorkerV2::run);
        o.method("process", &MajordomoWorkerV2::process);
        return o;
    }

};
