#pragma once

#include <phpcpp.h>
#include <czmq.h>
#include "zmdp_common.h"

class MajordomoClient : public Php::Base {
private:
  std::string broker;
  zsock_t *client = NULL;   //  Socket to broker
  int verbose = 0;          //  Print activity to stdout
  int timeout = 30000;      //  default 30s timeout

  void connect_to_broker ();
  void send (char * service, zmsg_t **request_p);
  zmsg_t * recv (char **command_p, char **service_p);

public:

    MajordomoClient() : Php::Base() { };
    virtual ~MajordomoClient();

    void __construct(Php::Parameters &param);
    Php::Value call(Php::Parameters &param);
    void call_async(Php::Parameters &param);

    static Php::Class<MajordomoClient> php_register() {
        Php::Class<MajordomoClient> o("Client");
        o.method("__construct", &MajordomoClient::__construct);
        o.method("call", &MajordomoClient::call);
        o.method("call_async", &MajordomoClient::call_async);
        return o;
    }

};