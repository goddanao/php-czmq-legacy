#pragma once

#include "../common.h"
#include <zyre.h>

class Zyre : public ZHandle, public Php::Base {
private:
    bool _verbose = false;
public:
    Zyre() : ZHandle(), Php::Base() {}
    Zyre(zyre_t *handle, bool owned) : ZHandle(handle, owned, "zyre"), Php::Base() {}
    zyre_t *zyre_handle() { return (zyre_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
		if(param.size() > 0 && param[0].isString()){
			set_handle((void *) zyre_new (param[0].stringValue().c_str()), true, "zyre");
		} else
			set_handle((void *) zyre_new (NULL), true, "zyre");
	}

	Php::Value get_uuid() {
		return zyre_uuid(zyre_handle());
	}

	Php::Value get_name() {
		return zyre_name(zyre_handle());
	}

	Php::Value get_peers() {
		Php::Value result;
		int result_idx = 0;
		zlist_t *list = zyre_peers(zyre_handle());
		char *item = (char *) zlist_first(list);
		while(item) {

			char *peer_address  = zyre_peer_address(zyre_handle(), item);

			result[result_idx]["id"] = item;
			result[result_idx]["address"] = peer_address;

			result_idx++;

			free(peer_address);

			item = (char *) zlist_next(list);
		}
		zlist_destroy(&list);

		return result;
	}

	Php::Value get_groups() {
		Php::Value result;
		int result_idx = 0;
		zlist_t *list = zyre_own_groups(zyre_handle());
		char *item = (char *) zlist_first(list);
		while(item) {
			result[result_idx++] = item;
			item = (char *) zlist_next(list);
		}
		zlist_destroy(&list);
		return result;
	}

	Php::Value get_peer_groups() {
        Php::Value result;
        int result_idx = 0;
        zlist_t *list = zyre_peer_groups(zyre_handle());
        char *item = (char *) zlist_first(list);
        while(item) {
            result[result_idx++] = item;
            item = (char *) zlist_next(list);
        }
        zlist_destroy(&list);
        return result;
    }


	void set_port(Php::Parameters &param) { zyre_set_port(zyre_handle(), param[0].numericValue()); }
	void set_interface(Php::Parameters &param) { zyre_set_interface(zyre_handle(), param[0].stringValue().c_str()); }
	void set_interval(Php::Parameters &param) { zyre_set_interval(zyre_handle(), param[0].numericValue()); }


	Php::Value set_endpoint(Php::Parameters &param) {
		return (zyre_set_endpoint(zyre_handle(), param[0].stringValue().c_str()) == 0);
	}

	void gossip_bind(Php::Parameters &param) {
		zyre_gossip_bind(zyre_handle(), param[0].stringValue().c_str());
	}

	void gossip_connect(Php::Parameters &param) {
		zyre_gossip_connect(zyre_handle(), param[0].stringValue().c_str());
	}

	Php::Value get_peer_header(Php::Parameters &param) {
		char *value = zyre_peer_header_value(zyre_handle(), param[0].stringValue().c_str(), param[1].stringValue().c_str());
		Php::Value result = value;
		free(value);
		return result;
	}


	static Php::Value get_version() {
		int major, minor, patch;
		zyre_version (&major, &minor, &patch);
		return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
	}

	void dump() {
		zyre_dump(zyre_handle());
	}

	void set_verbose() {
		zyre_set_verbose(zyre_handle());
	}

	void set_header(Php::Parameters &param) {
		zyre_set_header(zyre_handle(), (char *)param[0].stringValue().c_str(), (char *)param[1].stringValue().c_str());
	}

	Php::Value start() {
		return (zyre_start(zyre_handle()) == 0);
	}

	void stop() {
		zyre_stop(zyre_handle());
	}

	Php::Value join(Php::Parameters &param) {
		return (zyre_join(zyre_handle(), param[0].stringValue().c_str()) == 0);
	}

	Php::Value leave(Php::Parameters &param) {
		return (zyre_leave(zyre_handle(), param[0].stringValue().c_str()) == 0);
	}

	Php::Value recv(Php::Parameters &param) {

		zmsg_t *msg = zyre_recv(zyre_handle());
		if(msg == NULL)
			return nullptr;

		char *command = zmsg_popstr(msg);
		char *peerid  = zmsg_popstr(msg);
		char *name = zmsg_popstr (msg);

		Php::Value result;

		result["command"] = command;
		result["peerid"] = peerid;
		result["name"] = name;

		if(strcmp(command, "ENTER") == 0) {

			zframe_t *headers_packed = zmsg_pop (msg);
			if (headers_packed != NULL) {
				zhash_t *headers = zhash_unpack (headers_packed);
				zlist_t *hk = zhash_keys(headers);
				char *item = (char *) zlist_first(hk);
				while(item) {
					std::string lbl = item;
					result["headers"][lbl] = (char *) zhash_lookup(headers, item);
					item = (char *) zlist_next(hk);
				}
				zframe_destroy (&headers_packed);
				zhash_destroy(&headers);
				zlist_destroy(&hk);
			}

			char *address = zmsg_popstr(msg);
			result["address"] = address;
			free(address);

		} else if(strcmp(command, "JOIN") == 0) {
			char *group = zmsg_popstr(msg);
			result["group"] = group;
			free(group);
		} else if(strcmp(command, "LEAVE") == 0) {
			char *group = zmsg_popstr(msg);
			result["group"] = group;
			free(group);
		} else if(strcmp(command, "SHOUT") == 0) {
			char *group = zmsg_popstr(msg);
			char *data  = zmsg_popstr(msg);
			result["group"] = group;
			result["data"] = data;
			free(group);
			free(data);
		} else if(strcmp(command, "WHISPER") == 0) {
			char *data  = zmsg_popstr(msg);
			result["data"] = data;
			free(data);
		} else {
			// ...
		}

		if (command != NULL)
			free(command);
		if (peerid != NULL)
			free(peerid);
		if (name != NULL)
			free(name);
		if (msg != NULL)
			zmsg_destroy(&msg);

		return result;
	}

	Php::Value send_peer(Php::Parameters &param) {
		zmsg_t *msg = zmsg_new();
		zmsg_pushstr(msg, (char *) param[1].stringValue().c_str());
		return (zyre_whisper(zyre_handle(), (char *) param[0].stringValue().c_str(), &msg) == 0);
	}

	Php::Value send_group(Php::Parameters &param) {
		zmsg_t *msg = zmsg_new();
		zmsg_pushstr(msg, (char *) param[1].stringValue().c_str());
		return (zyre_shout(zyre_handle(), (char *) param[0].stringValue().c_str(), &msg) == 0);
	}

    static Php::Class<Zyre> php_register() {

        Php::Class<Zyre> o("Zyre");

        o.method("__construct", &Zyre::__construct, {
            Php::ByVal("name", Php::Type::String, false)
        });

        o.method("start", &Zyre::start);
        o.method("stop", &Zyre::stop);
        o.method("recv", &Zyre::recv);
        o.method("dump", &Zyre::dump);
        o.method("get_uuid", &Zyre::get_uuid);

        o.method("get_name", &Zyre::get_name);
        o.method("get_peers", &Zyre::get_peers);
        o.method("get_groups", &Zyre::get_groups);
        o.method("get_peer_groups", &Zyre::get_peer_groups);
        o.method("set_endpoint", &Zyre::set_endpoint, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
        o.method("set_port", &Zyre::set_port, {
            Php::ByVal("port", Php::Type::Numeric, true)
        });
        o.method("set_interface", &Zyre::set_interface, {
            Php::ByVal("interface", Php::Type::String, true)
        });
        o.method("set_interval", &Zyre::set_interval, {
            Php::ByVal("interval", Php::Type::Numeric, true)
        });
        o.method("gossip_bind", &Zyre::gossip_bind, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
        o.method("gossip_connect", &Zyre::gossip_connect, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
        o.method("get_peer_header", &Zyre::get_peer_header, {
            Php::ByVal("name", Php::Type::String, true)
        });

        o.method("get_version", &Zyre::get_version);
        o.method("set_verbose", &Zyre::set_verbose);

        o.method("set_header", &Zyre::set_header, {
            Php::ByVal("name", Php::Type::String, true),
            Php::ByVal("value", Php::Type::String, true)
        });

        o.method("join", &Zyre::join, {
            Php::ByVal("group", Php::Type::String, true)
        });
        o.method("leave", &Zyre::leave, {
            Php::ByVal("group", Php::Type::String, true)
        });
        o.method("send_peer", &Zyre::send_peer, {
            Php::ByVal("peer", Php::Type::String, true),
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("send_group", &Zyre::send_group, {
            Php::ByVal("group", Php::Type::String, true),
            Php::ByVal("data", Php::Type::String, true)
        });

		// IZSocket intf support
        o.method("get_socket", &Zyre::_get_socket);
        o.method("get_fd", &Zyre::_get_fd);

        return o;
    }

};
