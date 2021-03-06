#pragma once

#include <phpcpp.h>
#include <czmq.h>
#include <zyre.h>
#include <majordomo.h>
#include <filemq.h>

#if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))

    #include <malamute.h>

#endif


class ZHandle {
protected:
    int _created_by_pid = -1;
    void *_handle       = nullptr;
    int _fd             = -1;
    bool _owned         = false;
    std::string _type   = "unknown";

    virtual Php::Value emptyFn() { return nullptr; }

public:
    ZHandle() { _created_by_pid = getpid(); }
    ZHandle(void *handle, bool owned, std::string type) : _handle(handle), _owned(owned), _type(type) { _created_by_pid = getpid(); }
    ZHandle(int fd, bool owned, std::string type) : _fd(fd), _owned(owned), _type(type) { _created_by_pid = getpid(); }

    void set_handle(void *handle, bool owned, std::string type) { _handle = handle; _owned = owned; _type  = type; }
    void set_handle(int fd, bool owned, std::string type) { _fd = fd; _owned = owned; _type  = type; }

    void *get_handle() const { return _handle; }

    void *get_actor() const {

        if(_type == "zactor")
            return _handle;

        if(_type == "fmq_server")
            return _handle;
        if(_type == "fmq_client")
            return fmq_client_actor ((fmq_client_t *) _handle);

        if(_type == "mdp_broker_v2")
            return _handle;
        if(_type == "mdp_worker_v2")
            return (void *) mdp_worker_actor ((mdp_worker_t *) _handle);
        if(_type == "mdp_client_v2")
            return (void *) mdp_client_actor ((mdp_client_t *) _handle);


#ifdef MALAMUTE_VERSION_MAJOR
        if(_type == "mlm_broker")
            return _handle;
        if(_type == "mlm_client")
            return (void *) mlm_client_actor((mlm_client_t *) _handle);
#endif

        if(_type == "zyre")
                return _handle;

        return nullptr;
    }

    Php::Value get_fd() const {
        if(_type == "zudp")
            return _fd;
        if(_type == "fd")
            return _fd;
        return zsock_fd(get_socket());
    }

    Php::Value _get_socket();

    void *get_socket() const {
        if(_type == "socket")
            return _handle;

        if(_type == "zsock")
            return zsock_resolve(_handle);
        if(_type == "zactor")
            return (void *) zsock_resolve(_handle);

        if(_type == "fmq_server")
            return (void *) zsock_resolve(_handle);
        if(_type == "fmq_client")
             return zsock_resolve(fmq_client_msgpipe((fmq_client_t *) _handle));

        if(_type == "mdp_broker_v2")
            return (void *) zsock_resolve(_handle);
        if(_type == "mdp_worker_v2")
            return (void *) zsock_resolve(mdp_worker_msgpipe((mdp_worker_t *) _handle));
        if(_type == "mdp_client_v2")
            return (void *) zsock_resolve(mdp_client_msgpipe((mdp_client_t *) _handle));

#if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))
        if(_type == "mlm_broker")
            return (void *) zsock_resolve(_handle);
        if(_type == "mlm_client")
            return (void *) zsock_resolve(mlm_client_msgpipe((mlm_client_t *) _handle));
#endif
        if(_type == "zyre")
            return (void *) zsock_resolve(zyre_socket((zyre_t*)_handle));

        return nullptr;
    }

    virtual ~ZHandle() {

        if(!_owned || _handle == nullptr || _handle == NULL || _created_by_pid != getpid())
            return;

        // zsys_info("destroying %s .... PID: %d", _type.c_str(), _created_by_pid);

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
            zsys_udp_close( _fd );
        else
        if(_type == "zyre")
            zyre_destroy((zyre_t **) &_handle);
        else
        if(_type == "zpoller")
            zpoller_destroy((zpoller_t **) &_handle);
        else

    #if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))

        if((_type == "mlm_broker") && zactor_is(_handle))
            zactor_destroy((zactor_t **) &_handle);
        else
        if(_type == "mlm_client")
            mlm_client_destroy ((mlm_client_t **) &_handle);
        else

    #endif

        if(_type == "mdp_broker_v2" && zactor_is(_handle))
            zactor_destroy((zactor_t **) &_handle);
        else
        if(_type == "mdp_worker_v2")
            mdp_worker_destroy ((mdp_worker_t **) &_handle);
        else
        if(_type == "mdp_client_v2")
            mdp_client_destroy ((mdp_client_t **) &_handle);
        else
        if(_type == "fmq_server")
             zactor_destroy((zactor_t **) &_handle);
        else
        if(_type == "fmq_client")
              fmq_client_destroy((fmq_client_t **) &_handle);
        else
        if(_type == "fd")
            close(_fd);

        _handle = nullptr;
        _fd = -1;
    }

    virtual bool _send(zmsg_t *msg) {
        return (zmsg_send (&msg, get_socket()) == 0);
    }

    virtual zmsg_t *_recv() {
        return zmsg_recv (get_socket());
    }

    virtual Php::Value recv_bson(Php::Parameters &param);

    virtual Php::Value send_bson(Php::Parameters &param);

    virtual Php::Value recv_zipped(Php::Parameters &param);

    virtual Php::Value send_zipped(Php::Parameters &param);

    virtual Php::Value recv_msgpack(Php::Parameters &param);

    virtual Php::Value send_msgpack(Php::Parameters &param);

    virtual Php::Value send_picture(Php::Parameters &param);

    virtual Php::Value recv_picture(Php::Parameters &param);

    virtual Php::Value send_string(Php::Parameters &param);

    virtual Php::Value recv_string(Php::Parameters &param);

    virtual Php::Value send(Php::Parameters &param);

    virtual Php::Value recv(Php::Parameters &param);

    template<class T>
    static void register_intf(std::vector<std::string> intfs, Php::Class<T> *o) {
        if(std::find(intfs.begin(), intfs.end(), "send") != intfs.end())
            register_send(o);
        if(std::find(intfs.begin(), intfs.end(), "recv") != intfs.end())
            register_recv(o);
        if(std::find(intfs.begin(), intfs.end(), "config") != intfs.end())
            register_config(o);
        if(std::find(intfs.begin(), intfs.end(), "izdescriptor") != intfs.end())
            register_izdescriptor(o);
        if(std::find(intfs.begin(), intfs.end(), "izsocket") != intfs.end())
            register_izsocket(o);
        if(std::find(intfs.begin(), intfs.end(), "izemitter") != intfs.end())
            register_izemitter(o);
    }

    template<class T>
    static void register_send(Php::Class<T> *o) {
        o->method("send", &T::send, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o->method("send_string", &T::send_string, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o->method("send_picture", &T::send_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });
        o->method("send_msgpack", &T::send_msgpack, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o->method("send_zipped", &T::send_zipped, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o->method("send_bson", &T::send_bson, {
            Php::ByVal("data", Php::Type::String, true)
        });
    }

    template<class T>
    static void register_recv(Php::Class<T> *o) {
        o->method("recv", &T::recv);
        o->method("recv_string", &T::recv_string);
        o->method("recv_picture", &T::recv_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });
        o->method("recv_msgpack", &T::recv_msgpack);
        o->method("recv_zipped", &T::recv_zipped);
        o->method("recv_bson", &T::recv_bson);
    }

    template<class T>
    static void register_config(Php::Class<T> *o) {
        o->method("load_config", &T::load_config, {
            Php::ByVal("filename", Php::Type::String, true)
        });
        o->method("save_config", &T::save_config, {
            Php::ByVal("filename", Php::Type::String, true)
        });
        o->method("set_config", &T::set_config, {
            Php::ByVal("key", Php::Type::String, true),
            Php::ByVal("value", Php::Type::String, true)
        });
    }

    template<class T>
    static void register_izdescriptor(Php::Class<T> *o) {
        o->method("get_fd", &T::get_fd);
    }

    template<class T>
    static void register_izsocket(Php::Class<T> *o) {
        o->method("get_fd", &T::get_fd);
        o->method("get_socket", &T::_get_socket);
    }

    template<class T>
    static void register_izactor(Php::Class<T> *o) {
        o->method("get_fd", &T::get_fd);
        o->method("get_socket", &T::_get_socket);
        o->method("start", &T::start);
        o->method("run", &T::run);
    }

    template<class T>
    static void register_izemitter(Php::Class<T> *o) {
        o->method("on", &T::on, {
            Php::ByVal("event", Php::Type::String, true),
            Php::ByVal("listener", Php::Type::Callable, true)
        });
        o->method("once", &T::once, {
            Php::ByVal("event", Php::Type::String, true),
            Php::ByVal("listener", Php::Type::Callable, true)
        });
        o->method("remove_listener", &T::remove_listener, {
            Php::ByVal("event", Php::Type::String, true),
            Php::ByVal("listener", Php::Type::Callable, true)
        });
        o->method("remove_all_listeners", &T::remove_all_listeners, {
            Php::ByVal("event", Php::Type::String, false)
        });
        o->method("listeners", &T::listeners, {
            Php::ByVal("event", Php::Type::String, true)
        });
        o->method("emit", &T::emit, {
            Php::ByVal("event", Php::Type::String, true),
            Php::ByVal("arguments", Php::Type::Array, true)
        });
    }

};
