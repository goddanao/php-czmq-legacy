#pragma once

#include <msgpack.hpp>

class ZEncoder_MsgPack : public ZEncoder  {
private:

    // encoding
    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> *pk = nullptr;

    // decoding
    msgpack::unpacker pac;
    msgpack::unpacked unpacked_data;
    msgpack::object *obj = nullptr;

protected:

    // ENCODING

    void begin_encoding(Php::Value &v) {
        pk = new msgpack::packer<msgpack::sbuffer>(&buffer);
    }

    Php::Value end_encoding(Php::Value &v) {
        Php::Value result(buffer.data(), buffer.size());
        delete pk;
        return result;
    }

    void encodeArray(Php::Value &v) {
        pk->pack_array(v.size());
        for (auto &iter : v) {
            Php::Value val = iter.second;
            encode_phpvalue(val);
        }
    }

    void encodeMap(Php::Value &v) {
        pk->pack_map(v.size());
        for (auto &iter : v) {
            Php::Value key = iter.first;
            Php::Value val = iter.second;
            encode_phpvalue(key);
            encode_phpvalue(val);
        }
    }

    void encodeObject(Php::Value &v) {
        ZValue *zv = (ZValue *) &v;
        bool custom_encoder = _callback.isCallable();
        int size = 0;
        for (auto &iter : v) size++;

        pk->pack_map(size+1);
        pk->pack_nil();
        pk->pack(zv->get_class_name());
        Php::Value iterable = custom_encoder ? _callback(zv->get_class_name(), v) : v;

        for (auto &iter : iterable) {
            Php::Value key = iter.first;
            Php::Value val = iter.second;
            encode_phpvalue(key);
            encode_phpvalue(val);
        }
    }

    void encodeString(Php::Value &v) {
        pk->pack(v.stringValue());
    }

    void encodeInteger(Php::Value &v) {
        pk->pack(v.numericValue());
    }

    void encodeBool(Php::Value &v) {
        pk->pack(v.boolValue());
    }

    void encodeDouble(Php::Value &v) {
        pk->pack(v.floatValue());
    }

    void encodeNull(Php::Value &v) {
        pk->pack_nil();
    }

    void encodeResource(Php::Value &v) {
        // msgpack_pack_bin(pk, size_t l);
        // msgpack_pack_bin_body(msgpack_packer* pk, const void* b, size_t l);
    }

    // DECODING

    void begin_decoding(Php::Value &v) {
        pac.reserve_buffer(v.size());
        memcpy(pac.buffer(), v.rawValue(), v.size());
        pac.buffer_consumed(v.size());
        if(pac.next(&unpacked_data))
            obj = new msgpack::object(unpacked_data.get());
    }

    Php::Value end_decoding(Php::Value &v) {
        Php::Value result = nullptr;
        if(obj) {
            result = decode_phpvalue(obj);
            delete obj;
        }
        return result;
    }

    Php::Value decode_phpvalue(msgpack::object *unpacked) {
        Php::Value result;
        int  index = 0;
        bool custom_decoder = _callback.isCallable();
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
                    result[i] = decode_phpvalue(unpacked->via.array.ptr+i);
            break;
            case MSGPACK_OBJECT_MAP:
                if(unpacked->via.map.ptr->key.type == MSGPACK_OBJECT_NIL) {
                    classname = Php::Value(unpacked->via.map.ptr->val.via.str.ptr, unpacked->via.map.ptr->val.via.str.size);
                    index = 1;
                    decode_object = true;
                }
                for(int i = index; i < unpacked->via.map.size; i++) {
                    result[Php::Value((unpacked->via.map.ptr+i)->key.via.str.ptr,(unpacked->via.map.ptr+i)->key.via.str.size)] = decode_phpvalue(&(unpacked->via.map.ptr+i)->val);
                }

                if(decode_object) {
                    if(custom_decoder) {
                        // custom object decoding
                        result = _callback(classname, Php::Value(result));
                    } else {
                        // default object decoding
                        result = Php::Object(classname);
                        for(int i = 1; i < unpacked->via.map.size; i++)
                            result[Php::Value((unpacked->via.map.ptr+i)->key.via.str.ptr,(unpacked->via.map.ptr+i)->key.via.str.size)] = decode_phpvalue(&(unpacked->via.map.ptr+i)->val);
                    }
                }

            break;
            case MSGPACK_OBJECT_EXT:
                result = Php::Value(unpacked->via.ext.ptr, unpacked->via.ext.size);
                if(custom_decoder) {
                    result = _callback(unpacked->via.ext.type(), Php::Value(result));
                }
            break;
        }

        return result;
    }

};