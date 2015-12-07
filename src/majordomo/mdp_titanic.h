#pragma once

#include "../common.h"

#define TITANIC_DIR ".titanic"
#define uuid_size 37

class TitanicStorage {
public:

    virtual zmsg_t *read_request(const char *uuid) = 0;

    virtual void store_request(const char *uuid, zmsg_t *msg) = 0;

    virtual const char *status(const char *uuid)= 0;

    virtual zmsg_t *read_response(const char *uuid) = 0;

    virtual void store_response(const char *uuid, zmsg_t *msg) = 0;

    virtual void close(const char *uuid) = 0;

    virtual char *process() = 0;
};

class PhpCallbackStorage : public TitanicStorage {
private:
    Php::Value _object;
public:

    PhpCallbackStorage(Php::Value v) : _object(v) {}

    zmsg_t *read_request(const char *uuid) {
        zmsg_t *result;
        Php::Value res = _object.call("read", "request", uuid);
        if(!res.isNull()) {
            result = ZUtils::phpvalue_to_zmsg(res);
        }
        return result;
    }

    void store_request(const char *uuid, zmsg_t *msg) {
        _object.call("store", "request", uuid, Php::Object("ZMsg", new ZMsg(zmsg_dup(msg), true)));
    }

    const char * status(const char *uuid) {
        return _object.call("status", uuid);
    }

    zmsg_t *read_response(const char *uuid) {
        zmsg_t *result;
        Php::Value res = _object.call("read", "response", uuid);
        if(!res.isNull()) {
            result = ZUtils::phpvalue_to_zmsg(res);
        }
        return result;
    }

    void store_response(const char *uuid, zmsg_t *msg) {
        _object.call("store", "response", uuid, Php::Object("ZMsg", new ZMsg(zmsg_dup(msg), true)));
    }

    void close(const char *uuid) {
        _object.call("close", uuid);
    }

    char *process() {
        char *result = nullptr;
        Php::Value res = _object.call("process");
        if(!res.isNull()) {
            result = strdup(res.stringValue().c_str());
        }
        return result;
    }
};

class FileSystemStorage : public TitanicStorage {
private:

    static char *s_request_filename (const char *uuid) {
        char *filename = (char *) malloc (256);
        snprintf (filename, 256, TITANIC_DIR "/%s.req", uuid);
        return filename;
    }

    static char *s_response_filename (const char *uuid) {
        char *filename = (char *) malloc (256);
        snprintf (filename, 256, TITANIC_DIR "/%s.rep", uuid);
        return filename;
    }

public:

    zmsg_t *read_request(const char *uuid) {
        //  Ensure message directory exists
        zfile_mkdir (TITANIC_DIR);

        zmsg_t *result;
        char *filename = s_request_filename (uuid);
        FILE *file = fopen (filename, "r");
        zstr_free (&filename);
        result = zmsg_load (NULL, file);
        fclose (file);
        return result;
    }

    void store_request(const char *uuid, zmsg_t *msg) {
        //  Ensure message directory exists
        zfile_mkdir (TITANIC_DIR);

        //  Save message to disk
        char *filename = s_request_filename (uuid);
        FILE *file = fopen (filename, "w");
        zstr_free (&filename);
        zmsg_save (msg, file);
        fclose (file);

        // Add to the queue
        file = fopen (TITANIC_DIR "/queue", "a");
        fprintf (file, "-%s\n", uuid);
        fclose (file);
    }

    const char * status(const char *uuid) {
        const char* status = "400";
        char *req_filename = s_request_filename (uuid);
        char *rep_filename = s_response_filename (uuid);
        if (zfile_exists (rep_filename)) {
            status = "200";
        }
        else
        if (zfile_exists (req_filename))
            status = "300"; // Pending

        zstr_free (&req_filename);
        zstr_free (&rep_filename);

        return status;
    }

    zmsg_t *read_response(const char *uuid) {
        //  Ensure message directory exists
        zfile_mkdir (TITANIC_DIR);

        zmsg_t *result;
        char *filename = s_response_filename (uuid);
        FILE *file = fopen (filename, "r");
        zstr_free (&filename);
        result = zmsg_load (NULL, file);
        fclose (file);
        return result;
    }

    void store_response(const char *uuid, zmsg_t *msg) {
        //  Ensure message directory exists
        zfile_mkdir (TITANIC_DIR);

        //  Generate UUID and save message to disk
        char *filename = s_response_filename (uuid);
        FILE *file = fopen (filename, "w");
        zstr_free (&filename);
        zmsg_save (msg, file);
        fclose (file);
    }

    void close(const char *uuid) {
        //  Ensure message directory exists
        zfile_mkdir (TITANIC_DIR);

        char *req_filename = s_request_filename (uuid);
        char *rep_filename = s_response_filename (uuid);
        zfile_delete (req_filename);
        zfile_delete (rep_filename);
        zstr_free (&req_filename);
        zstr_free (&rep_filename);
    }

    char *process() {
        char *result = nullptr;

        //  Brute force dispatcher
        char entry [] = "?.......:.......:.......:...........:";
        FILE *file = fopen (TITANIC_DIR "/queue", "r+");
        while (file && fread (entry, uuid_size, 1, file) == 1) {
            //  UUID is prefixed with '-' if still waiting
            if (entry [0] == '-') {
                bool processed = streq(status((entry + 1)), "200");
                if (processed) {
                    //  Mark queue entry as processed
                    fseek (file, -uuid_size, SEEK_CUR);
                    fwrite ("+", 1, 1, file);
                    fseek (file, uuid_size-1, SEEK_CUR);
                } else {
                    result = strdup((entry + 1));
                    break;
                }
            }
            //  Skip end of line, LF or CRLF
            if (fgetc (file) == '\r')
                fgetc (file);
            if (zsys_interrupted)
                break;
        }
        if (file)
            fclose (file);

        return result;
    }
};

class MajordomoTitanicV2 : public ZHandle, public Php::Base  {
private:
    std::string _broker_endpoint;
    std::vector<zactor_t *> _actors;
    std::vector<mdp_client_t *> _clients;
    TitanicStorage *storage;
    zactor_t *process;

    static zmsg_t *mdcli_send(mdp_client_t *client, char *service, zmsg_t* msg, bool async = false) {
        int rc = mdp_client_request(client, service, &msg);
        if(rc == 0 && !async) {
            char *command;
            zmsg_t *body;
            rc = zsock_recv(mdp_client_msgpipe(client), "sm", &command, &body);
            if(command)
                zstr_free(&command);
            if(rc == 0)
                return body;
        }
        return nullptr;
    }

    static zmsg_t *mdwrk_recv(mdp_worker_t *worker, zmsg_t* reply) {
        if(reply != nullptr) {
            zframe_t *address = zmsg_pop(reply);
            mdp_worker_send_final(worker, &address, &reply);
        }
        char *command;
        zmsg_t *body;
        int rc = zsock_recv(mdp_worker_msgpipe(worker), "sm", &command, &body);
        if(rc == 0) {
            zstr_free(&command);
            return body;
        }
        return nullptr;
    }

    static char *s_generate_uuid (void) {
        zuuid_t *uuid = zuuid_new ();
        char *uuids = strdup(zuuid_str_canonical(uuid));
        zuuid_destroy(&uuid);
        return uuids;
    }

    static int s_service_success (char *uuid, const char *ep, TitanicStorage *storage) {

        const char *status = storage->status(uuid);
        if(streq(status, "200"))
            return 1;

        zmsg_t *request = storage->read_request(uuid);

        zframe_t *service = zmsg_pop (request);
        char *service_name = zframe_strdup (service);

        //  Create MDP client session with short timeout
        mdp_client_t *client = mdp_client_new (ep);
        // mdp_client_set_timeout (client, 1000);  //  1 sec
        // mdp_client_set_retries (client, 1);     //  only 1 retry

        zclock_sleep (200);

        //  Use MMI protocol to check if service is available
        int service_ok = 0;
        zmsg_t *mmi_request = zmsg_new ();
        zmsg_add (mmi_request, service);
        zmsg_t *mmi_reply = mdcli_send (client, "mmi.service", mmi_request);
        if(mmi_reply) {
            service_ok = (mmi_reply && zframe_streq (zmsg_first (mmi_reply), "200"));
            zmsg_destroy (&mmi_reply);
        }

        int result = 0;
        if (service_ok) {
            zmsg_t *reply = mdcli_send (client, service_name, request);
            if (reply) {
                storage->store_response(uuid, reply);
                zmsg_destroy (&reply);
                result = 1;
            }
        }
        else
            zmsg_destroy (&request);

        mdp_client_destroy (&client);
        zstr_free (&service_name);

        return result;
    }

    static void zmdp_titanic_request(zsock_t *pipe, void *args) {


        zsock_signal (pipe, 0);

        _actor_data *data = (_actor_data *)(args);
        TitanicStorage *storage = data->st();
        char *ep = (char *) data->ep;

        mdp_worker_t *worker = mdp_worker_new (ep,  "titanic.request");
        zpoller_t *poller = zpoller_new(pipe, mdp_worker_msgpipe(worker), NULL);
        zmsg_t *reply = NULL;

        while (!zsys_interrupted) {
           zsock_t *socket = (zsock_t *) zpoller_wait(poller, -1);

           if(socket == mdp_worker_msgpipe(worker)) {
                zmsg_t *request = mdwrk_recv (worker, NULL);
                zframe_t *address = zmsg_pop(request);
                char *uuid = s_generate_uuid();
                storage->store_request(uuid, request);
                zmsg_destroy(&request);

                reply = zmsg_new ();
                zmsg_addstr (reply, "200");
                zmsg_addstr (reply, uuid);
                mdp_worker_send_final(worker, &address, &reply);

           }
           else
           if(socket == pipe) {
               zmsg_t *msg;
               zsock_recv(socket, "m", &msg);
               char *command = zmsg_popstr(msg);
               bool exit = false;
               if(streq(command, "$TERM")) {
                  exit = true;
               }

               if(msg)
                    zmsg_destroy(&msg);

               if(command)
                    zstr_free(&command);

               if(exit) {
                  break;
               }
           }
           else
           if(zpoller_terminated(poller)) {
               break;
           }

        }

        delete storage;
        zpoller_destroy(&poller);
        mdp_worker_destroy (&worker);
    }

    static void zmdp_titanic_reply(zsock_t *pipe, void *args) {

        zsock_signal (pipe, 0);

        _actor_data *data = (_actor_data *)(args);
        TitanicStorage *storage = data->st();
        char *ep = (char *) data->ep;

        mdp_worker_t *worker = mdp_worker_new (ep, "titanic.reply");
        zpoller_t *poller = zpoller_new(pipe, mdp_worker_msgpipe(worker), NULL);
        zmsg_t *reply = NULL;

        while (!zsys_interrupted) {
            zsock_t *socket = (zsock_t *) zpoller_wait(poller, -1);

            if(socket == mdp_worker_msgpipe(worker)) {

                zmsg_t *request = mdwrk_recv (worker, NULL);
                zframe_t *address = zmsg_pop(request);
                char *uuid = zmsg_popstr (request);
                const char *status = storage->status(uuid);

                reply = zmsg_new ();
                zmsg_addstr (reply, status);
                zmsg_addstr (reply, uuid);
                if(streq(status, "200")) {
                   zmsg_t *rmsg = storage->read_response(uuid);
                   zmsg_addmsg(reply, &rmsg);
                }

                zmsg_destroy (&request);

                mdp_worker_send_final(worker, &address, &reply);

            }
            else
            if(socket == pipe) {
                bool exit = false;
                zmsg_t *msg;
                zsock_recv(pipe, "m", &msg);
                char *command = zmsg_popstr(msg);

                if(streq(command, "$TERM")) {
                    exit = true;
                }
                if(command)
                    zstr_free(&command);

                if(exit)
                    break;

            }
            else
            if(zpoller_terminated(poller)) {
                break;
            }
        }

        delete storage;
        zpoller_destroy(&poller);
        mdp_worker_destroy (&worker);
    }

    static void zmdp_titanic_close(zsock_t *pipe, void *args) {

        zsock_signal (pipe, 0);

        _actor_data *data = (_actor_data *)(args);
        TitanicStorage *storage = data->st();
        char *ep = (char *) data->ep;

        mdp_worker_t *worker = mdp_worker_new (ep,  "titanic.close");
        zpoller_t *poller = zpoller_new(pipe, mdp_worker_msgpipe(worker), NULL);
        zmsg_t *reply = NULL;

        while (!zsys_interrupted) {
           zsock_t *socket = (zsock_t *) zpoller_wait(poller, -1);

           if(socket == mdp_worker_msgpipe(worker)) {
                zmsg_t *request = mdwrk_recv (worker, NULL);
                zframe_t *address = zmsg_pop(request);
                char *uuid = zmsg_popstr (request);
                storage->close(uuid);

                reply = zmsg_new ();
                zmsg_addstr (reply, "200");
                zmsg_addstr (reply, uuid);
                mdp_worker_send_final(worker, &address, &reply);

                zmsg_destroy (&request);
            }
            else
            if(socket == pipe) {
                bool exit = false;
                zmsg_t *msg;
                zsock_recv(pipe, "m", &msg);
                char *command = zmsg_popstr(msg);

                if(streq(command, "$TERM")) {
                    exit = true;
                }

                if(command)
                    zstr_free(&command);

                if(exit)
                    break;

            }
            else
            if(zpoller_terminated(poller))
                break;
        }

        delete storage;
        zpoller_destroy(&poller);
        mdp_worker_destroy (&worker);
    }

    static void zmdp_titanic_process(zsock_t *pipe, void *args) {

        zsock_signal (pipe, 0);

        _actor_data *data = (_actor_data *)(args);
        TitanicStorage *storage = data->st();
        char *ep = (char *) data->ep;

        zpoller_t *poller = zpoller_new(pipe, NULL);
        zmsg_t *reply = NULL;

        while (!zsys_interrupted) {
           zsock_t *socket = (zsock_t *) zpoller_wait(poller, 1000);
           if(socket == pipe) {
                bool exit = false;
                zmsg_t *msg;
                zsock_recv(pipe, "m", &msg);
                char *command = zmsg_popstr(msg);

                if(streq(command, "$TERM")) {
                    exit = true;
                }

                if(command)
                    zstr_free(&command);

                if(exit)
                    break;

            }
            else
            if(zpoller_terminated(poller))
                break;

            // Send next request if available
            char *process = storage->process();
            if(process != nullptr) {
                int result = s_service_success(process, ep, storage);
                zstr_free(&process);
            }

        }

        delete storage;
        zpoller_destroy(&poller);
    }

    typedef struct {
        const char *ep;
        std::function<TitanicStorage*()> st;
    } _actor_data;

    _actor_data *actor_data_new(Php::Parameters &param) {
        _actor_data *data = new _actor_data();
        data->ep = _broker_endpoint.c_str();
        data->st = [param](){
            if(param.size()>1 && param[1].isObject() && !param[1].isNull()) {
                return (TitanicStorage*) new PhpCallbackStorage(param[1]);
            } else {
                return (TitanicStorage*) new FileSystemStorage();
            }
        };
        return data;
    }

public:

    MajordomoTitanicV2() : ZHandle(), Php::Base() {};

    void __construct(Php::Parameters &param) {
        _broker_endpoint = param[0].stringValue();

        int _threads = param.size()>2 ? param[2].numericValue() : 1;

        process = zactor_new(zmdp_titanic_process, (void*) actor_data_new(param));

        while(_threads > 0) {
            _actors.push_back(zactor_new(zmdp_titanic_request, (void*) actor_data_new(param)));
            _actors.push_back(zactor_new(zmdp_titanic_reply, (void*) actor_data_new(param)));
            _actors.push_back(zactor_new(zmdp_titanic_close, (void*) actor_data_new(param)));
            _threads--;
        }
    }

    virtual ~MajordomoTitanicV2(){
        for(auto it = _actors.begin() ; it < _actors.end(); it++)
            zactor_destroy(&(*it));
        if(storage)
            delete storage;
        zactor_destroy(&process);
    }

    void run(void) {

        zpoller_t *poller = zpoller_new(NULL);
        for(auto it = _actors.begin() ; it < _actors.end(); it++)
            zpoller_add(poller, *it);

        while (!zsys_interrupted) {
            void *socket = zpoller_wait(poller, 1000);
            if(zpoller_terminated(poller)) {
                zpoller_destroy(&poller);
                break;
            }
        }

        zpoller_destroy(&poller);
    }

    static Php::Class<MajordomoTitanicV2> php_register() {
        Php::Class<MajordomoTitanicV2> o("Titanic");
        o.method("__construct", &MajordomoTitanicV2::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("storage", "Majordomo\\ITitanicStorage", true, false),
            Php::ByVal("threads", Php::Type::Numeric, false)
        });
        o.method("run", &MajordomoTitanicV2::run);

        // IZSocket intf support
        o.method("get_fd", &MajordomoWorkerV2::get_fd);
        o.method("get_socket", &MajordomoWorkerV2::_get_socket);

        return o;
    }

};
