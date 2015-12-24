#pragma once

#include <msgpack.hpp>

class MsgPack : public Php::Base  {
private:

    static void encode_phpvalue(msgpack::packer<msgpack::sbuffer> *pk, Php::Value &v, Php::Value &c) {
        ZValue *val = (ZValue *) &v;

        if(val->isArray() && val->isHashMap()) {
            pk->pack_map(v.size());
            for (auto &iter : v) {
                Php::Value key = iter.first;
                Php::Value val = iter.second;
                encode_phpvalue(pk, key, c);
                encode_phpvalue(pk, val, c);
            }
        }
        else
        if(val->isArray()) {
            pk->pack_array(v.size());
            for (auto &iter : v) {
                Php::Value val = iter.second;
                encode_phpvalue(pk, val, c);
            }
        }
        else
        if(val->isObject()) {
            ZValue *zv = (ZValue *) &v;
            bool custom_encoder = c.isCallable();
            int size = 0;
            for (auto &iter : v) size++;

            pk->pack_map(size+1);
            pk->pack_nil();
            pk->pack(zv->get_class_name());
            Php::Value iterable = custom_encoder ? c(zv->get_class_name(), v) : v;

            for (auto &iter : iterable) {
                Php::Value key = iter.first;
                Php::Value val = iter.second;
                encode_phpvalue(pk, key, c);
                encode_phpvalue(pk, val, c);
            }
        }
        else
        if(val->isString()) {
            pk->pack(v.stringValue());
        }
        else
        if(val->isBool()) {
            pk->pack(v.boolValue());
        }
        else
        if(val->isFloat()) {
            pk->pack(v.floatValue());
        }
        else
        if(val->isNumeric()) {
            pk->pack(v.numericValue());
        }
        else
        if(val->isNull()) {
            pk->pack_nil();
        }
        else
        if(val->isResource()) {
            throw Php::Exception("Can't encode Resource type.");
        }
        else
        if(val->isCallable()) {
            throw Php::Exception("Can't encode Callable type.");
        }
    }

    static Php::Value decode_phpvalue(msgpack::object *unpacked, Php::Value &c) {
       Php::Value result;
       int  index = 0;
       bool custom_decoder = c.isCallable();
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
                   result[i] = decode_phpvalue(unpacked->via.array.ptr+i, c);
           break;
           case MSGPACK_OBJECT_MAP:
               if(unpacked->via.map.ptr->key.type == MSGPACK_OBJECT_NIL) {
                   classname = Php::Value(unpacked->via.map.ptr->val.via.str.ptr, unpacked->via.map.ptr->val.via.str.size);
                   index = 1;
                   decode_object = true;
               }
               for(int i = index; i < unpacked->via.map.size; i++) {
                   result[Php::Value((unpacked->via.map.ptr+i)->key.via.str.ptr,(unpacked->via.map.ptr+i)->key.via.str.size)] = decode_phpvalue(&(unpacked->via.map.ptr+i)->val, c);
               }

               if(decode_object) {
                   if(custom_decoder) {
                       // custom object decoding
                       result = c(classname, Php::Value(result));
                   } else {
                       // default object decoding
                       result = Php::Object(classname);
                       for(int i = 1; i < unpacked->via.map.size; i++)
                           result[Php::Value((unpacked->via.map.ptr+i)->key.via.str.ptr,(unpacked->via.map.ptr+i)->key.via.str.size)] = decode_phpvalue(&(unpacked->via.map.ptr+i)->val, c);
                   }
               }

           break;
           case MSGPACK_OBJECT_EXT:
               result = Php::Value(unpacked->via.ext.ptr, unpacked->via.ext.size);
               if(custom_decoder) {
                   result = c(unpacked->via.ext.type(), Php::Value(result));
               }
           break;
       }

       return result;
   }

    static Php::Value decode_from_buffer(const void *data, size_t data_len, Php::Value &c) {
        msgpack::unpacker pac;
        msgpack::unpacked unpacked_data;

        pac.reserve_buffer(data_len);
        memcpy(pac.buffer(), data, data_len);
        pac.buffer_consumed(data_len);
        if(pac.next(&unpacked_data)) {
            msgpack::object obj(unpacked_data.get());
            return decode_phpvalue(&obj, c);
        }
        return nullptr;
    }


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
        msgpack::sbuffer buffer;
        msgpack::packer<msgpack::sbuffer> pk(&buffer);
        encode_phpvalue(&pk,v,callback);
        return Php::Value(buffer.data(), buffer.size());
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
        return decode_from_buffer(v.rawValue(), v.size(), callback);
    }

    static Php::Value decode(const void* data, size_t size) {
        Php::Value callback;
        return decode_from_buffer(data, size, callback);
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