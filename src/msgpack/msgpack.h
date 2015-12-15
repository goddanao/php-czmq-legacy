#pragma once

#include <msgpack.hpp>

class MsgPack : public Php::Base  {
private:

    static void encodeArray(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk) {
        pk->pack_array(v.size());
        for (auto &iter : v) {
            Php::Value val = iter.second;
            encode_phpvalue(val, pk);
        }
    }

    static void encodeMap(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk) {
        pk->pack_map(v.size());
        for (auto &iter : v) {
            Php::Value key = iter.first;
            Php::Value val = iter.second;
            encode_phpvalue(key, pk);
            encode_phpvalue(val, pk);
        }
    }

    static void encodeObject(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk) {
        encodeMap(v, pk);
    }

    static void encodeString(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk) {
        pk->pack(v.stringValue());
    }

    static void encodeInteger(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk) {
        pk->pack(v.numericValue());
    }

    static void encodeBool(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk) {
        pk->pack(v.boolValue());
    }

    static void encodeDouble(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk) {
        pk->pack(v.floatValue());
    }

    static void encodeNull(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk) {
        pk->pack(NULL);
    }

    static void encodeResource(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk) {
        // msgpack_pack_bin(pk, size_t l);
        // msgpack_pack_bin_body(msgpack_packer* pk, const void* b, size_t l);
    }

    static void encode_phpvalue(Php::Value &v, msgpack::packer<msgpack::sbuffer> *pk) {
        ZValue *val = (ZValue *) &v;

        if(val->isArray() && val->isHashMap()) encodeMap(v, pk);
        if(val->isArray())  encodeArray(v, pk);
        if(val->isObject()) encodeObject(v, pk);
        if(val->isString()) encodeString(v, pk);
        if(val->isBool()) encodeBool(v, pk);
        if(val->isFloat()) encodeDouble(v, pk);
        if(val->isNumeric()) encodeInteger(v, pk);
        if(val->isNull()) encodeNull(v, pk);
        if(val->isResource()) encodeResource(v, pk);
    }

    static Php::Value decode_phpvalue(msgpack::object *unpacked) {
        Php::Value result;
        switch(unpacked->type) {
            case MSGPACK_OBJECT_NIL: result = nullptr; break;
            case MSGPACK_OBJECT_BOOLEAN: result = unpacked->via.boolean; break;
            case MSGPACK_OBJECT_POSITIVE_INTEGER: result = (int64_t) unpacked->via.u64; break;
            case MSGPACK_OBJECT_NEGATIVE_INTEGER: result = (int64_t) unpacked->via.i64; break;
            case MSGPACK_OBJECT_FLOAT: result = unpacked->via.f64; break;
            case MSGPACK_OBJECT_STR:
                result = Php::Value(unpacked->via.str.ptr, unpacked->via.str.size);
            break;
            case MSGPACK_OBJECT_BIN:
                result = Php::Value(unpacked->via.bin.ptr, unpacked->via.bin.size);
            break;
            case MSGPACK_OBJECT_ARRAY:
                for(int i = 0; i < unpacked->via.array.size; i++)
                    result[i] = decode_phpvalue(unpacked->via.array.ptr+i);
            break;
            case MSGPACK_OBJECT_MAP:
                for(int i = 0; i < unpacked->via.map.size; i++)
                    result[Php::Value((unpacked->via.map.ptr+i)->key.via.str.ptr,(unpacked->via.map.ptr+i)->key.via.str.size)] = decode_phpvalue(&(unpacked->via.map.ptr+i)->val);
            break;
            case MSGPACK_OBJECT_EXT: break;
        }

        return result;
    }


public:

    static Php::Value encode(Php::Parameters &param) {
        return encode(param[0]);
    }

    static Php::Value encode(Php::Value &v) {
        msgpack::sbuffer buffer;
        msgpack::packer<msgpack::sbuffer> pk(&buffer);
        encode_phpvalue(v, &pk);
        return Php::Value(buffer.data(), buffer.size());
    }

    static Php::Value decode(Php::Parameters &param) {
        return decode(param[0]);
    }

    static Php::Value decode(Php::Value &v) {
        msgpack::unpacker pac;
        pac.reserve_buffer(v.size());
        memcpy(pac.buffer(), v.rawValue(), v.size());
        pac.buffer_consumed(v.size());

        // now starts streaming deserialization.
        msgpack::unpacked unpacked_data;
        if(pac.next(&unpacked_data)) {
            msgpack::object object(unpacked_data.get());
            return decode_phpvalue(&object);
        }

        return nullptr;
    }

     static Php::Class<MsgPack> php_register() {
        Php::Class<MsgPack> o("MsgPack");
        o.method("encode", &MsgPack::encode);
        o.method("decode", &MsgPack::decode);
        return o;
    }
};