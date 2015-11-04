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

  void send_to_broker (char *command, char *option, zmsg_t *msg){
      msg = msg? zmsg_dup (msg): zmsg_new ();

      //  Stack protocol envelope to start of message
      if (option)
          zmsg_pushstr (msg, option);

      zmsg_pushstr (msg, command);
      zmsg_pushstr (msg, MDPW_WORKER);
      zmsg_pushstr (msg, "");

      if (verbose) {
          zclock_log ("WORKER - I: sending %s to broker", mdpw_commands [(int) *command]);
          zmsg_dump (msg);
      }
      zmsg_send (&msg, worker);
  }

  void connect_to_broker () {
      if (worker)
          zsock_destroy (&worker);

      worker = zsock_new_dealer (broker.c_str());
      zsock_set_linger(worker, 0);

      if (verbose)
          zclock_log ("WORKER - I: connecting to broker at %s...", broker.c_str());

      //  Register service with broker
      send_to_broker (MDPW_READY, (char *) service.c_str(), NULL);

      //  If liveness hits zero, worker is considered disconnected
      liveness = HEARTBEAT_LIVENESS;
      heartbeat_at = zclock_time () + heartbeat;
  }

  void send (zmsg_t **report_p, zframe_t *reply_to) {
     assert (report_p);
     zmsg_t *report = *report_p;
     assert (report);
     assert (reply_to);
     // Add client address
     zmsg_wrap (report, zframe_dup (reply_to));
     send_to_broker (MDPW_REPORT, NULL, report);
     zmsg_destroy (report_p);
  }

  zmsg_t * recv (zframe_t **reply_to_p) {

      zpoller_t *poller = zpoller_new(worker, NULL);

      while (true) {

          zsock_t *socket = (zsock_t *) zpoller_wait(poller, heartbeat);

          if(socket) {
              zmsg_t *msg = zmsg_recv (socket);
              if (!msg)
                  break;          //  Interrupted

              if (verbose) {
                  zclock_log ("WORKER - I: received message from broker:");
                  zmsg_dump (msg);
              }

              liveness = HEARTBEAT_LIVENESS;

              //  Don't try to handle errors, just assert noisily
              assert (zmsg_size (msg) >= 3);

              zframe_t *empty = zmsg_pop (msg);
              assert (zframe_streq (empty, ""));
              zframe_destroy (&empty);

              zframe_t *header = zmsg_pop (msg);
              assert (zframe_streq (header, MDPW_WORKER));
              zframe_destroy (&header);

              zframe_t *command = zmsg_pop (msg);
              if (zframe_streq (command, MDPW_REQUEST)) {
                  //  We should pop and save as many addresses as there are
                  //  up to a null part, but for now, just save one...
                  zframe_t *reply_to = zmsg_unwrap (msg);
                  if (reply_to_p)
                      *reply_to_p = reply_to;
                  else
                      zframe_destroy (&reply_to);

                  zframe_destroy (&command);
                  //  Here is where we actually have a message to process; we
                  //  return it to the caller application

                  zpoller_destroy(&poller);

                  return msg;     //  We have a request to process
              }
              else
              if (zframe_streq (command, MDPW_HEARTBEAT))
                  ;               //  Do nothing for heartbeats
              else
              if (zframe_streq (command, MDPW_DISCONNECT))
                  connect_to_broker ();
              else {
                  zclock_log ("E: invalid input message");
                  zmsg_dump (msg);
              }
              zframe_destroy (&command);
              zmsg_destroy (&msg);
          }
          else
          if(zpoller_terminated(poller)) {
              break;
          }
          else
          if (--liveness == 0) {
              if (verbose)
                  zclock_log ("W: disconnected from broker - retrying...");
              zclock_sleep (reconnect);
              connect_to_broker ();
          }
          //  Send HEARTBEAT if it's time
          if (zclock_time () > heartbeat_at) {
              send_to_broker (MDPW_HEARTBEAT, NULL, NULL);
              heartbeat_at = zclock_time () + heartbeat;
          }
      }

      zpoller_destroy(&poller);

      if (zctx_interrupted)
          zsys_info ("W: interrupt received, killing worker...");

      return NULL;
  }



public:

    MajordomoWorker() : Php::Base() {};
    virtual ~MajordomoWorker() {
	if (worker)
        zsock_destroy (&worker);
    }

    void __construct(Php::Parameters &param) {
        if(param.size() > 0)
            verbose = (int) param[0];
    }


    void run(Php::Parameters &param) {
        if(param.size() < 3 || !param[2].isCallable())
            throw Php::Exception("MajordomoWorker: please sepcify service name, broker endpoints, a callback to recieve/process requests.");

        service = param[0].stringValue();
        broker = param[1].stringValue();

        connect_to_broker();

        while (1) {
            zframe_t *reply_to = NULL;
            zmsg_t *request = recv (&reply_to);
            if (request) {
                Php::Object zmsg("ZMsg", new ZMsg(zmsg_dup(request), true));
                Php::Value result = param[2](zmsg);

                // in funzione del tipo di risultato (ZMsg / scalar type) devo valutare come confezionare la risposta.
                if(result.isObject()) {

                }
                else
                if(result.isString()) {
                    zmsg.call("append_string", result.stringValue());
                }
                else {
                    // null value / altro da gestire qua
                }

                send (&request, reply_to);
            }
            else {
                zsys_info("Worker interrupted, recieved null request ...");
                break;              //  Worker was interrupted
            }
            if(reply_to)
                zframe_destroy (&reply_to);
        }
    }

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
