#pragma once

#include "../common.h"

#define TITANIC_DIR ".titanic"
#define uuid_size 37

class TitanicStorage {
public:

    zmsg_t *read_request(const char *uuid);

    void store_request(const char *uuid, zmsg_t *msg);

    const char *status(const char *uuid);

    zmsg_t *read_response(const char *uuid);

    void store_response(const char *uuid, zmsg_t *msg);

    void close(const char *uuid);

    char *process();
};

class PhpCallbackStorage : public TitanicStorage {
private:
    Php::Value _read;       //  load request callback in zmsg out id
    Php::Value _store;      //  load request callback in zmsg out id
    Php::Value _close;      //  load response callback in id out zmsg
    Php::Value _status;     //  load response callback in id out zmsg
    Php::Value _process;    //  process all pending requests

public:

    zmsg_t *read_request(const char *uuid) {
        zmsg_t *result;
        if(_read.isCallable()){
            Php::Value res = _read("request", uuid);
            if(!res.isNull()) {
                result = ZUtils::phpvalue_to_zmsg(res);
            }
        }
        return result;
    }

    void store_request(const char *uuid, zmsg_t *msg) {
        if(_store.isCallable()){
            _store("request", uuid, Php::Object("ZMsg", new ZMsg(zmsg_dup(msg), true)));
        }
    }

    const char * status(const char *uuid) {
        const char* result = "400";
        if(_status.isCallable()){
            Php::Value res = _status(uuid);
            if(!res.isNull()) {
                result = res.stringValue().c_str();
            }
        }
        return result;
    }

    zmsg_t *read_response(const char *uuid) {
        zmsg_t *result;
        if(_read.isCallable()){
            Php::Value res = _read("response", uuid);
            if(!res.isNull()) {
                result = ZUtils::phpvalue_to_zmsg(res);
            }
        }
        return result;
    }

    void store_response(const char *uuid, zmsg_t *msg) {
        if(_store.isCallable()){
            _store("response", uuid, Php::Object("ZMsg", new ZMsg(zmsg_dup(msg), true)));
        }
    }

    void close(const char *uuid) {
        if(_close.isCallable()){
            _close(uuid);
        }
    }

    char *process() {
        char *result = nullptr;
        if(_process.isCallable()){
            Php::Value res = _process();
            if(!res.isNull()) {
                result = strdup(res.stringValue().c_str());
            }
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
        zsys_info("read_request - %s", uuid);

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
        zsys_info("store_request - %s", uuid);

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
        zsys_info("status - %s", uuid);

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
        zsys_info("read_response - %s", uuid);

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
        zsys_info("store_response - %s", uuid);

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
        zsys_info("close - %s", uuid);

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
        char *result;

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
    TitanicStorage *storage;
    std::string _broker_endpoint;

    std::vector<zactor_t *> _request;
    std::vector<zactor_t *> _reply;
    std::vector<zactor_t *> _close;

    static zmsg_t *mdcli_send(mdp_client_t *client, char *service, zmsg_t* msg) {
        int rc = mdp_client_request(client, service, &msg);
        if(rc == 0) {
            char *command;
            zmsg_t *body;
            rc = zsock_recv(mdp_client_msgpipe(client), "sm", &command, &body);
            if(rc == 0) {
                zstr_free(&command);
                return body;
            }
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

    int s_service_success (char *uuid, const char *ep) {

        FileSystemStorage storage;

        const char *status = storage.status(uuid);
        if(streq(status, "200"))
            return 1;

        zmsg_t *request = storage.read_request(uuid);

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
                storage.store_response(uuid, reply);
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

    static void zmdp_titanic_request(zsock_t *pipe, void *ep) {

        FileSystemStorage storage;

        mdp_worker_t *worker = mdp_worker_new ((char *) ep, "titanic.request");
        zmsg_t *reply = NULL;

        zsock_signal (pipe, 0);
        bool firstrun = true;

        while (!zsys_interrupted) {

            zmsg_t *request = mdwrk_recv (worker, reply);
            if (!request)
                break;      //  Interrupted, exit

            // Save worker address to send back the response
            zframe_t *address = zmsg_pop(request);
            char *uuid = s_generate_uuid();

            reply = zmsg_new ();
            zmsg_push(reply, address);

            storage.store_request(uuid, request);
            zmsg_destroy (&request);
            zmsg_addstr (reply, "200");

            //  Now send UUID back to client
            //  Done by the mdwrk_recv() at the top of the loop
            zmsg_addstr (reply, uuid);

            zstr_free(&uuid);

            zsys_info("titanic.request reply");
            zmsg_dump(reply);
        }
        mdp_worker_destroy (&worker);
    }

    static void zmdp_titanic_reply(zsock_t *pipe, void *ep) {

        FileSystemStorage storage;

        mdp_worker_t *worker = mdp_worker_new ((char *) ep, "titanic.reply");
        zmsg_t *reply = NULL;

        zsock_signal (pipe, 0);

        while (!zsys_interrupted) {
            zmsg_t *request = mdwrk_recv (worker, reply);
            if (!request)
                break;      //  Interrupted, exit

            // Save worker address to send back the response
            zframe_t *address = zmsg_pop(request);
            char *uuid = zmsg_popstr (request);

            reply = zmsg_new();
            zmsg_push(reply, address);

            const char *status = storage.status(uuid);
            if(streq(status, "200")) {
                zmsg_t *msg = storage.read_response(uuid);
                zmsg_addstr (reply, "200");
                zmsg_addmsg(reply, &msg);
            }
            else {
                zmsg_addstr (reply, status);
            }

            zstr_free(&uuid);
            zmsg_destroy(&request);

            zsys_info("titanic.reply reply");
            zmsg_dump(reply);

        }
        mdp_worker_destroy (&worker);
    }

    static void zmdp_titanic_close(zsock_t *pipe, void *ep) {

        FileSystemStorage storage;

        mdp_worker_t *worker = mdp_worker_new ((char *) ep, "titanic.close");
        zmsg_t *reply = NULL;

        zsock_signal (pipe, 0);

        while (!zsys_interrupted) {
            zmsg_t *request = mdwrk_recv (worker, reply);
            if (!request)
                break;      //  Interrupted, exit

            // Save worker address to send back the response
            zframe_t *address = zmsg_pop(request);
            char *uuid = zmsg_popstr (request);

            reply = zmsg_new();
            zmsg_push(reply, address);

            storage.close(uuid);
            zmsg_addstr (reply, "200");

            zstr_free (&uuid);
            zmsg_destroy (&request);

            zsys_info("titanic.close reply");
            zmsg_dump(reply);

        }
        mdp_worker_destroy (&worker);
    }

public:

    MajordomoTitanicV2() : ZHandle(), Php::Base() {};
    // MajordomoTitanicV2(mdp_worker_t *handle, bool owned) : ZHandle(handle, owned, "mdp_worker_v2"), Php::Base() {}
    // mdp_worker_t *mdpworker_handle() const { return (mdp_worker_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        _broker_endpoint = param[0].stringValue();

        int _threads = param.size()>2 ? param[2].numericValue() : 1;
        while(_threads > 0) {
            _request.push_back(zactor_new(zmdp_titanic_request, (void*) _broker_endpoint.c_str()));
            _reply.push_back(zactor_new(zmdp_titanic_reply, (void*) _broker_endpoint.c_str()));
            _close.push_back(zactor_new(zmdp_titanic_close, (void*) _broker_endpoint.c_str()));
            _threads--;
        }
        // set_handle(mdp_worker_new(_broker_endpoint.c_str(), _name.c_str()), true, "mdp_worker_v2");
    }

    virtual ~MajordomoTitanicV2(){
        for(auto it = _request.begin() ; it < _request.end(); it++)
            zactor_destroy(&(*it));
        for(auto it = _reply.begin() ; it < _reply.end(); it++)
            zactor_destroy(&(*it));
        for(auto it = _close.begin() ; it < _close.end(); it++)
            zactor_destroy(&(*it));
    }

    void run(void) {

        FileSystemStorage storage;

        //  Main dispatcher loop
        while (!zsys_interrupted) {
            char *process = storage.process();
            if(process) {
                int result = s_service_success(process, _broker_endpoint.c_str());
                zstr_free(&process);
            } else {
                zclock_sleep(1000);
            }
        }
    }

    static Php::Class<MajordomoTitanicV2> php_register() {
        Php::Class<MajordomoTitanicV2> o("Titanic");
        o.method("__construct", &MajordomoTitanicV2::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("storage", "Majordomo\\ITitanicStorage", true, false),
            Php::ByVal("threads", Php::Type::Numeric, false)
        });
        o.method("run", &MajordomoTitanicV2::run);

//        o.method("on_store_request", &MajordomoTitanicV2::on_store_request, {
//            Php::ByVal("callback", Php::Type::Callable, true)
//        });

//        // IZSocket intf support
//        o.method("get_fd", &MajordomoWorkerV2::get_fd);
//        o.method("get_socket", &MajordomoWorkerV2::_get_socket);

        return o;
    }

};
