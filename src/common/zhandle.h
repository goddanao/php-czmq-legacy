#pragma once

#include <phpcpp.h>
#include <czmq.h>
#include <zyre.h>
#include <majordomo.h>
#include <malamute.h>
#include <filemq.h>

class ZHandle {
protected:
    void *_handle      = nullptr;
    SOCKET _socket     = 0;
    bool _owned        = false;
    std::string _type  = "unknown";
public:
    ZHandle() {}
    ZHandle(void *handle, bool owned, std::string type) : _handle(handle), _owned(owned), _type(type) {}
    ZHandle(SOCKET socket, bool owned, std::string type) : _socket(socket), _owned(owned), _type(type) {}

    void set_handle(void *handle, bool owned, std::string type) { _handle = handle; _owned = owned; _type  = type; }
    void set_handle(SOCKET socket, bool owned, std::string type) { _socket = socket; _owned = owned; _type  = type; }

    void *get_handle() const { return _handle; }

    virtual void *get_actor() const {

        if(_type == "zactor")
            return _handle;

        if(_type == "fmq_broker")
            return _handle;
        if(_type == "fmq_client")
            return fmq_client_actor ((fmq_client_t *) _handle);

        if(_type == "mdp_broker_v2")
            return _handle;
        if(_type == "mdp_worker_v2")
            return (void *) mdp_worker_actor ((mdp_worker_t *) _handle);
        if(_type == "mdp_client_v2")
            return (void *) mdp_client_actor ((mdp_client_t *) _handle);

        if(_type == "mdp_broker_vX")
            return _handle;

        if(_type == "mlm_broker")
            return _handle;
        if(_type == "mlm_client")
            return (void *) mlm_client_actor((mlm_client_t *) _handle);

        if(_type == "zyre")
                return _handle;

        return nullptr;
    }

    virtual SOCKET get_fd() const {
        if(_type == "zudp")
            return _socket;
        return zsock_fd(get_socket());
    }

    Php::Value _get_fd () const;
    Php::Value _get_socket () const;

    virtual void *get_socket() const {
        if(_type == "socket")
            return _handle;

        if(_type == "zsock")
            return zsock_resolve(_handle);
        if(_type == "zactor")
            return (void *) zsock_resolve(_handle);

        if(_type == "fmq_broker")
            return (void *) zsock_resolve(_handle);
        if(_type == "fmq_client")
             return fmq_client_msgpipe((fmq_client_t *) _handle);

        if(_type == "mdp_broker_v2")
            return (void *) zsock_resolve(_handle);
        if(_type == "mdp_worker_v2")
            return (void *) mdp_worker_msgpipe((mdp_worker_t *) _handle);
        if(_type == "mdp_client_v2")
            return (void *) mdp_client_msgpipe((mdp_client_t *) _handle);

        if(_type == "mdp_broker_vX")
            return (void *) zsock_resolve(_handle);
        if(_type == "mdp_worker_vX")
            return (void *) _handle;
        if(_type == "mdp_client_vX")
            return (void *) _handle;

        if(_type == "mlm_broker")
            return (void *) zsock_resolve(_handle);
        if(_type == "mlm_client")
            return (void *) mlm_client_msgpipe((mlm_client_t *) _handle);

        if(_type == "zyre")
            return (void *) zyre_socket((zyre_t*)_handle);

        return nullptr;
    }

    virtual ~ZHandle() {

        if(!_owned || _handle == nullptr || _handle == NULL)
            return;

        if(_type == "zactor" && zactor_is(_handle))
            zactor_destroy((zactor_t **) &_handle);
        else
        if(_type == "zsock" && zsock_is(_handle))
            zsock_destroy((zsock_t **) &_handle);
        else
        if(_type == "zsocket")
            zsys_close(_handle, NULL, 0);
        else
        if(_type == "zcert")
            zcert_destroy((zcert_t **) &_handle);
        else
        if(_type == "zframe" && zframe_is(_handle))
            zframe_destroy((zframe_t **) &_handle);
        else
        if(_type == "zmsg" && zmsg_is(_handle))
            zmsg_destroy((zmsg_t **) &_handle);
        else
        if(_type == "zhash")
            zhash_destroy((zhash_t **) &_handle);
        else
        if(_type == "zchunk" && zchunk_is(_handle))
            zchunk_destroy((zchunk_t **) &_handle);
        else
        if(_type == "zcertstore")
            zcertstore_destroy((zcertstore_t **) &_handle);
        else
        if(_type == "zloop")
            zloop_destroy((zloop_t **) &_handle);
        else
        if(_type == "zudp")
            zsys_udp_close( _socket );
        else
        if(_type == "zyre")
            zyre_destroy((zyre_t **) &_handle);
        else
        if(_type == "zpoller")
            zpoller_destroy((zpoller_t **) &_handle);
        else
        if(_type == "mlm_broker" && zactor_is(_handle))
            zactor_destroy((zactor_t **) &_handle);
        else
        if(_type == "mlm_client")
            mlm_client_destroy ((mlm_client_t **) &_handle);
        else
        if(_type == "mdp_broker_v2" && zactor_is(_handle))
            zactor_destroy((zactor_t **) &_handle);
        else
        if(_type == "mdp_worker_v2")
            mdp_worker_destroy ((mdp_worker_t **) &_handle);
        else
        if(_type == "mdp_client_v2")
            mdp_client_destroy ((mdp_client_t **) &_handle);
        else
        if(_type == "mdp_broker_vX" && zactor_is(_handle))
            zactor_destroy((zactor_t **) &_handle);
        else
        if(_type == "mdp_worker_vX" && zsock_is(_handle))
            zsock_destroy((zsock_t **) &_handle);
        else
        if(_type == "mdp_client_vX" && zsock_is(_handle))
            zsock_destroy((zsock_t **) &_handle);
        else
        if(_type == "fmq_broker")
             zactor_destroy((zactor_t **) &_handle);
         else
         if(_type == "fmq_client")
              fmq_client_destroy((fmq_client_t **) &_handle);
          else
          ;


        _handle = nullptr;
        _socket = INVALID_SOCKET;
    }

};
