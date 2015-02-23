#include "../../include/zyre/zyre.h"

void Zyre::__construct(Php::Parameters &param) {
	if(param.size() > 0 && param[0].isString()){
		set_handle((void *) zyre_new (param[0].stringValue().c_str()), true, "zyre");
	} else
		set_handle((void *) zyre_new (NULL), true, "zyre");
}

Php::Value Zyre::get_uuid() {
	return zyre_uuid(zyre_handle());
}

Php::Value Zyre::get_name() {
	return zyre_name(zyre_handle());
}

Php::Value Zyre::get_peers() {
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

Php::Value Zyre::get_groups() {
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

Php::Value Zyre::set_endpoint(Php::Parameters &param) {
	return (zyre_set_endpoint(zyre_handle(), param[0].stringValue().c_str()) == 0);
}

void Zyre::gossip_bind(Php::Parameters &param) {
	zyre_gossip_bind(zyre_handle(), param[0].stringValue().c_str());
}

void Zyre::gossip_connect(Php::Parameters &param) {
	zyre_gossip_connect(zyre_handle(), param[0].stringValue().c_str());
}

Php::Value Zyre::get_peer_header(Php::Parameters &param) {
	char *value = zyre_peer_header_value(zyre_handle(), param[0].stringValue().c_str(), param[1].stringValue().c_str());
	Php::Value result = value;
	free(value);
	return result;
}


Php::Value Zyre::get_version() {
	int major, minor, patch;
	zyre_version (&major, &minor, &patch);
	return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}

void Zyre::dump() {
	zyre_dump(zyre_handle());
}

void Zyre::set_verbose() {
	zyre_set_verbose(zyre_handle());
}

void Zyre::set_header(Php::Parameters &param) {
	zyre_set_header(zyre_handle(), (char *)param[0].stringValue().c_str(), (char *)param[1].stringValue().c_str());
}

Php::Value Zyre::start() {
	return (zyre_start(zyre_handle()) == 0);
}

void Zyre::stop() {
	zyre_stop(zyre_handle());
}

Php::Value Zyre::join(Php::Parameters &param) {
	return (zyre_join(zyre_handle(), param[0].stringValue().c_str()) == 0);
}

Php::Value Zyre::leave(Php::Parameters &param) {
	return (zyre_leave(zyre_handle(), param[0].stringValue().c_str()) == 0);
}

Php::Value Zyre::recv() {

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

Php::Value Zyre::send_peer(Php::Parameters &param) {
	zmsg_t *msg = zmsg_new();
	zmsg_pushstr(msg, (char *) param[1].stringValue().c_str());
	return (zyre_whisper(zyre_handle(), (char *) param[0].stringValue().c_str(), &msg) == 0);
}

Php::Value Zyre::send_group(Php::Parameters &param) {
	zmsg_t *msg = zmsg_new();
	zmsg_pushstr(msg, (char *) param[1].stringValue().c_str());
	return (zyre_shout(zyre_handle(), (char *) param[0].stringValue().c_str(), &msg) == 0);
}