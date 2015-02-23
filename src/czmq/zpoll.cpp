#include "../../include/czmq/zpoll.h"
#include "../../include/czmq/zhandle.h"

void ZPoll::reindex(size_t const index) {
    if ( nullptr != _items[index].socket )
	{
		auto found = _index.find( _items[index].socket );
		if (_index.end() == found) { throw Php::Exception("unable to reindex socket in poller"); }
		found->second = index;
	}
	else
	{
		auto found = _fdindex.find( _items[index].fd );
		if (_fdindex.end() == found) { throw Php::Exception("unable to reindex file descriptor in poller"); }
		found->second = index;
	}
}

void ZPoll::set_verbose(Php::Parameters &param) {
    _verbose = param.size()>0 ? (bool) param[0] : true;
}

void ZPoll::add(Php::Parameters &param) {
    if(param.size() == 0 || !param[0].isObject())
        throw Php::Exception("ZPoller add require a ZActor, ZSocker or ZHandle and a poll mode.");

    // default ZMQ_POLL_IN
    short event = (param.size()>1) ? (short) param[1].numericValue() : ZMQ_POLLIN;
    std::string classname = Php::call("get_class", param[0]);
    ZHandle *zhandle = dynamic_cast<ZHandle *>(param[0].implementation());

    void *socket = NULL;

    if(zhandle != NULL) {
        socket = zhandle->get_socket();
        if(socket) {
            zmq_pollitem_t item { socket, 0, event, 0 };
            size_t index = _items.size();
            _items.push_back(item);
            _index[socket] = index;
            std::pair<void *, Php::Value> el = {socket, param[0]};
            _objects.insert(el);
        } else {
            if(_verbose)
                zsys_info ("zpoller -> ne' socket, ne' fd ?!??!");
        }
    }

}

Php::Value ZPoll::has(Php::Parameters &param) {
    if(param.size() == 0 || !param[0].isObject())
        throw Php::Exception("ZPoller has require a ZActor, ZSocker or ZHandle");

    std::string classname = Php::call("get_class", param[0]);
    ZHandle *zhandle = dynamic_cast<ZHandle *>(param[0].implementation());

    void *socket = NULL;

    if(zhandle != NULL) {
        socket = zhandle->get_socket();
        if(socket)
            return _index.find(socket) != _index.end();
        else {
            if(_verbose)
                zsys_info ("zpoller -> ne' socket, ne' fd ?!??!");
        }
    }

    return false;
}

void ZPoll::remove(Php::Parameters &param) {
    if(param.size() == 0 || !param[0].isObject())
        throw Php::Exception("ZPoller remove require a ZActor, ZSocker or ZHandle");

    std::string classname = Php::call("get_class", param[0]);
    ZHandle *zhandle = dynamic_cast<ZHandle *>(param[0].implementation());

    void *socket = NULL;

    if(zhandle != NULL) {
        socket = zhandle->get_socket();

        if(socket) {
            auto ofound = _objects.find((void *) socket);
            if(ofound != _objects.end()) {
                _objects.erase(ofound);
            }
            auto found = _index.find(socket);
            if (_index.end() == found) { return; }
            if ( _items.size() - 1 == found->second ) {
                _items.pop_back();
                _index.erase(found);
                return;
            }
            std::swap(_items[found->second], _items.back());
            _items.pop_back();
            auto index = found->second;
            _index.erase(found);
            reindex( index );
        }
        else {
            if(_verbose)
                zsys_info ("zpoller -> ne' socket, ne' fd ?!??!");
        }
    }
}

void ZPoll::check_for(Php::Parameters &param) {
    if(param.size() < 2 || !param[0].isObject())
        throw Php::Exception("ZPoller check_for require a ZActor, ZSocker or ZHandle and event type");

    short event = param[1];
    std::string classname = Php::call("get_class", param[0]);
    ZHandle *zhandle = dynamic_cast<ZHandle *>(param[0].implementation());

    void *socket = NULL;

    if(zhandle != NULL) {
        socket = zhandle->get_socket();

        if(socket) {
            auto found = _index.find(socket);
            if (_index.end() == found) { return; }
            _items[found->second].events = event;
        }
        else {
            if(_verbose)
                zsys_info ("zpoller -> ne' socket, ne' fd ?!??!");
        }
    }
}

Php::Value ZPoll::events(Php::Parameters &param) {
    if(param.size() == 0 || !param[0].isObject())
        throw Php::Exception("ZPoller events require a ZActor, ZSocker or ZHandle");

    std::string classname = Php::call("get_class", param[0]);
    ZHandle *zhandle = dynamic_cast<ZHandle *>(param[0].implementation());

    void *socket = NULL;

    if(zhandle != NULL) {
        socket = zhandle->get_socket();

        if(socket) {
            auto found = _index.find(socket);
            if (_index.end() == found) {
                return 0;
            }
            return _items[found->second].revents;
        }
        else {
            if(_verbose)
                zsys_info ("zpoller -> ne' socket, ne' fd ?!??!");
        }
    }

    return false;
}

Php::Value ZPoll::poll(Php::Parameters &param) {
    long timeout = (param.size()>0) ? (long) param[0] : -1; // -1 = WAIT_FOREVER
    int result   = zmq_poll(_items.data(), _items.size(), timeout);
    if (result < 0) {
        if(EINTR == zmq_errno())
            return false;
        throw Php::Exception(zmq_strerror (zmq_errno()));
    }
    return (result > 0);
}

Php::Value ZPoll::has_input(Php::Parameters &param) {
    short evs = events(param);
    return (evs & ZMQ_POLLIN) > 0;
}

Php::Value ZPoll::has_output(Php::Parameters &param) {
    short evs = events(param);
    return (evs & ZMQ_POLLOUT) > 0;
}

Php::Value ZPoll::has_error(Php::Parameters &param) {
    short evs = events(param);
    return (evs & ZMQ_POLLERR) > 0;
}