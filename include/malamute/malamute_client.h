#pragma once

#include "../common.h"

class MalamuteClient   : public ZHandle {
 private:
     bool _verbose = false;
     std::string _endpoint;
     std::string _address;
     int _timeout = 0;
     bool _connected = false;
 public:
    MalamuteClient() : ZHandle() {}
    MalamuteClient(mlm_client_t *handle, bool owned) : ZHandle(handle, owned, "malamute_client") {}
    mlm_client_t *mlm_client_handle() const { return (mlm_client_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    Php::Value connect(Php::Parameters &param);

    void set_verbose(Php::Parameters &param);

    Php::Value set_producer(Php::Parameters &param) { return (mlm_client_set_producer(mlm_client_handle(), param[0].stringValue().c_str()) != -1); }

    Php::Value set_worker(Php::Parameters &param) { return (mlm_client_set_worker(mlm_client_handle(), param[0].stringValue().c_str(), param[1].stringValue().c_str()) != -1); }

    Php::Value set_consumer(Php::Parameters &param) { return (mlm_client_set_consumer(mlm_client_handle(), param[0].stringValue().c_str(), param[1].stringValue().c_str()) != -1); }

    Php::Value header(Php::Parameters &param);

    Php::Value content(Php::Parameters &param);

    Php::Value send_stream(Php::Parameters &param);
    Php::Value send_mailbox(Php::Parameters &param);
    Php::Value send_service(Php::Parameters &param);

    // Ovverride of ZHandle::recv_picture
    Php::Value recv_picture(Php::Parameters &param);

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

        // From ZHandle
//        o.method("recv_picture", &MalamuteClient::recv_picture, {
//            Php::ByVal("picture", Php::Type::String, true)
//        });
//        o.method("recv_string", &MalamuteClient::recv_string);
//        o.method("recv", &MalamuteClient::recv);


        return o;
    }

};
