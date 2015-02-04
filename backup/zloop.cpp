#include "../include/zloop.h"

void ZLoop::__construct(Php::Parameters &param) {
    zsys_info("zloop_conscutct");
	set_handle(zloop_new(), true, "zpoll");
	zsys_info("zloop_conscutct end");
}

void ZLoop::set_verbose (Php::Parameters &param) {
	_verbose = param.size() > 0 ? param[0].boolValue() : true;
	zloop_set_verbose(zloop_handle(), _verbose);
}


void ZLoop::add(Php::Parameters &param) {
    if(param.size() == 0 || !param[0].isObject())
        throw Php::Exception("ZLoop add require a ZActor, ZSocker or ZHandle.");

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