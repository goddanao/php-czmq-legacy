#pragma once

#include "../common.h"
#include "../czmq/zmsg.h"

class MalamuteClient   : public ZHandle, public Php::Base {
 private:
     bool _verbose = false;
     std::string _endpoint;
     std::string _address;
     int _timeout = 0;
     bool _connected = false;

 public:

    MalamuteClient() : ZHandle(), Php::Base() {}
    MalamuteClient(mlm_client_t *handle, bool owned) : ZHandle(handle, owned, "mlm_client"), Php::Base() {}
    mlm_client_t *mlm_client_handle() const { return (mlm_client_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
		mlm_client_t *client = mlm_client_new();
		if(!client)
			throw Php::Exception("Internal Error: Can't create MalamuteClient.");
		set_handle(client, true, "mlm_client");
		_endpoint = (param.size() > 0) ? param[0].stringValue() : "";
		_address  = (param.size() > 1) ? param[1].stringValue() : "";
		_timeout  = (param.size() > 2) ? param[2].numericValue() : 0;
	}

	Php::Value connect(Php::Parameters &param) {
		if(_connected)
			return true;
		std::string _ep = (param.size() > 0) ? param[0].stringValue() : _endpoint;
		std::string _ad = (param.size() > 1) ? param[1].stringValue() : _address;
		int _to = (param.size() > 2) ? param[2].numericValue() : _timeout;
		int rc = mlm_client_connect(mlm_client_handle(), _ep.c_str(), _to, _ad.c_str());
		return (rc == 0);
	}

	void set_verbose(Php::Parameters &param) {
		_verbose = param.size() > 0 ? param[0].boolValue() : true;
	}

	Php::Value header(Php::Parameters &param) {
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

	Php::Value content(Php::Parameters &param) {
		zmsg_t *msg = mlm_client_content(mlm_client_handle());
		if(!msg)
			return nullptr;
		return Php::Object("ZMsg", new ZMsg(msg, true));
	}

	Php::Value send_stream(Php::Parameters &param) {
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

	Php::Value send_mailbox(Php::Parameters &param) {
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

	Php::Value send_service(Php::Parameters &param) {
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

	Php::Value recv_picture(Php::Parameters &param) {
		zmsg_t *msg = mlm_client_recv (mlm_client_handle());
		if(!msg)
			return nullptr;
		ZMsg z(msg, true);
		return z.pop_picture(param);
	}

	Php::Value recv() {
        zmsg_t *msg = mlm_client_recv (mlm_client_handle());
        if(!msg)
            return nullptr;
        return Php::Object("ZMsg", new ZMsg(msg, true));
    }

    Php::Value recv_string() {
        zmsg_t *msg = mlm_client_recv (mlm_client_handle());
        if(!msg)
            return nullptr;
        ZMsg z(msg, true);
        return z.pop_string();
    }

    Php::Value set_producer(Php::Parameters &param) { return (mlm_client_set_producer(mlm_client_handle(), param[0].stringValue().c_str()) != -1); }

    Php::Value set_worker(Php::Parameters &param) { return (mlm_client_set_worker(mlm_client_handle(), param[0].stringValue().c_str(), param[1].stringValue().c_str()) != -1); }

    Php::Value set_consumer(Php::Parameters &param) { return (mlm_client_set_consumer(mlm_client_handle(), param[0].stringValue().c_str(), param[1].stringValue().c_str()) != -1); }


    static Php::Class<MalamuteClient> php_register() {
        Php::Class<MalamuteClient> o("Client");
        o.method("__construct", &MalamuteClient::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("address", Php::Type::String, false),
            Php::ByVal("timeout", Php::Type::Numeric, false)
        });
        o.method("set_verbose", &MalamuteClient::set_verbose);
        o.method("connect", &MalamuteClient::connect, {
            Php::ByVal("endpoint", Php::Type::String, false),
            Php::ByVal("address", Php::Type::String, false),
            Php::ByVal("timeout", Php::Type::Numeric, false)
        });
        o.method("header", &MalamuteClient::header);
        o.method("content", &MalamuteClient::content);
        o.method("set_producer", &MalamuteClient::set_producer, {
            Php::ByVal("stream", Php::Type::String, true)
        });
        o.method("set_worker", &MalamuteClient::set_worker, {
            Php::ByVal("address", Php::Type::String, true),
            Php::ByVal("patern", Php::Type::String, true)
        });
        o.method("set_consumer", &MalamuteClient::set_consumer, {
            Php::ByVal("stream", Php::Type::String, true),
            Php::ByVal("patern", Php::Type::String, true)
        });
        o.method("send_stream", &MalamuteClient::send_stream, {
            Php::ByVal("subject", Php::Type::String, true)
        });
        o.method("send_mailbox", &MalamuteClient::send_mailbox, {
            Php::ByVal("address", Php::Type::String, true),
            Php::ByVal("subject", Php::Type::String, true),
            Php::ByVal("pattern", Php::Type::String, true),
            Php::ByVal("timeout", Php::Type::Numeric, true)
        });
        o.method("send_service", &MalamuteClient::send_service, {
            Php::ByVal("address", Php::Type::String, true),
            Php::ByVal("subject", Php::Type::String, true),
            Php::ByVal("pattern", Php::Type::String, true),
            Php::ByVal("timeout", Php::Type::Numeric, true)
        });

        o.method("recv_picture", &MalamuteClient::recv_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });
        o.method("recv_string", &MalamuteClient::recv_string);
        o.method("recv", &MalamuteClient::recv);


        return o;
    }

};
