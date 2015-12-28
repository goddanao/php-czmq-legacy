#pragma once

#include <msgpack.hpp>

class MsgPack : public Php::Base  {
private:

    static void encode_phpvalue(msgpack::packer<msgpack::sbuffer> *pk, Php::Value &v, Php::Value &c) {
        ZValue *val = (ZValue *) &v;
        bool got_custom_encoder = c.isCallable();

        std::function<Php::Value(Php::Value type, Php::Value v, Php::Value a)> custom_encoder = [got_custom_encoder, &c](Php::Value type, Php::Value v, Php::Value a) {
            if(got_custom_encoder) {
                Php::Value result = c(type, v, a);
                return result.isNull() ? v : result;
            }
            return v;
        };

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
        if(val->isObject() && !val->isCallable()) {
            ZValue *zv = (ZValue *) &v;
            std::string classname(zv->get_class_name());
            Php::Value vv = custom_encoder("object", v, { classname });

            int size = 0;
            for (auto &iter : vv) size++;

            pk->pack_map(size+1);
            pk->pack_nil();
            pk->pack(classname);

            for (auto &iter : vv) {
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
            Php::Value vv = custom_encoder("resource", v, { });
            if(vv.isNull() || !vv.isString() || vv.size() == 0)
                pk->pack_nil();
            else {
                pk->pack_bin(vv.size());
                pk->pack_bin_body(vv.rawValue(), vv.size());
            }
        }
        else
        if(val->isCallable()) {
            Php::Value vv = custom_encoder("callable", v, { });
            if(vv.isNull() || !vv.isString() || vv.size() == 0)
                pk->pack_nil();
            else {
                pk->pack_bin(vv.size());
                pk->pack_bin_body(vv.rawValue(), vv.size());
            }
        }
        else {
            Php::Value vv = custom_encoder("unknown type", v, { });
            if(vv.isNull() || !vv.isString() || vv.size() == 0)
                pk->pack_nil();
            else {
                pk->pack_bin(vv.size());
                pk->pack_bin_body(vv.rawValue(), vv.size());
            }
        }
    }

    static Php::Value decode_phpvalue(msgpack::object *unpacked, Php::Value &c) {
       Php::Value result;
       int  index = 0;
       bool got_custom_decoder = c.isCallable();
       bool decode_object = false;
       std::string classname;

       std::function<Php::Value(int type, Php::Value v, Php::Value a)> custom_decoder = [&c, got_custom_decoder](int type, Php::Value v, Php::Value a){
        if(!got_custom_decoder)
            return v;
        Php::Value res = c(type, v, a);
        return res.isNull() ? v : res;
       };

       switch(unpacked->type) {
           case MSGPACK_OBJECT_NIL: return custom_decoder(unpacked->type, nullptr, {});
           case MSGPACK_OBJECT_BOOLEAN: return custom_decoder(unpacked->type,unpacked->via.boolean, {});
           case MSGPACK_OBJECT_POSITIVE_INTEGER: return custom_decoder(unpacked->type,(int64_t) unpacked->via.u64, {});
           case MSGPACK_OBJECT_NEGATIVE_INTEGER: return custom_decoder(unpacked->type,(int64_t) unpacked->via.i64, {});
           case MSGPACK_OBJECT_FLOAT: return custom_decoder(unpacked->type,unpacked->via.f64, {});
           case MSGPACK_OBJECT_STR: return custom_decoder(unpacked->type,Php::Value(unpacked->via.str.ptr, unpacked->via.str.size), {});
           case MSGPACK_OBJECT_BIN: return custom_decoder(unpacked->type,Php::Value(unpacked->via.bin.ptr, unpacked->via.bin.size), {});
           case MSGPACK_OBJECT_ARRAY:
               for(int i = 0; i < unpacked->via.array.size; i++)
                   result[i] = decode_phpvalue(unpacked->via.array.ptr+i, c);
               return custom_decoder(unpacked->type, result, {});

           case MSGPACK_OBJECT_MAP:
               if(unpacked->via.map.ptr->key.type == MSGPACK_OBJECT_NIL) {
                   classname = std::string(unpacked->via.map.ptr->val.via.str.ptr, unpacked->via.map.ptr->val.via.str.size);
                   index = 1;
                   decode_object = !got_custom_decoder;
               }
               for(int i = index; i < unpacked->via.map.size; i++) {
                   result[Php::Value((unpacked->via.map.ptr+i)->key.via.str.ptr,(unpacked->via.map.ptr+i)->key.via.str.size)] = decode_phpvalue(&(unpacked->via.map.ptr+i)->val, c);
               }

               if(decode_object) {
                   // default object decoding
                   result = Php::Object(classname);
                   for(int i = 1; i < unpacked->via.map.size; i++)
                   result[Php::Value((unpacked->via.map.ptr+i)->key.via.str.ptr,(unpacked->via.map.ptr+i)->key.via.str.size)] = decode_phpvalue(&(unpacked->via.map.ptr+i)->val, c);
               }
               if(classname != "")
                return custom_decoder(unpacked->type, result, { classname });
               else
                return custom_decoder(unpacked->type, result, { });

           case MSGPACK_OBJECT_EXT:
               result = Php::Value(unpacked->via.ext.ptr, unpacked->via.ext.size);
               return custom_decoder(unpacked->type, result, { unpacked->via.ext.type() });

           default:
            return custom_decoder(unpacked->type, nullptr, {});
       }
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

        o.constant("MSGPACK_OBJECT_NIL", ZUtils::sprintf("0x%08x", MSGPACK_OBJECT_NIL));
        o.constant("MSGPACK_OBJECT_BOOLEAN", ZUtils::sprintf("0x%08x", MSGPACK_OBJECT_BOOLEAN));
        o.constant("MSGPACK_OBJECT_POSITIVE_INTEGER", ZUtils::sprintf("0x%08x", MSGPACK_OBJECT_POSITIVE_INTEGER));
        o.constant("MSGPACK_OBJECT_NEGATIVE_INTEGER", ZUtils::sprintf("0x%08x", MSGPACK_OBJECT_NEGATIVE_INTEGER));
        o.constant("MSGPACK_OBJECT_FLOAT", ZUtils::sprintf("0x%08x", MSGPACK_OBJECT_FLOAT));
        o.constant("MSGPACK_OBJECT_STR", ZUtils::sprintf("0x%08x", MSGPACK_OBJECT_STR));
        o.constant("MSGPACK_OBJECT_ARRAY", ZUtils::sprintf("0x%08x", MSGPACK_OBJECT_ARRAY));
        o.constant("MSGPACK_OBJECT_MAP", ZUtils::sprintf("0x%08x", MSGPACK_OBJECT_MAP));
        o.constant("MSGPACK_OBJECT_BIN", ZUtils::sprintf("0x%08x", MSGPACK_OBJECT_BIN));
        o.constant("MSGPACK_OBJECT_EXT", ZUtils::sprintf("0x%08x", MSGPACK_OBJECT_EXT));

        return o;
    }

};