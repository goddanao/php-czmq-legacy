#include "../../include/malamute/malamute_client.h"
#include "../../include/czmq/zmsg.h"

void MalamuteClient::__construct(Php::Parameters &param) {
	_endpoint = (param.size() > 0) ? param[0].stringValue() : "";
	_address  = (param.size() > 1) ? param[1].stringValue() : "";
	_timeout  = (param.size() > 2) ? param[2].numericValue() : 0;
}

Php::Value MalamuteClient::connect(Php::Parameters &param) {
	if(_connected)
		return true;
	std::string _ep = (param.size() > 0) ? param[0].stringValue() : _endpoint;
	std::string _ad = (param.size() > 1) ? param[1].stringValue() : _address;
	int _to = (param.size() > 2) ? param[2].numericValue() : _timeout;
	mlm_client_t *client = mlm_client_new(_ep.c_str(), _to, _ad.c_str());
	if(!client)
		return false;
	set_handle(client, true, "malamute_client");
	_connected = true;
	return true;
}

void MalamuteClient::set_verbose(Php::Parameters &param) {
	_verbose = param.size() > 0 ? param[0].boolValue() : true;
}

Php::Value MalamuteClient::header(Php::Parameters &param) {
	Php::Value result;
	result["command"]  = mlm_client_command(mlm_client_handle());
	result["status"]   = mlm_client_status(mlm_client_handle());
	result["reason"]   = mlm_client_reason(mlm_client_handle());
	result["address"]  = mlm_client_address(mlm_client_handle());
	result["sender"]   = mlm_client_sender(mlm_client_handle());
	result["subject"]  = mlm_client_subject(mlm_client_handle());
	result["tracker"]  = mlm_client_tracker(mlm_client_handle());
	return result;
}

Php::Value MalamuteClient::content(Php::Parameters &param) {
	zmsg_t *msg = mlm_client_content(mlm_client_handle());
	if(!msg)
		return nullptr;
	return Php::Object("ZMsg", new ZMsg(msg, true));
}

Php::Value MalamuteClient::send_stream(Php::Parameters &param) {
	std::string subject = param[0].stringValue();

	zmsg_t *msg = NULL;
	ZMsg *zmsg = (ZMsg *) dynamic_cast<ZMsg *>(param[1].implementation());
    if(!zmsg) {
    	ZFrame *zframe = (ZFrame *) dynamic_cast<ZFrame *>(param[1].implementation());
    	if(zframe) {
    	    msg = zmsg_new();
    	    zmsg_pushmem(msg, zframe_data(zframe->zframe_handle()), zframe_size(zframe->zframe_handle()));
    	}
    	else
    	if(param[1].isString()) {
    	    msg = zmsg_new();
            zmsg_pushmem(msg, param[1].rawValue(), param[1].size());
    	}
    	else
    	    throw Php::Exception("Send Stream need a ZMsg, ZFrame or String Buffer");
    } else {
    	 msg = zmsg_dup(zmsg->zmsg_handle());
    }
	return (mlm_client_send(mlm_client_handle(), subject.c_str(), &msg) == 0);
}

Php::Value MalamuteClient::send_mailbox(Php::Parameters &param) {
	std::string address = param[0].stringValue();
	std::string subject = param[1].stringValue();
	std::string tracker = param[2].stringValue();
	int _to = (param.size() > 3) ? param[3].numericValue() : _timeout;

	zmsg_t *msg = NULL;
	ZMsg *zmsg = (ZMsg *) dynamic_cast<ZMsg *>(param[4].implementation());
    if(!zmsg) {
    	ZFrame *zframe = (ZFrame *) dynamic_cast<ZFrame *>(param[4].implementation());
    	if(zframe) {
            msg = zmsg_new();
            zmsg_pushmem(msg, zframe_data(zframe->zframe_handle()), zframe_size(zframe->zframe_handle()));
        }
        else
        if(param[4].isString()) {
            msg = zmsg_new();
            zmsg_pushmem(msg, param[4].rawValue(), param[4].size());
        }
        else
            throw Php::Exception("Send Mailbox need a ZMsg, ZFrame or String Buffer");
    } else {
    	 msg = zmsg_dup(zmsg->zmsg_handle());
    }
	return (mlm_client_sendto(mlm_client_handle(), address.c_str(), subject.c_str(), tracker.c_str(), _to, &msg) == 0);
}

Php::Value MalamuteClient::send_service(Php::Parameters &param) {
	std::string address = param[0].stringValue();
	std::string subject = param[1].stringValue();
	std::string tracker = param[2].stringValue();
	int _to = (param.size() > 3) ? param[3].numericValue() : _timeout;

	zmsg_t *msg = NULL;
	ZMsg *zmsg = (ZMsg *) dynamic_cast<ZMsg *>(param[4].implementation());
    if(!zmsg) {
    	ZFrame *zframe = (ZFrame *) dynamic_cast<ZFrame *>(param[4].implementation());
    	if(zframe) {
            msg = zmsg_new();
            zmsg_pushmem(msg, zframe_data(zframe->zframe_handle()), zframe_size(zframe->zframe_handle()));
        }
        else
        if(param[4].isString()) {
            msg = zmsg_new();
            zmsg_pushmem(msg, param[4].rawValue(), param[4].size());
        }
        else
            throw Php::Exception("Send Service need a ZMsg, ZFrame or String Buffer");
    } else {
    	 msg = zmsg_dup(zmsg->zmsg_handle());
    }
	return (mlm_client_sendfor(mlm_client_handle(), address.c_str(), subject.c_str(), tracker.c_str(), _to, &msg) == 0);
}

Php::Value MalamuteClient::recv_picture(Php::Parameters &param) {
	zmsg_t *msg = mlm_client_recv (mlm_client_handle());
	if(!msg)
		return nullptr;
	ZMsg z(msg, true);
	return z.pop_picture(param);
}