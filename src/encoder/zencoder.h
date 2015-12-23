#pragma once

class ZEncoder {

protected :
    Php::Value _callback;

    virtual void begin_encoding(Php::Value &v) = 0;
    virtual Php::Value end_encoding(Php::Value &v) = 0;

    virtual void begin_decoding(Php::Value &v) = 0;
    virtual Php::Value end_decoding(Php::Value &v) = 0;

    virtual void encodeArray(Php::Value &v) = 0;
    virtual void encodeMap(Php::Value &v) = 0;
    virtual void encodeObject(Php::Value &v) = 0;
    virtual void encodeString(Php::Value &v) = 0;
    virtual void encodeInteger(Php::Value &v) = 0;
    virtual void encodeBool(Php::Value &v) = 0;
    virtual void encodeDouble(Php::Value &v) = 0;
    virtual void encodeNull(Php::Value &v) = 0;
    virtual void encodeResource(Php::Value &v)= 0;

    virtual void decode_phpvalue(Php::Value &v) {

    }

    virtual void encode_phpvalue(Php::Value &v) {
        ZValue *val = (ZValue *) &v;
        if(val->isArray() && val->isHashMap()) encodeMap(v);
        else
        if(val->isArray())  encodeArray(v);
        else
        if(val->isObject()) encodeObject(v);
        else
        if(val->isString()) encodeString(v);
        else
        if(val->isBool()) encodeBool(v);
        else
        if(val->isFloat()) encodeDouble(v);
        else
        if(val->isNumeric()) encodeInteger(v);
        else
        if(val->isNull()) encodeNull(v);
        else
        if(val->isResource()) encodeResource(v);
    }

public:

    Php::Value encode(Php::Value &v) {
        Php::Value callback;
        return encode(v, callback);
    }

    Php::Value encode(Php::Value &v, Php::Value &callback) {
        _callback = callback;
        begin_encoding(v);
        encode_phpvalue(v);
        return end_encoding(v);
    }

    Php::Value decode(Php::Value &v) {
        Php::Value callback;
        return decode(v, callback);
    }

    Php::Value decode(Php::Value &v, Php::Value &callback) {
        _callback = callback;
        begin_decoding(v);
        decode_phpvalue(v);
        return end_decoding(v);
    }

};