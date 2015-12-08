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
    std::map<zactor_t *, _actor_data *> _actors;

    _actor_data *actor_data_new(Php::Parameters &param) {
        _actor_data *data = new _actor_data;
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

        _actor_data *ad = actor_data_new(param);
        _actors.insert({zactor_new(zmdp_titanic_process, (void*) ad), ad});

        while(_threads > 0) {
            ad = actor_data_new(param);
            _actors.insert({zactor_new(zmdp_titanic_request, (void*) ad), ad});
            ad = actor_data_new(param);
            _actors.insert({zactor_new(zmdp_titanic_reply, (void*) ad), ad});
            ad = actor_data_new(param);
            _actors.insert({zactor_new(zmdp_titanic_close, (void*) ad), ad});
            _threads--;
        }
    }

    virtual ~MajordomoTitanicV2(){
        for (auto it = std::begin(_actors); it!=std::end(_actors); ++it) {
            zactor_destroy((_zactor_t**) &(it->first));
            delete (_actor_data *) it->second;
        }
    }

    void run(void) {

        zpoller_t *poller = zpoller_new(NULL);
        for (auto it = std::begin(_actors); it!=std::end(_actors); ++it)
            zpoller_add(poller, it->first);

        while (!zsys_interrupted) {
            void *socket = zpoller_wait(poller, -1);
            if(zpoller_terminated(poller)) {
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
