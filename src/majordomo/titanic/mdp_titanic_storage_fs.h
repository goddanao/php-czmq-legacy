#pragma once

#include "mdp_titanic_storage.h"

#define TITANIC_DIR ".titanic"
#define uuid_size 37

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

        #if (CZMQ_VERSION >= CZMQ_MAKE_VERSION(3,0,3))
            result = zmsg_load (file);
        #else
            result = zmsg_load (NULL, file);
        #endif

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
        #if (CZMQ_VERSION >= CZMQ_MAKE_VERSION(3,0,3))
            result = zmsg_load (file);
        #else
            result = zmsg_load (NULL, file);
        #endif
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