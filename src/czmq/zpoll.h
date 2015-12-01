#pragma once

#include "../common.h"

class ZPoll : public Php::Base {
private:

    struct itemdata {
        int index;
        Php::Value object;
    };

    bool _verbose = false;
    std::vector<zmq_pollitem_t> _items;
    std::map<uintptr_t, itemdata> _objects;

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
        itemdata data = { index, param[0] };
        std::pair<uintptr_t, itemdata> el = {item.socket != nullptr ? (uintptr_t) item.socket : (uintptr_t) item.fd, data };
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
            _items.erase(_items.begin() + found->second.index);
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
            _items[found->second.index].events = (short) param[1].numericValue();
        }
    }

    Php::Value events(Php::Parameters &param) {
        zmq_pollitem_t item = ZUtils::phpvalue_to_pollitem(param[0]);
        if(item.socket == nullptr && item.fd == INVALID_SOCKET)
            throw Php::Exception("Cannot create PollItem.");

        uintptr_t key = item.socket != nullptr ? (uintptr_t) item.socket : (uintptr_t) item.fd;
        auto found = _objects.find(key);
        if(found != _objects.end()) {
            return _items[found->second.index].revents;
        }
        return false;
    }

    Php::Value poll(Php::Parameters &param) {

        long timeout  = -1;
        int readable  = -1;
        int writeable = -1;

        bool valid = (param.size() == 0);
        if(!valid && param[0].isNumeric()) {
            timeout = param[0].numericValue();
            valid = true;
        } else
        if(!valid && param[0].isArray()) {
            readable = 0;
            valid = true;
            if(param.size() > 1 && param[1].isNumeric()) {
                timeout = param[1].numericValue();
            }
            else
            if(param.size()>1 && param[1].isArray()) {
                writeable = 1;
                if(param.size() > 2 && param[2].isNumeric()) {
                    timeout = param[2].numericValue();
                }
            }
        }

        if(!valid)
            throw Php::Exception("ZPoll::poll requires a timeout or a readers, writes array and timeout.");

        int result   = zmq_poll(_items.data(), _items.size(), timeout);
        if (result < 0) {
            if(EINTR == zmq_errno())
                return false;
            throw Php::Exception(zmq_strerror (zmq_errno()));
        }

        if(result > 0 && readable != -1) {
            int r = 0; int w = 0;
            for (auto it = std::begin(_objects); it!=std::end(_objects); ++it) {
                if(_items[it->second.index].revents & ZMQ_POLLIN) {
                    param[readable][r++] = it->second.object;
                }
                if(writeable != -1 && (_items[it->second.index].revents & ZMQ_POLLOUT)) {
                    param[writeable][w++] = it->second.object;
                }
            }
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

        o.method("poll_array", &ZPoll::poll, {
            Php::ByRef("readers", Php::Type::Array, true),
            Php::ByRef("writers", Php::Type::Array, true),
            Php::ByVal("timeout", Php::Type::Numeric, false)
        });

        o.method("poll", &ZPoll::poll, {
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