#pragma once

#include "../common.h"

class ZPoll : public Php::Base {
private:
    bool _verbose = false;
    std::vector<zmq_pollitem_t> _items;
    std::map<uintptr_t, int> _objects;

public:

    void set_verbose(Php::Parameters &param) {
        _verbose = param.size()>0 ? (bool) param[0] : true;
    }

    void add(Php::Parameters &param) {
        short event = (param.size() > 1) ? (short) param[1].numericValue() : ZMQ_POLLIN;
        zmq_pollitem_t item = ZUtils::phpvalue_to_pollitem(param[0], event);
        if(item.socket == nullptr && item.fd == INVALID_SOCKET)
            throw Php::Exception("Cannot create PollItem.");

        int index = _items.size();
        _items.push_back(item);
        std::pair<uintptr_t, int> el = {item.socket != nullptr ? (uintptr_t) item.socket : (uintptr_t) item.fd, index };
        _objects.insert(el);
    }

    Php::Value has(Php::Parameters &param) {
        zmq_pollitem_t item = ZUtils::phpvalue_to_pollitem(param[0]);
        if(item.socket == nullptr && item.fd == INVALID_SOCKET)
            throw Php::Exception("Cannot create PollItem.");
        uintptr_t key = item.socket != nullptr ? (uintptr_t) item.socket : (uintptr_t) item.fd;
        return _objects.find(key) != _objects.end();
    }

    void remove(Php::Parameters &param) {
        zmq_pollitem_t item = ZUtils::phpvalue_to_pollitem(param[0]);
        if(item.socket == nullptr && item.fd == INVALID_SOCKET)
            throw Php::Exception("Cannot create PollItem.");

        uintptr_t key = item.socket != nullptr ? (uintptr_t) item.socket : (uintptr_t) item.fd;
        auto found = _objects.find(key);
        if(found != _objects.end()) {
            _items.erase(_items.begin() + found->second);
            _objects.erase(found);
        }
    }

    void check_for(Php::Parameters &param) {
        zmq_pollitem_t item = ZUtils::phpvalue_to_pollitem(param[0]);
        if(item.socket == nullptr && item.fd == INVALID_SOCKET)
            throw Php::Exception("Cannot create PollItem.");

        uintptr_t key = item.socket != nullptr ? (uintptr_t) item.socket : (uintptr_t) item.fd;
        auto found = _objects.find(key);
        if(found != _objects.end()) {
            _items[found->second].events = (short) param[1].numericValue();
        }
    }

    Php::Value events(Php::Parameters &param) {
        zmq_pollitem_t item = ZUtils::phpvalue_to_pollitem(param[0]);
        if(item.socket == nullptr && item.fd == INVALID_SOCKET)
            throw Php::Exception("Cannot create PollItem.");

        uintptr_t key = item.socket != nullptr ? (uintptr_t) item.socket : (uintptr_t) item.fd;
        auto found = _objects.find(key);
        if(found != _objects.end()) {
            return _items[found->second].revents;
        }
        return false;
    }

    Php::Value poll(Php::Parameters &param) {
        long timeout = (param.size()>0) ? param[0].numericValue() : -1; // -1 = WAIT_FOREVER
        int result   = zmq_poll(_items.data(), _items.size(), timeout);
        if (result < 0) {
            if(EINTR == zmq_errno())
                return false;
            throw Php::Exception(zmq_strerror (zmq_errno()));
        }
        return (result > 0);
    }

    Php::Value has_input(Php::Parameters &param) {
        short evs = events(param);
        return (evs & ZMQ_POLLIN) > 0;
    }

    Php::Value has_output(Php::Parameters &param) {
        short evs = events(param);
        return (evs & ZMQ_POLLOUT) > 0;
    }

    Php::Value has_error(Php::Parameters &param) {
        short evs = events(param);
        return (evs & ZMQ_POLLERR) > 0;
    }

    static Php::Class<ZPoll> php_register() {

        Php::Class<ZPoll> o("ZPoll");

        o.method("set_verbose", &ZPoll::set_verbose, {
            Php::ByVal("verbose", Php::Type::Bool, false)
        });

        o.method("add", &ZPoll::add, {
            Php::ByVal("pollitem", Php::Type::String, true),
            Php::ByVal("mode", Php::Type::Numeric, false)
        });
        o.method("has", &ZPoll::has, {
            Php::ByVal("pollitem", Php::Type::String, true)
        });
        o.method("remove", &ZPoll::remove, {
             Php::ByVal("pollitem", Php::Type::String, true)
        });
        o.method("check_for", &ZPoll::check_for, {
            Php::ByVal("pollitem", Php::Type::String, true),
            Php::ByVal("event", Php::Type::Numeric, false)
        });

        o.method("events", &ZPoll::events, {
            Php::ByVal("pollitem", Php::Type::String, true)
        });

        o.method("poll", &ZPoll::poll, {
//            Php::ByRef("readable", Php::Type::Array, true),
//            Php::ByRef("writeable", Php::Type::Array, true),
            Php::ByVal("timeout", Php::Type::Numeric, false)
        });

        o.method("has_input", &ZPoll::has_input, {
            Php::ByVal("pollitem", Php::Type::String, true)
        });
        o.method("has_output", &ZPoll::has_output, {
            Php::ByVal("pollitem", Php::Type::String, true)
        });
        o.method("has_error", &ZPoll::has_error, {
            Php::ByVal("pollitem", Php::Type::String, true)
        });

        return o;

    }


};