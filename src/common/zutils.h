#pragma once

#include <string>
#include <cstdio>
#include "zvalue.h"
#include <stdexcept>
#include <iomanip>
#include <zlib.h>

class ZUtils {
public:

    // Php Value Utils

    static zmsg_t *params_to_zmsg(const Php::Parameters &param, int start = 0, int end = -1) {
        zmsg_t *zmsg = zmsg_new();

        if(end == -1)
            end = param.size();

        for(int idx = start; idx < end; idx++) {
            zmsg_t *mm = phpvalue_to_zmsg(param[idx]);
            if(mm) {
               zframe_t *f = zmsg_pop(mm);
               while(f) {
                 zmsg_append(zmsg, &f);
                 f = zmsg_pop(mm);
               }
               zmsg_destroy(&mm);
           }
        }

        return zmsg;
    }

    static zframe_t *phpvalue_to_zframe(const Php::Value &value) {
        ZValue *val = (ZValue *) &value;
        zmsg_t *msg = val->to_zmsg();
        zframe_t *res = nullptr;
        if(msg) {
            res = zmsg_pop(msg);
            zmsg_destroy(&msg);
        }
        return res;

    }

    static zmsg_t *phpvalue_to_zmsg(const Php::Value &value) {
        ZValue *val = (ZValue *) &value;
        return val->to_zmsg();
    }

    static zmq_pollitem_t phpvalue_to_pollitem(const Php::Value &value, short event = 0) {
        ZValue *val = (ZValue *) &value;
        return val->to_pollitem(event);
    }

    static zsock_t *phpvalue_to_zsock(const Php::Value &value) {
        ZValue *val = (ZValue *) &value;
        return val->get_socket();
    }

    static int phpvalue_to_fd(const Php::Value &value) {
        ZValue *val = (ZValue *) &value;
        return val->get_fd();
    }

    static zconfig_t *phparray_to_zconfig(const Php::Value &value, std::string root) {
        zconfig_t *config = nullptr;
        if(value.isArray() && value.size()>0) {
            config = zconfig_new(root.c_str(), NULL);
            for(auto &it : value) {
                std::string path = root + "/" + it.first.stringValue();
                zconfig_put(config, path.c_str(), it.second.stringValue().c_str());
            }
        }
        return config;
    }

    // String Utils

    static std::string toUpper(const std::string& s) {
        std::string result;

        std::locale loc;
        for (unsigned int i = 0; i < s.length(); ++i)
        {
            result += std::toupper(s.at(i), loc);
        }

        return result;
    }

    static std::string toLower(const std::string& s) {
        std::string result;

        std::locale loc;
        for (unsigned int i = 0; i < s.length(); ++i)
        {
            result += std::tolower(s.at(i), loc);
        }

        return result;
    }

    static std::string hexArrayToStr(const char* info, size_t infoLength) {
        std::string result;
        for (int i = 0; i < infoLength; i++)
            result += sprintf("%02X ", info[i] & 0xFF);
        return result;
    }

    static std::vector<std::string> explode(const std::string& str, const char delimiter) {
      std::vector<std::string> elements;
      std::stringstream stream(str);
      std::string item;
      while (std::getline(stream, item, delimiter))
        elements.push_back(item);

      return elements;
    }

    static std::string implode(std::vector<std::string> & elements, char delimiter) {
      std::string full;
      for (std::vector<std::string>::iterator it = elements.begin(); it != elements.end(); ++it)
      {
        full += (*it);
        if (it != elements.end()-1)
          full += delimiter;

      }
      return full;
    }

    template<typename... Args>
    static std::string sprintf( const char* format, Args... args ) {
        int length = std::snprintf( nullptr, 0, format, args... );
        assert( length >= 0 );

        char* buf = new char[length + 1];
        std::snprintf( buf, length + 1, format, args... );

        std::string str( buf );
        delete[] buf;
        return std::move(str);
    }

    static std::string uuid (void) {
        zuuid_t *uuid = zuuid_new ();
        std::string uuidstr = zuuid_str_canonical(uuid);
        zuuid_destroy(&uuid);
        return uuidstr;
    }

    static std::string compress_string(const std::string& str, int compressionlevel = Z_BEST_COMPRESSION) {
        return compress_string(str.data(), str.size(), compressionlevel);
    }

    static std::string compress_string(const byte *str, size_t size, int compressionlevel = Z_BEST_COMPRESSION) {
        return compress_string((const char *) str, size, compressionlevel);
    }

    static std::string compress_string(const char *str, size_t size, int compressionlevel = Z_BEST_COMPRESSION) {
        z_stream zs;
        memset(&zs, 0, sizeof(zs));

        if (deflateInit(&zs, compressionlevel) != Z_OK)
            throw ( std::runtime_error("deflateInit failed while compressing.") );

        zs.next_in = (Bytef*)str;
        zs.avail_in = size;

        int ret;
        char outbuffer[32768];
        std::string outstring;

        do {
            zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
            zs.avail_out = sizeof(outbuffer);
            ret = deflate(&zs, Z_FINISH);
            if (outstring.size() < zs.total_out)
                outstring.append(outbuffer, zs.total_out - outstring.size());
        } while (ret == Z_OK);

        deflateEnd(&zs);

        if (ret != Z_STREAM_END) {
            std::ostringstream oss;
            oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
            throw ( std::runtime_error(oss.str()) );
        }

        return outstring;
    }

    static std::string decompress_string(const std::string& str) {
        return decompress_string(str.data(), str.size());
    }

    static std::string decompress_string(const byte *str, size_t size) {
        return decompress_string((const char *) str, size);
    }

    static std::string decompress_string(const char* str, size_t size) {
        z_stream zs;
        memset(&zs, 0, sizeof(zs));

        if (inflateInit(&zs) != Z_OK)
            throw ( std::runtime_error("inflateInit failed while decompressing.") );

        zs.next_in = (Bytef*)str;
        zs.avail_in = size;

        int ret;
        char outbuffer[32768];
        std::string outstring;

        do {
            zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
            zs.avail_out = sizeof(outbuffer);
            ret = inflate(&zs, 0);
            if (outstring.size() < zs.total_out)
                outstring.append(outbuffer, zs.total_out - outstring.size());
        } while (ret == Z_OK);

        inflateEnd(&zs);

        if (ret != Z_STREAM_END) {
            std::ostringstream oss;
            oss << "Exception during zlib decompression: (" << ret << ") " << zs.msg;
            throw ( std::runtime_error(oss.str()) );
        }

        return outstring;
    }

};