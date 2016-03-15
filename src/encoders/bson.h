#pragma once

#include <bson.h>

class Bson : public Php::Base  {
private:

    static void encode_phpvalue(bson_t *curdoc, std::string &k, Php::Value &v, Php::Value &c, bool first = false) {
        ZValue *val = (ZValue *) &v;
        bool got_custom_encoder = c.isCallable();

        std::function<Php::Value(Php::Value type, Php::Value v, Php::Value a)> custom_encoder = [got_custom_encoder, &c](Php::Value type, Php::Value v, Php::Value a) {
            if(got_custom_encoder) {
                Php::Value result = c(type, v, a);
                return result.isNull() ? v : result;
            } else {
                return ZUtils::default_encoder(type, v, a);
            }
        };

        if(val->isObject() && !val->isCallable()) {
            bson_t *doc = first ? curdoc : bson_new();
            std::string classname(val->get_class_name());
            Php::Value vv = custom_encoder("object", v, { classname });

            for (auto &iter : vv) {
                std::string key = iter.first.stringValue();
                std::string classname = val->get_class_name();
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
            Php::Value vv = custom_encoder("resource", v, { });
            if(vv.isNull() || !vv.isString() || vv.size() == 0)
                bson_append_null(curdoc, k.c_str(), k.size());
            else
                bson_append_binary(curdoc, k.c_str(), k.size(), BSON_SUBTYPE_BINARY, (const uint8_t *) vv.rawValue(), vv.size());
        }
        else
        if(val->isCallable()) {
            Php::Value vv = custom_encoder("callable", v(), { });
            if(vv.isNull() || !vv.isString() || vv.size() == 0)
                bson_append_null(curdoc, k.c_str(), k.size());
            else
                bson_append_binary(curdoc, k.c_str(), k.size(), BSON_SUBTYPE_BINARY, (const uint8_t *) vv.rawValue(), vv.size());
        }
        else {
            Php::Value vv = custom_encoder("unknown type", v, { });
            if(vv.isNull() || !vv.isString() || vv.size() == 0)
                bson_append_null(curdoc, k.c_str(), k.size());
            else
                bson_append_binary(curdoc, k.c_str(), k.size(), BSON_SUBTYPE_BINARY, (const uint8_t *) vv.rawValue(), vv.size());
        }
    }

    static Php::Value decode_bson_value(bson_iter_t *iter, const bson_value_t *_value, Php::Value &c) {
        Php::Value result = nullptr;
        bool got_custom_decoder = c.isCallable();
        int idx = 0;
        bson_iter_t child_iter;

        std::function<Php::Value(int type, Php::Value v, Php::Value a)> custom_decoder = [&c, got_custom_decoder](int type, Php::Value v, Php::Value a){
            if(got_custom_decoder) {
                Php::Value res = c(type, v, a);
                return res.isNull() ? v : res;
            } else {
                return ZUtils::default_decoder(type, v, a);
            }
       };

        switch(_value->value_type) {
            case BSON_TYPE_NULL       : return custom_decoder(_value->value_type, nullptr, { });
            case BSON_TYPE_BOOL       : return custom_decoder(_value->value_type, _value->value.v_bool, { });
            case BSON_TYPE_INT32      : return custom_decoder(_value->value_type, _value->value.v_int32, { });
            case BSON_TYPE_INT64      : return custom_decoder(_value->value_type, _value->value.v_int64, { });
            case BSON_TYPE_DOUBLE     : return custom_decoder(_value->value_type, _value->value.v_double, { });
            case BSON_TYPE_CODE       : return custom_decoder(_value->value_type,  Php::Value((const char *) _value->value.v_code.code, _value->value.v_code.code_len), { });
            case BSON_TYPE_CODEWSCOPE : return custom_decoder(_value->value_type,  std::string(_value->value.v_codewscope.code, _value->value.v_codewscope.code_len), { std::string((const char *) _value->value.v_codewscope.scope_data, _value->value.v_codewscope.scope_len) });
            case BSON_TYPE_UTF8       : return custom_decoder(_value->value_type,  Php::Value((const char *) _value->value.v_utf8.str, _value->value.v_utf8.len), { });
            case BSON_TYPE_TIMESTAMP  : return custom_decoder(_value->value_type,  Php::Object("DateTime", (int) _value->value.v_timestamp.timestamp), { (int) _value->value.v_timestamp.increment });
            case BSON_TYPE_DATE_TIME  : return custom_decoder(_value->value_type,  Php::Object("DateTime", _value->value.v_datetime), { });
            case BSON_TYPE_REGEX      : return custom_decoder(_value->value_type,  std::string(_value->value.v_regex.regex, strlen(_value->value.v_regex.regex)), { std::string(_value->value.v_regex.options, strlen(_value->value.v_regex.options)) });
            case BSON_TYPE_BINARY     : return custom_decoder(_value->value_type,  Php::Value((const char *) _value->value.v_binary.data, _value->value.v_binary.data_len), { _value->value.v_binary.subtype });
            case BSON_TYPE_SYMBOL     : return custom_decoder(_value->value_type,  Php::Value((const char *) _value->value.v_symbol.symbol, _value->value.v_symbol.len), { });
            case BSON_TYPE_OID        : return custom_decoder(_value->value_type,  ZUtils::hexArrayToStr((const char *) _value->value.v_oid.bytes, 12), { });
            case BSON_TYPE_ARRAY      :
                if (bson_iter_recurse (iter, &child_iter)) {
                    while (bson_iter_next (&child_iter)) {
                        result[idx++] = decode_bson_value(&child_iter, bson_iter_value (&child_iter), c);
                   }
                }
                return custom_decoder(_value->value_type,  result, { });

            case BSON_TYPE_DOCUMENT   :
                if (bson_iter_recurse (iter, &child_iter)) {
                    while (bson_iter_next (&child_iter)) {
                        const char *_key = bson_iter_key(&child_iter);
                        result[_key] = decode_bson_value(&child_iter, bson_iter_value (&child_iter), c);
                   }
                }
                return custom_decoder(_value->value_type,  result, { });

            case BSON_TYPE_UNDEFINED  :
            case BSON_TYPE_EOD        :
            case BSON_TYPE_DBPOINTER  :
            case BSON_TYPE_MAXKEY     :
            case BSON_TYPE_MINKEY     :

            default:
                return custom_decoder(_value->value_type,  nullptr, { });

        }

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
                        result[_key] = decode_bson_value(&iter, bson_iter_value (&iter), c);
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

        // BSON TYPE
        o.constant("BSON_TYPE_UNDEFINED", ZUtils::sprintf("0x%08x", BSON_TYPE_UNDEFINED));
        o.constant("BSON_TYPE_NULL", ZUtils::sprintf("0x%08x", BSON_TYPE_NULL));
        o.constant("BSON_TYPE_BOOL", ZUtils::sprintf("0x%08x", BSON_TYPE_BOOL));
        o.constant("BSON_TYPE_INT32", ZUtils::sprintf("0x%08x", BSON_TYPE_INT32));
        o.constant("BSON_TYPE_INT64", ZUtils::sprintf("0x%08x", BSON_TYPE_INT64));
        o.constant("BSON_TYPE_DOUBLE", ZUtils::sprintf("0x%08x", BSON_TYPE_DOUBLE));
        o.constant("BSON_TYPE_CODE", ZUtils::sprintf("0x%08x", BSON_TYPE_CODE));
        o.constant("BSON_TYPE_CODEWSCOPE", ZUtils::sprintf("0x%08x", BSON_TYPE_CODEWSCOPE));
        o.constant("BSON_TYPE_UTF8", ZUtils::sprintf("0x%08x", BSON_TYPE_UTF8));
        o.constant("BSON_TYPE_TIMESTAMP", ZUtils::sprintf("0x%08x", BSON_TYPE_TIMESTAMP));
        o.constant("BSON_TYPE_DATE_TIME", ZUtils::sprintf("0x%08x", BSON_TYPE_DATE_TIME));
        o.constant("BSON_TYPE_REGEX", ZUtils::sprintf("0x%08x", BSON_TYPE_REGEX));
        o.constant("BSON_TYPE_BINARY", ZUtils::sprintf("0x%08x", BSON_TYPE_BINARY));
        o.constant("BSON_TYPE_SYMBOL", ZUtils::sprintf("0x%08x", BSON_TYPE_SYMBOL));
        o.constant("BSON_TYPE_OID", ZUtils::sprintf("0x%08x", BSON_TYPE_OID));
        o.constant("BSON_TYPE_ARRAY", ZUtils::sprintf("0x%08x", BSON_TYPE_ARRAY));
        o.constant("BSON_TYPE_DOCUMENT", ZUtils::sprintf("0x%08x", BSON_TYPE_DOCUMENT));
        o.constant("BSON_TYPE_EOD", ZUtils::sprintf("0x%08x", BSON_TYPE_EOD));
        o.constant("BSON_TYPE_DBPOINTER", ZUtils::sprintf("0x%08x", BSON_TYPE_DBPOINTER));
        o.constant("BSON_TYPE_MAXKEY", ZUtils::sprintf("0x%08x", BSON_TYPE_MAXKEY));
        o.constant("BSON_TYPE_MINKEY", ZUtils::sprintf("0x%08x", BSON_TYPE_MINKEY));

        // BSON Binary Subtypes
        o.constant("BSON_SUBTYPE_BINARY", ZUtils::sprintf("0x%08x", BSON_SUBTYPE_BINARY));
        o.constant("BSON_SUBTYPE_FUNCTION", ZUtils::sprintf("0x%08x", BSON_SUBTYPE_FUNCTION));
        o.constant("BSON_SUBTYPE_BINARY_DEPRECATED", ZUtils::sprintf("0x%08x", BSON_SUBTYPE_BINARY_DEPRECATED));
        o.constant("BSON_SUBTYPE_UUID_DEPRECATED", ZUtils::sprintf("0x%08x", BSON_SUBTYPE_UUID_DEPRECATED));
        o.constant("BSON_SUBTYPE_UUID", ZUtils::sprintf("0x%08x", BSON_SUBTYPE_UUID));
        o.constant("BSON_SUBTYPE_MD5", ZUtils::sprintf("0x%08x", BSON_SUBTYPE_MD5));
        o.constant("BSON_SUBTYPE_USER", ZUtils::sprintf("0x%08x", BSON_SUBTYPE_USER));

        return o;
    }

};