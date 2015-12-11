#pragma once

#include "titanic/mdp_titanic_actor.h"
#include "titanic/mdp_titanic_storage_fs.h"
#include "titanic/mdp_titanic_storage_php.h"

class MajordomoTitanicV2 : public ZActor, public Php::Base  {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {

        _actor_data *data = new _actor_data;
        data->threads = param.size()>2 ? param[2].numericValue() : 1;
        data->ep = strdup(param[0].stringValue().c_str());
        data->st = [param](){
            if(param.size()>1 && param[1].isObject() && !param[1].isNull()) {
                return (TitanicStorage*) new PhpCallbackStorage(param[1]);
            } else {
                return (TitanicStorage*) new FileSystemStorage();
            }
        };

        zactor_t *titanic = zactor_new(mdp_titanic, data);
        if(titanic) {
            if(poller)
                zpoller_add(poller, titanic);

            if(param.size()>1 && param[1].boolValue()) {
                zstr_sendx (titanic, "VERBOSE", NULL);
            }
            return titanic;
        }
        return nullptr;
    }

public:

    MajordomoTitanicV2() : ZActor(&MajordomoTitanicV2::new_actor), Php::Base() { _type = "zactor"; };

    static void run(Php::Parameters &param) {
        _run(
            &MajordomoTitanicV2::new_actor,
            [](void *actor){
                zactor_destroy((zactor_t **) &actor);
            },
            [param](void *actor, void *socket){

            },
        param);
    }

    static Php::Class<MajordomoTitanicV2> php_register() {
        Php::Class<MajordomoTitanicV2> o("Titanic");
        o.method("__construct", &MajordomoTitanicV2::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("storage", "Majordomo\\ITitanicStorage", true, false),
            Php::ByVal("threads", Php::Type::Numeric, false)
        });
        o.method("run", &MajordomoTitanicV2::run, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("storage", "Majordomo\\ITitanicStorage", true, false),
            Php::ByVal("threads", Php::Type::Numeric, false)
        });

        o.method("send", &MajordomoTitanicV2::send, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("recv", &MajordomoTitanicV2::recv);
        o.method("send_string", &MajordomoTitanicV2::send_string, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("recv_string", &MajordomoTitanicV2::recv_string);
        o.method("send_picture", &MajordomoTitanicV2::send_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });
        o.method("recv_picture", &MajordomoTitanicV2::recv_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });

        // IZSocket intf support
        o.method("get_fd", &MajordomoWorkerV2::get_fd);
        o.method("get_socket", &MajordomoWorkerV2::_get_socket);

        return o;
    }

};
