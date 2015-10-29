#include "../../include/czmq/zudp.h"
#include "../../include/czmq/zframe.h"
#include "../../include/czmq/zmsg.h"

void ZUdp::__construct(Php::Parameters &param) {
    bool routable = (param.size()>0) ? param[0].boolValue() : false;
    _socket = zsys_udp_new(routable);
    set_handle((void *) &_socket, true, "zudp");
}

void ZUdp::send(Php::Parameters &param) {

    inaddr_t* address = nullptr; // ???
    zframe_t *frame = nullptr;

    ZFrame *zframe = dynamic_cast<ZFrame *>(param[0].implementation());
    if(!zframe) {
        ZMsg *zmsg = dynamic_cast<ZMsg *>(param[0].implementation());
        if(zmsg) {
            frame = zmsg_pop (zmsg->zmsg_handle());
            if(frame) {
                zsys_udp_send(zudp_handle(), frame, address);
                zframe_destroy(&frame);
            }
        }
    } else {
        frame = zframe->zframe_handle();
        zsys_udp_send(zudp_handle(), frame, address);
    }
}

Php::Value ZUdp::recv() {
    char *peername = "stocazzo"; // ????
    zframe_t *frame = zsys_udp_recv(zudp_handle(), peername);
    if(frame)
        Php::Object("ZFrame", new ZFrame(frame, true));
    return nullptr;
}
