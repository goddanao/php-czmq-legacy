#include "../../include/czmq/zreactor.h"

void ZReactor::__construct(Php::Parameters &param) {
    _poller = Php::Object("ZPoll", new ZPoll());
}

void ZReactor::set_verbose(Php::Parameters &param) {
    _verbose = param.size()>0 ? (bool) param[0] : true;
}

void ZReactor::add(Php::Parameters &param) {
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

Php::Value ZReactor::has(Php::Parameters &param) {
    if(param.size() == 0 || !param[0].isObject())
        throw Php::Exception("ZReactor has require a ZActor, ZSocker or ZHandle");
    return _poller.call("has", param[0]);
}

void ZReactor::remove(Php::Parameters &param) {
    if(param.size() == 0 || !param[0].isObject())
        throw Php::Exception("ZReactor remove require a ZActor, ZSocker or ZHandle");
    _remove(dynamic_cast<ZHandle *> (param[0].implementation()));
}

void ZReactor::_remove(ZHandle *to_remove) {
    if (_dispatching){
        _objectsRemoveLater.push_back(to_remove);
        return;
    }
    _poller.call("remove", _objects[to_remove]);
    _objects.erase(to_remove);
    _callbacks.erase(to_remove);
}

void ZReactor::check_for(Php::Parameters &param) {
    if(param.size() < 2 || !param[0].isObject())
        throw Php::Exception("ZReactor check_for require a ZActor, ZSocker or ZHandle");

    _poller.call("check_for", param[0], param[1]);
}

Php::Value ZReactor::events(Php::Parameters &param) {
    if(param.size() == 0 || !param[0].isObject())
        throw Php::Exception("ZReactor events require a ZActor, ZSocker or ZHandle");
    return _poller.call("events", param[0]);
}

Php::Value ZReactor::poll(Php::Parameters &param) {
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

void ZReactor::flush_remove_later() {
    for (const ZHandle *sock : _objectsRemoveLater)
        _remove((ZHandle *) sock);
    _objectsRemoveLater.clear();
}

Php::Value ZReactor::has_input(Php::Parameters &param) {
    if(param.size() == 0 || !param[0].isObject())
        throw Php::Exception("ZReactor has_input require a ZActor, ZSocker or ZHandle");
    return _poller.call("has_input", param[0]);
}

Php::Value ZReactor::has_output(Php::Parameters &param) {
   if(param.size() == 0 || !param[0].isObject())
       throw Php::Exception("ZReactor has_output require a ZActor, ZSocker or ZHandle");
   return _poller.call("has_output", param[0]);
}

Php::Value ZReactor::has_error(Php::Parameters &param) {
    if(param.size() == 0 || !param[0].isObject())
        throw Php::Exception("ZReactor has_error require a ZActor, ZSocker or ZHandle");
    return _poller.call("has_error", param[0]);
}