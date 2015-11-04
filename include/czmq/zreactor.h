#pragma once

#include <phpcpp.h>
#include <iostream>
#include <czmq.h>
#include "zpoll.h"
#include "../common.h"

class ZReactor : public Php::Base {
private:
    bool _verbose       = false;
    bool _dispatching   = false;

    Php::Object _poller; // will hold ZPollerEx _poller;
    std::map<ZHandle *, Php::Value> _objects;
    std::map<ZHandle *, Php::Value> _callbacks;
    std::vector<ZHandle *> _objectsRemoveLater;

    void flush_remove_later() {
        for (const ZHandle *sock : _objectsRemoveLater)
            _remove((ZHandle *) sock);
        _objectsRemoveLater.clear();
    }

    void _remove(ZHandle *to_remove) {
        if (_dispatching){
            _objectsRemoveLater.push_back(to_remove);
            return;
        }
        _poller.call("remove", _objects[to_remove]);
        _objects.erase(to_remove);
        _callbacks.erase(to_remove);
    }

public:


    void __construct(Php::Parameters &param) {
        _poller = Php::Object("ZPoll", new ZPoll());
    }

    void set_verbose(Php::Parameters &param) {
        _verbose = param.size()>0 ? (bool) param[0] : true;
    }

    void add(Php::Parameters &param) {
        if(param.size() < 2 || !param[0].isObject() || !param[1].isCallable())
            throw Php::Exception("ZReactor add require a ZActor, ZSocker or ZHandle and a callback.");

        if(_verbose)
            zsys_info("Adding socket ...");

        _poller.call("add", param[0], (param.size()>2 ? (int) param[2] : (int) ZMQ_POLLIN));

        if(_verbose)
            zsys_info("Added socket ...");

        ZHandle *zh = dynamic_cast<ZHandle *> (param[0].implementation());
        _objects.insert((std::pair<ZHandle *, Php::Value>) {zh, param[0]});
        _callbacks.insert((std::pair<ZHandle *, Php::Value>) {zh, param[1]});

        if(_verbose)
            zsys_info("Inserted socket ...");
    }

    Php::Value has(Php::Parameters &param) {
        if(param.size() == 0 || !param[0].isObject())
            throw Php::Exception("ZReactor has require a ZActor, ZSocker or ZHandle");
        return _poller.call("has", param[0]);
    }

    void remove(Php::Parameters &param) {
        if(param.size() == 0 || !param[0].isObject())
            throw Php::Exception("ZReactor remove require a ZActor, ZSocker or ZHandle");
        _remove(dynamic_cast<ZHandle *> (param[0].implementation()));
    }

    void check_for(Php::Parameters &param) {
        if(param.size() < 2 || !param[0].isObject())
            throw Php::Exception("ZReactor check_for require a ZActor, ZSocker or ZHandle");

        _poller.call("check_for", param[0], param[1]);
    }

    Php::Value events(Php::Parameters &param) {
        if(param.size() == 0 || !param[0].isObject())
            throw Php::Exception("ZReactor events require a ZActor, ZSocker or ZHandle");
        return _poller.call("events", param[0]);
    }

    Php::Value poll(Php::Parameters &param) {
        long timeout = (param.size()>0) ? (long) param[0] : -1; // -1 = WAIT_FOREVER
        if(_poller.call("poll", timeout)) {
            _dispatching = true;
            std::map<ZHandle *, Php::Value>::iterator iter;
            for (iter = _objects.begin(); iter != _objects.end(); ++iter) {
                short evts = _poller.call("events", _objects[iter->first]);
                if((evts & ZMQ_POLLIN) || (evts & ZMQ_POLLOUT) || (evts & ZMQ_POLLERR)) {
                    _callbacks[iter->first]();
                }
            }
            _dispatching = false;
            flush_remove_later();
            return true;
        }

        return false;
    }

    Php::Value has_input(Php::Parameters &param) {
        if(param.size() == 0 || !param[0].isObject())
            throw Php::Exception("ZReactor has_input require a ZActor, ZSocker or ZHandle");
        return _poller.call("has_input", param[0]);
    }

    Php::Value has_output(Php::Parameters &param) {
       if(param.size() == 0 || !param[0].isObject())
           throw Php::Exception("ZReactor has_output require a ZActor, ZSocker or ZHandle");
       return _poller.call("has_output", param[0]);
    }

    Php::Value has_error(Php::Parameters &param) {
        if(param.size() == 0 || !param[0].isObject())
            throw Php::Exception("ZReactor has_error require a ZActor, ZSocker or ZHandle");
        return _poller.call("has_error", param[0]);
    }

    static Php::Class<ZReactor> php_register() {
        Php::Class<ZReactor> o("ZReactor");

        o.method("__construct", &ZReactor::__construct);
        o.method("set_verbose", &ZReactor::set_verbose);
        o.method("add", &ZReactor::add);
        o.method("has", &ZReactor::has);
        o.method("remove", &ZReactor::remove);
        o.method("check_for", &ZReactor::check_for);
        o.method("events", &ZReactor::events);
        o.method("poll", &ZReactor::poll);
        o.method("has_input", &ZReactor::has_input);
        o.method("has_output", &ZReactor::has_output);
        o.method("has_error", &ZReactor::has_error);

        return o;
    }

};