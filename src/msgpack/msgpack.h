#pragma once

class MsgPack : public Php::Base  {
public:

    static Php::Value encode(Php::Parameters &param) {
        Php::Value callback = param.size()>1 && param[1].isCallable() ? param[1] : nullptr;
        return encode(param[0], callback);
    }

    static Php::Value encode(Php::Value &v) {
        Php::Value callback;
        return encode(v, callback);
    }

    static Php::Value encode(Php::Value &v, Php::Value &callback) {
        ZEncoder_MsgPack encoder;
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
        ZEncoder_MsgPack decoder;
        return decoder.decode(v, callback);
    }

    static Php::Value decode(const void* data, size_t size) {
        Php::Value val((const char*) data, size);
        Php::Value callback;
        return decode(val, callback);
    }

    static Php::Class<MsgPack> php_register() {
        Php::Class<MsgPack> o("MsgPack");
        o.method("encode", &MsgPack::encode, {
            Php::ByVal("data", Php::Type::String, true),
            Php::ByVal("encoder", Php::Type::Callable, false)
        });
        o.method("decode", &MsgPack::decode, {
            Php::ByVal("data", Php::Type::String, true),
            Php::ByVal("decoder", Php::Type::Callable, false)
        });
        return o;
    }
};