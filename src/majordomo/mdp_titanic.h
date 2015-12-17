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

    MajordomoTitanicV2() : ZActor(&MajordomoTitanicV2::new_actor), Php::Base() { };

    static void run(Php::Parameters &param) {
        _run(param, &MajordomoTitanicV2::new_actor);
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

        // ZEmitter
        o.method("start", &MajordomoTitanicV2::start);
        ZHandle::register_izemitter((Php::Class<MajordomoTitanicV2> *) &o);

        // Send / Recv
        ZHandle::register_recv((Php::Class<MajordomoTitanicV2> *) &o);
        ZHandle::register_send((Php::Class<MajordomoTitanicV2> *) &o);

        // IZSocket intf support
        ZHandle::register_izsocket((Php::Class<MajordomoTitanicV2> *) &o);

        return o;
    }

};
