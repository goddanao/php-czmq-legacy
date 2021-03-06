#pragma once

#include "zmsg.h"

class ZUdp : public ZHandle, public Php::Base {
private:
    bool _verbose = false;
    inaddr_t broadcast;         //  Our broadcast address
public:
    ZUdp() : ZHandle(), Php::Base() {}
    ZUdp(SOCKET handle, bool owned) : ZHandle(handle, owned, "zudp"), Php::Base() {}
    SOCKET  zudp_handle() const { return _fd; }

    void set_verbose (Php::Parameters &param) {
    	_verbose = param.size() > 0 ? param[0].boolValue() : true;
    }

    void __construct(Php::Parameters &param) {
        std::string interface = (param.size() > 0) ? param[0].stringValue() : "";
        const char* iface = interface.c_str();
        int port_nbr = (param.size() > 1) ? param[1].numericValue() : 5670;
        bool routable = (param.size() > 2) ? param[2].boolValue() : false;

        SOCKET socket = zsys_udp_new(routable);
        if(INVALID_SOCKET == socket)
            throw Php::Exception("ZUdp can't create UDP Socket");

        in_addr_t bind_to = 0;
        in_addr_t send_to = 0;

        if (streq (iface, "*")) {
            //  Wildcard means bind to INADDR_ANY and send to INADDR_BROADCAST
            bind_to = INADDR_ANY;
            send_to = INADDR_BROADCAST;
        }
        else {
            //  Look for matching interface, or first ziflist item
            ziflist_t *iflist = ziflist_new ();
            assert (iflist);
            const char *name = ziflist_first (iflist);
            while (name) {
                if (streq (iface, name) || streq (iface, "")) {
                    //  Using inet_addr instead of inet_aton or inet_atop
                    //  because these are not supported in Win XP
                    send_to = inet_addr (ziflist_broadcast (iflist));
                    bind_to = inet_addr (ziflist_address (iflist));
                    if (_verbose)
                        zsys_info ("ZUdp: interface=%s address=%s broadcast=%s", name, ziflist_address (iflist), ziflist_broadcast (iflist));
                    break;      //  iface is known, so allow it
                }
                name = ziflist_next (iflist);
            }
            ziflist_destroy (&iflist);
        }

        if (bind_to) {
            broadcast.sin_family = AF_INET;
            broadcast.sin_port = htons (port_nbr);
            broadcast.sin_addr.s_addr = send_to;
            inaddr_t address = broadcast;
            address.sin_addr.s_addr = bind_to;
            //  Bind to the port on all interfaces
        #if (defined (__WINDOWS__))
            inaddr_t sockaddr = address;
        #elif (defined (__APPLE__))
            inaddr_t sockaddr = broadcast;
            sockaddr.sin_addr.s_addr = htons (INADDR_ANY);
        #else
            inaddr_t sockaddr = broadcast;
        #endif

            if (bind (socket, (struct sockaddr *) &sockaddr, sizeof (inaddr_t))) {
                zsys_udp_close(socket);
                socket = INVALID_SOCKET;
                throw Php::Exception("ZUdp can't bind UDP Socket");
            }

            char hostname [NI_MAXHOST];
            if (getnameinfo ((struct sockaddr *) &address, sizeof (inaddr_t), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) == 0) {
                if (_verbose)
                    zsys_info ("ZUdp: configured, hostname=%s", hostname);
            }

        } else {
            zsys_udp_close(socket);
            socket = INVALID_SOCKET;
            throw Php::Exception("ZUdp can't bind UDP Socket");
        }

        set_handle(socket, true, "zudp");
    }

    bool _send(zmsg_t *msg) override {
        int rc = -1;
        if(msg) {
            rc = 0;
            zframe_t *frame = zmsg_pop (msg);
            while(frame && (rc == 0)) {
                #if (CZMQ_VERSION >= CZMQ_MAKE_VERSION(3,0,3))
                    rc = zsys_udp_send(zudp_handle(), frame, &broadcast, sizeof (inaddr_t));
                #else
                    rc = zsys_udp_send(zudp_handle(), frame, &broadcast);
                #endif
                zframe_destroy(&frame);
                frame = zmsg_pop (msg);
            }
            zmsg_destroy(&msg);
        }
        return (rc == 0);
    }

    zmsg_t *_recv() override {
        char peername [INET_ADDRSTRLEN];

        #if (CZMQ_VERSION >= CZMQ_MAKE_VERSION(3,0,3))
            zframe_t *frame = zsys_udp_recv(zudp_handle(), peername, INET_ADDRSTRLEN);
        #else
            zframe_t *frame = zsys_udp_recv(zudp_handle(), peername);
        #endif

        if(!frame)
            return nullptr;

        zmsg_t *msg = zmsg_new();
        zmsg_addstr(msg, peername);
        zmsg_append(msg, &frame);
        return msg;
    }

    static Php::Class<ZUdp> php_register() {
        Php::Class<ZUdp> o("ZUdp");

        o.method("__construct", &ZUdp::__construct, {
            Php::ByVal("interface", Php::Type::String, false),
            Php::ByVal("port", Php::Type::Numeric, false),
            Php::ByVal("routable", Php::Type::Bool, false)
        });
        o.method("set_verbose", &ZUdp::set_verbose);

        // Send / Recv
        ZHandle::register_recv((Php::Class<ZUdp> *) &o);
        ZHandle::register_send((Php::Class<ZUdp> *) &o);

        // IZDescriptor intf support
        ZHandle::register_izdescriptor((Php::Class<ZUdp> *) &o);

        return o;
    }

};
