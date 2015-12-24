#pragma once

#include <bson.h>

class Bson : public Php::Base  {

private:

    static void encode_phpvalue(bson_t *curdoc, std::string &k, Php::Value &v, Php::Value &c, bool first = false) {
        ZValue *val = (ZValue *) &v;

        if(val->isObject()) {
            bson_t *doc = first ? curdoc : bson_new();
            for (auto &iter : v) {
                std::string key = iter.first.stringValue();
                Php::Value val = iter.second;
                encode_phpvalue(doc, key, val, c);
            }
            if(!first) {
                bson_append_document(curdoc, k.c_str(), k.size(), doc);
                bson_free (doc);
            }
        }
        else
        if((val->isArray() && val->isHashMap())) {
            bson_t *doc = first ? curdoc : bson_new();
            if(v.size() > 0) {
                for (auto &iter : v) {
                    std::string key = iter.first.stringValue();
                    Php::Value val = iter.second;
                    encode_phpvalue(doc, key, val, c);
                }
            }
            if(!first) {
                bson_append_document(curdoc, k.c_str(), k.size(), doc);
                bson_free (doc);
            }
        }
        else
        if(val->isArray()) {
            bson_t *doc = first ? curdoc : bson_new();
            if(v.size() > 0) {
                int i = 0;
                for (auto &iter : v) {
                    std::string key = std::to_string(i++);
                    Php::Value val = iter.second;
                    encode_phpvalue(doc, key, val, c);
                }
            }
            if(!first) {
                bson_append_array(curdoc, k.c_str(), k.size(), doc);
                bson_free (doc);
            }
        }
        else
        if(val->isString()) {
            bson_append_utf8(curdoc, k.c_str(), k.size(), v.rawValue(), v.size());
        }
        else
        if(val->isBool()) {
            bson_append_bool(curdoc, k.c_str(), k.size(), v.boolValue());
        }
        else
        if(val->isFloat()) {
            bson_append_double(curdoc, k.c_str(), k.size(), v.floatValue());
        }
        else
        if(val->isNumeric()) {
            bson_append_int64(curdoc, k.c_str(), k.size(), v.numericValue());
        }
        else
        if(val->isNull()) {
            bson_append_null(curdoc, k.c_str(), k.size());
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

    static Php::Value decode_bson_value(bson_iter_t *iter, const bson_value_t *_value) {
        Php::Value result = nullptr;
        int idx = 0;
        bson_iter_t child_iter;

        switch(_value->value_type) {
            case BSON_TYPE_NULL : return nullptr;
            case BSON_TYPE_BOOL : return _value->value.v_bool;
            case BSON_TYPE_INT32: return _value->value.v_int32;
            case BSON_TYPE_INT64: return _value->value.v_int64;
            case BSON_TYPE_DOUBLE: return _value->value.v_double;
            case BSON_TYPE_UTF8: return Php::Value((const char *) _value->value.v_utf8.str, _value->value.v_utf8.len);
            case BSON_TYPE_ARRAY :
                if (bson_iter_recurse (iter, &child_iter)) {
                    while (bson_iter_next (&child_iter)) {
                        result[idx++] = decode_bson_value(&child_iter, bson_iter_value (&child_iter));
                   }
                }
                return result;
            break;
            case BSON_TYPE_DOCUMENT :
                if (bson_iter_recurse (iter, &child_iter)) {
                    while (bson_iter_next (&child_iter)) {
                        const char *_key = bson_iter_key(&child_iter);
                        result[_key] = decode_bson_value(&child_iter, bson_iter_value (&child_iter));
                   }
                }
                return result;
            break;
            case BSON_TYPE_BINARY : return Php::Value((const char *) _value->value.v_binary.data, _value->value.v_binary.data_len);
        }
        return nullptr;
    }

    static Php::Value decode_from_buffer(const void *data, size_t data_len, Php::Value &c) {
        Php::Value result;

        bson_reader_t *reader = bson_reader_new_from_data ((const uint8_t *) data, data_len);
        bson_t *doc;
        bool eof;

        if(reader) {
            if((doc = (bson_t *) bson_reader_read (reader, &eof))) {
                bson_iter_t iter;
                if (bson_iter_init (&iter, doc)) {
                    while (bson_iter_next (&iter)) {
                        const char *_key = bson_iter_key(&iter);
                        result[_key] = decode_bson_value(&iter, bson_iter_value (&iter));
                   }
                }
            }
            bson_reader_destroy (reader);
        }
        return result;
    }

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
        bson_t *doc;
        uint8_t *buf = NULL;
        size_t buflen = 0;
        bson_writer_t *writer = bson_writer_new (&buf, &buflen, 0, bson_realloc_ctx, NULL);
        bson_writer_begin (writer, &doc);
        std::string key;
        encode_phpvalue(doc, key, v, callback, true);
        bson_writer_end (writer);
        Php::Value result((const char*) buf, buflen);
        bson_writer_destroy(writer);
        bson_free (buf);
        return result;
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

    static Php::Value bson_to_json(Php::Parameters &param) {
        bson_reader_t *reader;
        const bson_t *doc;
        bson_error_t error;
        bool eof;
        int i = 0;

        Php::Value result = nullptr;

        if (reader = bson_reader_new_from_data((const uint8_t *) param[0].rawValue(), param[0].size())) {
            while ((doc = bson_reader_read (reader, &eof))) {
                  char *data = bson_as_json (doc, NULL);
                  result[i++] = Php::Value(data);
                  bson_free (data);
               }
            bson_reader_destroy (reader);
        }
        return i == 1 ? result[0] : result;
    }

    static Php::Value json_to_bson(Php::Parameters &param) {
        bson_error_t error;
        bson_t *doc = bson_new_from_json ((const uint8_t *) param[0].rawValue(), param[0].size(), &error);
        Php::Value result((const char *) bson_get_data(doc), doc->len);
        bson_destroy (doc);
        return result;
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