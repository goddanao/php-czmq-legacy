#pragma once

class Bson : public Php::Base  {
public:

    static Php::Value encode(Php::Parameters &param) {
        if(!(param[0].isObject() || param[0].isArray()))
            throw Php::Exception("BSON encoder need an object, hash or array as input");
        Php::Value callback = param.size()>1 && param[1].isCallable() ? param[1] : nullptr;
        return encode(param[0], callback);
    }

    static Php::Value encode(Php::Value &v) {
        Php::Value callback;
        return encode(v, callback);
    }

    static Php::Value encode(Php::Value &v, Php::Value &callback) {
        ZEncoder_BSON encoder;
        return encoder.encode(v, callback);
    }

    static Php::Value decode(Php::Parameters &param) {
        Php::Value callback = param.size()>1 && param[1].isCallable() ? param[1] : nullptr;
        return decode(param[0], callback);
    }

    static Php::Value decode(Php::Value &v) {
        Php::Value callback;
        return decode(v, callback);
    }

    static Php::Value decode(Php::Value &v, Php::Value &callback) {
        ZEncoder_BSON decoder;
        return decoder.decode(v, callback);
    }

    static Php::Value decode(const void* data, size_t size) {
        Php::Value val((const char*) data, size);
        Php::Value callback;
        return decode(val, callback);
    }

    static Php::Value json_to_bson(Php::Parameters &param) {
        return ZEncoder_BSON::json_to_bson(param);
    }

    static Php::Value bson_to_json(Php::Parameters &param) {
        return ZEncoder_BSON::bson_to_json(param);
    }

    static Php::Class<Bson> php_register() {
        Php::Class<Bson> o("Bson");
        o.method("encode", &Bson::encode, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("decode", &Bson::decode, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("json_to_bson", &Bson::json_to_bson, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("bson_to_json", &Bson::bson_to_json, {
            Php::ByVal("data", Php::Type::String, true)
        });
        return o;
    }
};