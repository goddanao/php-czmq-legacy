#pragma once

#include <bson.h>

class ZEncoder_BSON : public ZEncoder  {
private:

    bson_writer_t *writer;
    bson_reader_t *reader;
    bson_t *doc;
    uint8_t *buf = NULL;
    size_t buflen = 0;

    bool first;
    bson_t *curdoc;
    std::string key;

protected:

    void begin_encoding(Php::Value &v) {
       writer = bson_writer_new (&buf, &buflen, 0, bson_realloc_ctx, NULL);
       bson_writer_begin (writer, &doc);
       first = true;
       curdoc = doc;
    }

    Php::Value end_encoding(Php::Value &v) {
       bson_writer_end (writer);
       Php::Value result((const char*) buf, buflen);
       bson_writer_destroy(writer);
       bson_free (buf);
       return result;
    }

    void begin_decoding(Php::Value &v) {
        reader = bson_reader_new_from_data ((const uint8_t *) v.rawValue(), v.size());
        if(reader) {
            bool eof;
            if((doc = (bson_t *) bson_reader_read (reader, &eof))) {
                first = true;
                curdoc = doc;
            }
        }
    }

    Php::Value end_decoding(Php::Value &v) {
        Php::Value result;
        bson_iter_t iter;
        if (bson_iter_init (&iter, curdoc)) {
            while (bson_iter_next (&iter)) {
                const char *_key = bson_iter_key(&iter);
                result[_key] = decode_bson_value(&iter, bson_iter_value (&iter));
           }
        }
        if(reader)
            bson_reader_destroy (reader);
        return result;
    }

    void encodeArray(Php::Value &v) {
        std::string _key = key;
        bson_t *_curdoc = curdoc;
        int i = 0;
        bool append = !first;

        if(append)
            curdoc = bson_new();
        first = false;


        if(v.size() > 0) {
            for (auto &iter : v) {
                key = std::to_string(i++);
                Php::Value val = iter.second;
                encode_phpvalue(val);
            }
        }

        if(append) {
            bson_append_array(_curdoc, _key.c_str(), _key.size(), curdoc);
            bson_free (curdoc);
            curdoc = _curdoc;
        }
    }

    void encodeMap(Php::Value &v) {
        std::string _key = key;
        bson_t *_curdoc = curdoc;
        bool append = !first;

        if(append)
            curdoc = bson_new ();
        first = false;

        for (auto &iter : v) {
            key = iter.first.stringValue();
            Php::Value val = iter.second;
            encode_phpvalue(val);
        }

        if(append) {
            bson_append_document(_curdoc, _key.c_str(), _key.size(), curdoc);
            bson_free (curdoc);
            curdoc = _curdoc;
        }
    }

    void encodeObject(Php::Value &v) {
        encodeMap(v);
    }

    void encodeString(Php::Value &v) {
        bson_append_utf8(curdoc, key.c_str(), key.size(), v.rawValue(), v.size());
    }

    void encodeInteger(Php::Value &v) {
        bson_append_int64(curdoc, key.c_str(), key.size(), v.numericValue());
    }

    void encodeBool(Php::Value &v) {
        bson_append_bool(curdoc, key.c_str(), key.size(), v.boolValue());
    }

    void encodeDouble(Php::Value &v) {
        bson_append_double(curdoc, key.c_str(), key.size(), v.floatValue());
    }

    void encodeNull(Php::Value &v) {
        bson_append_null(curdoc, key.c_str(), key.size());
    }

    void encodeResource(Php::Value &v) {

    }

    Php::Value decode_bson_value(bson_iter_t *iter, const bson_value_t *_value) {
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

public:

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

//    static Php::Value encode_json_file(Php::Parameters &param) {
//        bson_json_reader_t *reader;
//        bson_error_t error;
//        int i = 0;
//        int b;
//
//        Php::Value result = nullptr;
//
//        if (reader = bson_json_reader_new_from_file (param[0].stringValue().c_str(), &error)) {
//            bson_t doc = BSON_INITIALIZER;
//            while ((b = bson_json_reader_read (reader, &doc, &error))) {
//                if (b > 0) {
//                    const char *data = (const char *) bson_get_data(&doc);
//                    result[i++] = Php::Value(data, doc.len);
//                    bson_reinit (&doc);
//                }
//            }
//            bson_json_reader_destroy (reader);
//            bson_destroy (&doc);
//        }
//        return i == 1 ? result[0] : result;
//    }

};