#pragma once

#include <phpcpp.h>
#include <czmq.h>
#include "zmdp_common.h"

class MajordomoWorker : public Php::Base {
private:
  std::string broker;
  std::string service;
  zsock_t *worker = NULL;       //  Socket to broker
  int verbose = 0;              //  Print activity to stdout

  //  Heartbeat management

  uint64_t heartbeat_at;        //  When to send HEARTBEAT
  size_t liveness;              //  How many attempts left
  int heartbeat = 2500;         //  Heartbeat delay, msecs
  int reconnect = 2500;         //  Reconnect delay, msecs

  void connect_to_broker ();
  void send_to_broker (char *command, char *option, zmsg_t *msg);

  void send (zmsg_t **report_p, zframe_t *reply_to);
  zmsg_t * recv (zframe_t **reply_to_p);

public:

    MajordomoWorker() : Php::Base() {};
    virtual ~MajordomoWorker();

    void __construct(Php::Parameters &param);
    void run(Php::Parameters &param);

    static Php::Class<MajordomoWorker> php_register() {
        Php::Class<MajordomoWorker> o("Worker");
        o.method("__construct", &MajordomoWorker::__construct);
        o.method("run", &MajordomoWorker::run, {
            Php::ByVal("name", Php::Type::String),
            Php::ByVal("broker", Php::Type::String),
            Php::ByVal("callback", Php::Type::Callable)
        });
        return o;
    }

};
