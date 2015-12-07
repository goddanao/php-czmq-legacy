#pragma once

#include "titanic/mdp_titanic_storage_fs.h"
#include "titanic/mdp_titanic_storage_php.h"
#include "titanic/mdp_titanic_request.h"
#include "titanic/mdp_titanic_reply.h"
#include "titanic/mdp_titanic_close.h"
#include "titanic/mdp_titanic_process.h"

class MajordomoTitanicV2 : public ZHandle, public Php::Base  {
private:
    std::string _broker_endpoint;
    std::vector<zactor_t *> _actors;
    std::vector<mdp_client_t *> _clients;
    TitanicStorage *storage;
    zactor_t *process;

    _actor_data *actor_data_new(Php::Parameters &param) {
        _actor_data *data = new _actor_data();
        data->ep = _broker_endpoint.c_str();
        data->st = [param](){
            if(param.size()>1 && param[1].isObject() && !param[1].isNull()) {
                return (TitanicStorage*) new PhpCallbackStorage(param[1]);
            } else {
                return (TitanicStorage*) new FileSystemStorage();
            }
        };
        return data;
    }

public:

    MajordomoTitanicV2() : ZHandle(), Php::Base() {};

    void __construct(Php::Parameters &param) {
        _broker_endpoint = param[0].stringValue();

        int _threads = param.size()>2 ? param[2].numericValue() : 1;

        process = zactor_new(zmdp_titanic_process, (void*) actor_data_new(param));

        while(_threads > 0) {
            _actors.push_back(zactor_new(zmdp_titanic_request, (void*) actor_data_new(param)));
            _actors.push_back(zactor_new(zmdp_titanic_reply, (void*) actor_data_new(param)));
            _actors.push_back(zactor_new(zmdp_titanic_close, (void*) actor_data_new(param)));
            _threads--;
        }
    }

    virtual ~MajordomoTitanicV2(){
        for(auto it = _actors.begin() ; it < _actors.end(); it++)
            zactor_destroy(&(*it));
        if(storage)
            delete storage;
        zactor_destroy(&process);
    }

    void run(void) {

        zpoller_t *poller = zpoller_new(NULL);
        for(auto it = _actors.begin() ; it < _actors.end(); it++)
            zpoller_add(poller, *it);

        while (!zsys_interrupted) {
            void *socket = zpoller_wait(poller, 1000);
            if(zpoller_terminated(poller)) {
                zpoller_destroy(&poller);
                break;
            }
        }

        zpoller_destroy(&poller);
    }

    static Php::Class<MajordomoTitanicV2> php_register() {
        Php::Class<MajordomoTitanicV2> o("Titanic");
        o.method("__construct", &MajordomoTitanicV2::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("storage", "Majordomo\\ITitanicStorage", true, false),
            Php::ByVal("threads", Php::Type::Numeric, false)
        });
        o.method("run", &MajordomoTitanicV2::run);

        // IZSocket intf support
        o.method("get_fd", &MajordomoWorkerV2::get_fd);
        o.method("get_socket", &MajordomoWorkerV2::_get_socket);

        return o;
    }

};
