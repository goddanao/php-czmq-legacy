#pragma once

#include <msgpack.hpp>

class MsgPack : public Php::Base  {
private:

    static void encodeArray(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk, Php::Value &callback) {
        pk->pack_array(v.size());
        for (auto &iter : v) {
            Php::Value val = iter.second;
            encode_phpvalue(val, pk, callback);
        }
    }

    static void encodeMap(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk, Php::Value &callback) {
        pk->pack_map(v.size());
        for (auto &iter : v) {
            Php::Value key = iter.first;
            Php::Value val = iter.second;
            encode_phpvalue(key, pk, callback);
            encode_phpvalue(val, pk, callback);
        }
    }

    static void encodeObject(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk, Php::Value &callback) {
        ZValue *zv = (ZValue *) &v;
        bool custom_encoder = callback.isCallable();
        int size = 0;
        for (auto &iter : v) size++;

        pk->pack_map(size+1);
        pk->pack_nil();
        pk->pack(zv->get_class_name());
        Php::Value iterable = custom_encoder ? callback(zv->get_class_name(), v) : v;

        for (auto &iter : iterable) {
            Php::Value key = iter.first;
            Php::Value val = iter.second;
            encode_phpvalue(key, pk, callback);
            encode_phpvalue(val, pk, callback);
        }
    }

    static void encodeString(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk, Php::Value &callback) {
        pk->pack(v.stringValue());
    }

    static void encodeInteger(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk, Php::Value &callback) {
        pk->pack(v.numericValue());
    }

    static void encodeBool(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk, Php::Value &callback) {
        pk->pack(v.boolValue());
    }

    static void encodeDouble(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk, Php::Value &callback) {
        pk->pack(v.floatValue());
    }

    static void encodeNull(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk, Php::Value &callback) {
        pk->pack_nil();
    }

    static void encodeResource(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk, Php::Value &callback) {
        // msgpack_pack_bin(pk, size_t l);
        // msgpack_pack_bin_body(msgpack_packer* pk, const void* b, size_t l);
    }

    static void encode_phpvalue(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk, Php::Value &callback) {
        ZValue *val = (ZValue *) &v;

        if(val->isArray() && val->isHashMap()) encodeMap(v, pk, callback);
        if(val->isArray())  encodeArray(v, pk, callback);
        if(val->isObject()) encodeObject(v, pk, callback);
        if(val->isString()) encodeString(v, pk, callback);
        if(val->isBool()) encodeBool(v, pk, callback);
        if(val->isFloat()) encodeDouble(v, pk, callback);
        if(val->isNumeric()) encodeInteger(v, pk, callback);
        if(val->isNull()) encodeNull(v, pk, callback);
        if(val->isResource()) encodeResource(v, pk, callback);
    }

    static Php::Value decode_phpvalue(msgpack::object *unpacked, Php::Value &callback) {
        Php::Value result;
        int  index = 0;
        bool custom_decoder = callback.isCallable();
        bool decode_object = false;
        Php::Value classname;

        switch(unpacked->type) {
            case MSGPACK_OBJECT_NIL:
                result = nullptr;
            break;
            case MSGPACK_OBJECT_BOOLEAN:
                result = unpacked->via.boolean;
            break;
            case MSGPACK_OBJECT_POSITIVE_INTEGER:
                result = (int64_t) unpacked->via.u64;
            break;
            case MSGPACK_OBJECT_NEGATIVE_INTEGER:
                result = (int64_t) unpacked->via.i64;
            break;
            case MSGPACK_OBJECT_FLOAT:
                result = unpacked->via.f64;
            break;
            case MSGPACK_OBJECT_STR:
                result = Php::Value(unpacked->via.str.ptr, unpacked->via.str.size);
            break;
            case MSGPACK_OBJECT_BIN:
                result = Php::Value(unpacked->via.bin.ptr, unpacked->via.bin.size);
            break;
            case MSGPACK_OBJECT_ARRAY:
                for(int i = 0; i < unpacked->via.array.size; i++)
                    result[i] = decode_phpvalue(unpacked->via.array.ptr+i, callback);
            break;
            case MSGPACK_OBJECT_MAP:
                if(unpacked->via.map.ptr->key.type == MSGPACK_OBJECT_NIL) {
                    classname = Php::Value(unpacked->via.map.ptr->val.via.str.ptr, unpacked->via.map.ptr->val.via.str.size);
                    index = 1;
                    decode_object = true;
                }
                for(int i = index; i < unpacked->via.map.size; i++) {
                    result[Php::Value((unpacked->via.map.ptr+i)->key.via.str.ptr,(unpacked->via.map.ptr+i)->key.via.str.size)] = decode_phpvalue(&(unpacked->via.map.ptr+i)->val, callback);
                }

                if(decode_object) {
                    if(custom_decoder) {
                        // custom object decoding
                        result = callback(classname, Php::Value(result));
                    } else {
                        // default object decoding
                        result = Php::Object(classname);
                        for(int i = 1; i < unpacked->via.map.size; i++)
                            result[Php::Value((unpacked->via.map.ptr+i)->key.via.str.ptr,(unpacked->via.map.ptr+i)->key.via.str.size)] = decode_phpvalue(&(unpacked->via.map.ptr+i)->val, callback);

                    }
                }

            break;
            case MSGPACK_OBJECT_EXT:
                result = Php::Value(unpacked->via.ext.ptr, unpacked->via.ext.size);
                if(custom_decoder) {
                    result = callback(unpacked->via.ext.type(), Php::Value(result));
                }
            break;
        }

        return result;
    }


public:

    static Php::Value encode(Php::Parameters &param) {
        Php::Value callback = param.size()>1 && param[1].isCallable() ? param[1] : nullptr;
        return encode(param[0], callback);
    }

    static Php::Value encode(Php::Value &v, Php::Value &callback) {
        msgpack::sbuffer buffer;
        msgpack::packer<msgpack::sbuffer> pk(&buffer);
        encode_phpvalue(v, &pk, callback);
        return Php::Value(buffer.data(), buffer.size());
    }

    static Php::Value decode(Php::Parameters &param) {
        Php::Value callback = param.size()>1 && param[1].isCallable() ? param[1] : nullptr;
        return decode(param[0], callback);
    }

    static Php::Value decode(Php::Value &v, Php::Value &callback) {
        msgpack::unpacker pac;
        pac.reserve_buffer(v.size());
        memcpy(pac.buffer(), v.rawValue(), v.size());
        pac.buffer_consumed(v.size());

        // now starts streaming deserialization.
        msgpack::unpacked unpacked_data;
        if(pac.next(&unpacked_data)) {
            msgpack::object object(unpacked_data.get());
            return decode_phpvalue(&object, callback);
        }

        return nullptr;
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