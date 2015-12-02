#pragma once

#include "zframe.h"

class ZMsg  : public ZHandle, public Php::Base, public Php::Countable, public Php::ArrayAccess, public Php::Traversable {
public:

    ZMsg() : ZHandle(), Php::Base() {}
    ZMsg(zmsg_t *handle, bool owned) : ZHandle(handle, owned, "zmsg"), Php::Base() {}
    zmsg_t *zmsg_handle() const { return (zmsg_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        set_handle(zmsg_new(), true, "zmsg");
    }

    Php::Value send(Php::Parameters &param) {
        ZHandle *zhandle = dynamic_cast<ZHandle *>(param[0].implementation());
        zmsg_t *zmsg = zmsg_dup(zmsg_handle());
        return zmsg_send(&zmsg, zhandle->get_socket());
    }

    void remove(Php::Parameters &param) {
        ZFrame *zframe = dynamic_cast<ZFrame *>(param[0].implementation());
        if(!zframe)
            return;
        zmsg_remove(zmsg_handle(), zframe->zframe_handle());
    }

    Php::Value first() {
        zframe_t *frame = zmsg_first(zmsg_handle());
        if(!frame)
            return nullptr;
        return Php::Object("ZFrame", new ZFrame(frame, false));
    }

    Php::Value next() {
        zframe_t *frame = zmsg_next(zmsg_handle());
        if(!frame)
            return nullptr;
        return Php::Object("ZFrame", new ZFrame(frame, false));
    }

    Php::Value last() {
        zframe_t *frame = zmsg_last(zmsg_handle());
        if(!frame)
            return nullptr;
        return Php::Object("ZFrame", new ZFrame(frame, false));
    }

    void dump() {
        zmsg_print(zmsg_handle());
    }

    Php::Value append(Php::Parameters &param) {
        ZFrame *zframe  = dynamic_cast<ZFrame *>(param[0].implementation());
        zframe_t *frame = zframe_dup(zframe->zframe_handle());
        zmsg_append(zmsg_handle(), &frame);
    }

    Php::Value prepend(Php::Parameters &param) {
        ZFrame *zframe  = dynamic_cast<ZFrame *>(param[0].implementation());
        zframe_t *frame = zframe_dup(zframe->zframe_handle());
        zmsg_prepend(zmsg_handle(), &frame);
    }

    Php::Value pop() {
        zframe_t *frame = zmsg_pop(zmsg_handle());
        if(frame)
            return Php::Object("ZFrame", new ZFrame(frame, true));
        return nullptr;
    }

    void append_picture(Php::Parameters &param){
        const char *picture = param[0];
        int picture_idx = 1;

        zmsg_t *msg = zmsg_handle();

        while (*picture) {

            if (*picture == 'i')
                zmsg_addstrf (msg, "%d", (int) param[picture_idx++]);
            else
            if (*picture == '1') // PRIu8
                zmsg_addstrf (msg, "%u" , (uint8_t) (int) param[picture_idx++]);
            else
            if (*picture == '2') // PRIu16
                zmsg_addstrf (msg, "%u" , (uint16_t) (int) param[picture_idx++]);
            else
            if (*picture == '4') // PRIu32
                zmsg_addstrf (msg, "%u" , (uint32_t) (int) param[picture_idx++]);
            else
            if (*picture == '8') // PRIu64
                zmsg_addstrf (msg, "%lu" , (uint64_t) (long) param[picture_idx++]);
            else
            if (*picture == 'u')    //  Deprecated, use 4 or 8 instead
                zmsg_addstrf (msg, "%ud", (uint) (long) param[picture_idx++]);
            else
            if (*picture == 's') {
                zmsg_addstr (msg, param[picture_idx++].stringValue().substr(0, 255).c_str());
            }
            else
            if (*picture == 'S') {
                zmsg_addstr (msg, param[picture_idx++].stringValue().c_str());
            }
            else
            if (*picture == 'b') {
                const char *pointer = param[picture_idx].rawValue();
                zmsg_addmem (msg, pointer, param[picture_idx].size());
                picture_idx++;
            }
            else
    //		if (*picture == 'p') {
    //			if(streq(sock_type, "PAIR")) {
    //				void *pointer = param[picture_idx++].implementation();
    //				if(pointer != NULL) {
    //					zmsg_addmem (msg, &pointer, sizeof (void *));
    //					if(_verbose)
    //						zsys_info("address sent %p", pointer);
    //				}
    //			} else {
    //				throw Php::Exception("ZMsg picture: 'p' param not valid for socket type != PAIR.");
    //			}
    //		}
    //		else
//            if (*picture == 'c') {
//                ZChunk *zchunk = dynamic_cast<ZChunk *>(param[picture_idx++].implementation());
//                if(zchunk != NULL)
//                    zmsg_addmem (msg, zchunk_data (zchunk->zchunk_handle()), zchunk_size (zchunk->zchunk_handle()));
//                else
//                    throw Php::Exception("ZMsg picture: 'c' param not mapped on ZChunk.");
//            }
//            else
            if (*picture == 'f') {
                ZFrame *zframe = dynamic_cast<ZFrame *>(param[picture_idx++].implementation());
                if(zframe != NULL)
                    zmsg_addmem (msg, zframe_data(zframe->zframe_handle()), zframe_size(zframe->zframe_handle()));
                else
                    throw Php::Exception("ZMsg picture: 'f' param not mapped on ZFrame.");
            }
            else
//            if (*picture == 'h') {
//                ZHash *zhash = dynamic_cast<ZHash *>(param[picture_idx++].implementation());
//                if(zhash != NULL) {
//                    zframe_t *frame = zhash_pack (zhash->zhash_handle());
//                    zmsg_append (msg, &frame);
//                }
//                else
//                    throw Php::Exception("ZMsg picture: 'h' param not mapped on ZHash.");
//            }
//            else
            if (*picture == 'm') {
                ZMsg *zmsg = dynamic_cast<ZMsg *>(param[picture_idx++].implementation());
                if(zmsg != NULL) {
                    zframe_t *frame;
                    for (frame = zmsg_first (zmsg->zmsg_handle()); frame; frame = zmsg_next (zmsg->zmsg_handle()) ) {
                        zframe_t *frame_dup = zframe_dup (frame);
                        zmsg_append (msg, &frame_dup);
                    }
                }
                else
                    throw Php::Exception("ZMsg picture: 'm' param not mapped on ZMsg.");
            }
            else
            if (*picture == 'z') {
                zmsg_addmem (msg, NULL, 0);
                picture_idx++;
            }
            else
                throw Php::Exception("ZMsg picture invalid element '" + std::to_string(*picture) + "'");

            picture++;
        }

    }

    // Prepend deve invertire l'ordine della stringa con cui reperire i dati
    // (di conseguenza anche i parametri vengono risolti dall'ultimo al primo ...)
    void prepend_picture(Php::Parameters &param) {
        std::string _p = param[0].stringValue();
        _p = std::string(_p.rbegin(), _p.rend());
        const char *picture = _p.c_str();
        int picture_idx = param.size()-1;

        zmsg_t *msg = zmsg_handle();

        while (*picture) {

            if (*picture == 'i')
                zmsg_pushstrf (msg, "%d", (int) param[picture_idx--]);
            else
            if (*picture == '1') // PRIu8
                zmsg_pushstrf (msg, "%u" , (uint8_t) (int) param[picture_idx--]);
            else
            if (*picture == '2') // PRIu16
                zmsg_pushstrf (msg, "%u" , (uint16_t) (int) param[picture_idx--]);
            else
            if (*picture == '4') // PRIu32
                zmsg_pushstrf (msg, "%u" , (uint32_t) (int) param[picture_idx--]);
            else
            if (*picture == '8') // PRIu64
                zmsg_pushstrf (msg, "%lu" , (uint64_t) (long) param[picture_idx--]);
            else
            if (*picture == 'u')    //  Deprecated, use 4 or 8 instead
                zmsg_pushstrf (msg, "%ud", (uint) (long) param[picture_idx--]);
            else
            if (*picture == 's') {
                zmsg_pushstr (msg, param[picture_idx--].stringValue().substr(0, 255).c_str());
            }
            else
            if (*picture == 'S') {
                zmsg_pushstr (msg, param[picture_idx--].stringValue().c_str());
            }
            else
            if (*picture == 'b') {
                const char *pointer = param[picture_idx].rawValue();
                zmsg_pushmem (msg, pointer, param[picture_idx].size());
                picture_idx--;
            }
            else
    //		if (*picture == 'p') {
    //			if(streq(sock_type, "PAIR")) {
    //				void *pointer = param[picture_idx--].implementation();
    //				if(pointer != NULL) {
    //					zmsg_pushmem (msg, &pointer, sizeof (void *));
    //					if(_verbose)
    //						zsys_info("address sent %p", pointer);
    //				}
    //			} else {
    //				throw Php::Exception("ZMsg picture: 'p' param not valid for socket type != PAIR.");
    //			}
    //		}
    //		else
//            if (*picture == 'c') {
//                ZChunk *zchunk = dynamic_cast<ZChunk *>(param[picture_idx--].implementation());
//                if(zchunk != NULL)
//                    zmsg_pushmem (msg, zchunk_data (zchunk->zchunk_handle()), zchunk_size (zchunk->zchunk_handle()));
//                else
//                    throw Php::Exception("ZMsg picture: 'c' param not mapped on ZChunk.");
//            }
//            else
            if (*picture == 'f') {
                ZFrame *zframe = dynamic_cast<ZFrame *>(param[picture_idx--].implementation());
                if(zframe != NULL)
                    zmsg_pushmem (msg, zframe_data(zframe->zframe_handle()), zframe_size(zframe->zframe_handle()));
                else
                    throw Php::Exception("ZMsg picture: 'f' param not mapped on ZFrame.");
            }
            else
//            if (*picture == 'h') {
//                ZHash *zhash = dynamic_cast<ZHash *>(param[picture_idx--].implementation());
//                if(zhash != NULL) {
//                    zframe_t *frame = zhash_pack (zhash->zhash_handle());
//                    zmsg_prepend (msg, &frame);
//                }
//                else
//                    throw Php::Exception("ZMsg picture: 'h' param not mapped on ZHash.");
//            }
//            else
            if (*picture == 'm') {
                ZMsg *zmsg = dynamic_cast<ZMsg *>(param[picture_idx--].implementation());
                if(zmsg != NULL) {
                    zframe_t *frame;
                    for (frame = zmsg_first (zmsg->zmsg_handle()); frame; frame = zmsg_next (zmsg->zmsg_handle()) ) {
                        zframe_t *frame_dup = zframe_dup (frame);
                        zmsg_prepend (msg, &frame_dup);
                    }
                }
                else
                    throw Php::Exception("ZMsg picture: 'm' param not mapped on ZMsg.");
            }
            else
            if (*picture == 'z') {
                zmsg_pushmem (msg, NULL, 0);
                picture_idx--;
            }
            else
                throw Php::Exception("ZMsg picture invalid element '" + std::to_string(picture[0]) + "'");

            picture++;
        }

    }

    Php::Value pop_picture(Php::Parameters &param) {
        Php::Value result;
        const char *picture = param[0];
        int rc = 0;
        int idx = 0;

        zmsg_t *msg = zmsg_handle();
        if (!msg)
            return false;              //  Interrupted

        while (*picture) {
            if (*picture == 'i') {
                char *string = zmsg_popstr (msg);
                result[idx++] = (int) atol(string);
                zstr_free (&string);
            }
            else
            if (*picture == '1') {
                char *string = zmsg_popstr (msg);
                result[idx++] = (int16_t) atoi (string);
                zstr_free (&string);
            }
            else
            if (*picture == '2') {
                char *string = zmsg_popstr (msg);
                result[idx++] = (int16_t) atol (string);
                zstr_free (&string);
            }
            else
            if (*picture == '4') {
                char *string = zmsg_popstr (msg);
                result[idx++] = (int32_t) atol (string);
                zstr_free (&string);
            }
            else
            if (*picture == '8') {
                char *string = zmsg_popstr (msg);
                result[idx++] = (int64_t) atoll (string);
                zstr_free (&string);
            }
            else
            if (*picture == 'u') {  //  Deprecated, use 4 or 8 instead
                char *string = zmsg_popstr (msg);
                result[idx++] = (int64_t) atoll (string);
                zstr_free (&string);
            }
            else
            if (*picture == 's') {
                char *string = zmsg_popstr (msg);
                std::string sub = string;
                result[idx++] = sub.substr(0,255);
                zstr_free (&string);
            }
            else
            if (*picture == 'S') {
                char *string = zmsg_popstr (msg);
                result[idx++] = string;
                zstr_free (&string);
            }
            else
            if (*picture == 'b') {
                zframe_t *frame = zmsg_pop (msg);
                if(frame) {
                    Php::Value buffer;
                    int _buffer_size = zframe_size(frame);
                    buffer.reserve(_buffer_size);
                    const char *_buffer_to = buffer.rawValue();
                    byte *_buffer_from = zframe_data(frame);
                    memcpy((void *) _buffer_to, _buffer_from, _buffer_size);
                    result[idx++] = buffer;
                    zframe_destroy (&frame);
                }
                else
                    result[idx++] = nullptr;
            }
            else
            if (*picture == 'f') {
                zframe_t *frame = zmsg_pop (msg);
                if(frame)
                    result[idx++] = Php::Object("ZFrame", new ZFrame(frame, true));
                else
                    result[idx++] = nullptr;
            }
            else
//            if (*picture == 'c') {
//                zframe_t *frame = zmsg_pop (msg);
//                if(frame) {
//                    zchunk_t *chunk = zchunk_new(zframe_data (frame), zframe_size(frame));
//                    if(chunk)
//                        result[idx++] = Php::Object("ZChunk", new ZChunk(chunk,true));
//                    else
//                        result[idx++] = nullptr;
//                    zframe_destroy (&frame);
//                }
//                else
//                    result[idx++] = nullptr;
//            }
//            else
    //		if (*picture == 'p') {
    //			if(streq(sock_type,"PAIR")) {
    //				void *pointer = NULL;
    //				void *address = NULL;
    //				zframe_t *frame = zmsg_pop (msg);
    //
    //				if (frame) {
    //					if (zframe_size (frame) == sizeof (void *)) {
    //						pointer = zframe_data (frame);
    //						memcpy(&address, pointer, sizeof (void *));
    //						result[idx++] = nullptr; // &address;
    //
    //						if(_verbose)
    //							zsys_info("address recieved %p", address);
    //
    //					}
    //					else
    //						rc = -1;
    //
    //					zframe_destroy (&frame);
    //				}
    //
    //			} else {
    //				idx++;
    //				rc = -1;
    //			}
    //		}
    //		else
//            if (*picture == 'h') {
//                zframe_t *frame = zmsg_pop (msg);
//                if(frame) {
//                    zhash_t *unpacked = zhash_unpack (frame);
//                    if(unpacked)
//                        result[idx++] = Php::Object("ZHash", new ZHash(unpacked, true));
//                    else
//                        result[idx++] = nullptr;
//                    zframe_destroy (&frame);
//                }
//                else
//                    result[idx++] = nullptr;
//            }
//            else
            if (*picture == 'm') {
                zmsg_t *zmsg_p = zmsg_new ();
                zframe_t *frame;
                while ((frame = zmsg_pop (msg))) {
                    zmsg_append (zmsg_p, &frame);
                    zframe_destroy (&frame);
                }
                result[idx++] = Php::Object("ZMsg", new ZMsg(zmsg_p, true));
            }
            else
            if (*picture == 'z') {
                zframe_t *frame = zmsg_pop (msg);
                if (frame) {
                    rc = (zframe_size (frame) != 0) ? -1 : 0;
                    zframe_destroy (&frame);
                } else
                    rc = -1;

                result[idx++] = nullptr;
            }
            else
                throw Php::Exception("ZMsg picture invalid element '" + std::to_string(*picture) + "'");

            picture++;
        }

        if(rc != 0)
            return false;

        return result;
    }

    void append_string(Php::Parameters &param) {
        zmsg_addstr (zmsg_handle(), param[0].stringValue().c_str());
    }

    void prepend_string(Php::Parameters &param) {
        zmsg_pushstr (zmsg_handle(), param[0].stringValue().c_str());
    }

    Php::Value pop_string() {
        char *string = zmsg_popstr (zmsg_handle());
        if(string) {
            std::string sub = string;
            zstr_free (&string);
            return sub;
        }
        return nullptr;
    }

    Php::Value get_size() {
        return (int) zmsg_size(zmsg_handle());
    }

    Php::Value get_content_size() {
        return (int) zmsg_content_size(zmsg_handle());
    }

    Php::Value __toString() {
        if(zmsg_size(zmsg_handle()) == 0)
            return "";

        std::vector<std::string> result;

        zmsg_t *msg = zmsg_dup (zmsg_handle());
        char *str = zmsg_popstr(msg);
        while(str) {
            result.push_back(std::string(str));
            zstr_free(&str);
            str = zmsg_popstr(msg);
        }
        zmsg_destroy(&msg);

        return ZUtils::implode(result, ' ');
    }


    /**
     *  Method from the Php::Countable interface that
     *  returns the number of elements in the map
     *  @return long
     */
    virtual long count() override {
        return zmsg_size(zmsg_handle());
    }

 /**
     *  Method from the Php::ArrayAccess interface that is
     *  called to check if a certain key exists in the map
     *  @param  key
     *  @return bool
     */
    virtual bool offsetExists(const Php::Value &key) override {
        return key.isNumeric() && zmsg_size(zmsg_handle()) > key.numericValue();
    }

    /**
     *  Set a member
     *  @param  key
     *  @param  value
     */
    virtual void offsetSet(const Php::Value &key, const Php::Value &value) override {
        if(!(key.isNumeric() && zmsg_size(zmsg_handle()) > key.numericValue()))
            return;

        zframe_t *frame = zmsg_first(zmsg_handle());
        int count = key.numericValue();
        while(count && frame) {
            frame = zmsg_next(zmsg_handle());
            count--;
        }
        if(frame) {
            zmsg_t *msg = ZUtils::phpvalue_to_zmsg(value);
            if(msg) {
                zframe_t *repl = zmsg_first(msg);
                if(repl)
                    zframe_reset(frame, zframe_data(repl), zframe_size(repl));
                zmsg_destroy(&msg);
            }
        }
    }

    /**
     *  Retrieve a member
     *  @param  key
     *  @return value
     */
    virtual Php::Value offsetGet(const Php::Value &key) override {
        if(!(key.isNumeric() && zmsg_size(zmsg_handle()) > key.numericValue()))
            return nullptr;

        zframe_t *frame = zmsg_first(zmsg_handle());
        int count = key.numericValue();
        while(count && frame) {
            frame = zmsg_next(zmsg_handle());
            count--;
        }
        return Php::Object("ZFrame", new ZFrame(zframe_dup(frame), true));
    }

    /**
     *  Remove a member
     *  @param key
     */
    virtual void offsetUnset(const Php::Value &key) override {
        if(!(key.isNumeric() && zmsg_size(zmsg_handle()) > key.numericValue()))
            return;

        zframe_t *frame = zmsg_first(zmsg_handle());
        int count = key.numericValue();
        while(count && frame) {
            frame = zmsg_next(zmsg_handle());
            count--;
        }
        if(frame) {
            zmsg_remove(zmsg_handle(), frame);
            zframe_destroy(&frame);
        }
    }


    /**
     *  Get the iterator
     *  @return Php::Iterator
     */
    virtual Php::Iterator *getIterator() override {

        class ZMsgIterator : public Php::Iterator {
        private:
            ZMsg * _msg;
            Php::Value _current;
            int _current_key;
        public:

            ZMsgIterator(ZMsg *object) : Php::Iterator(object), _msg(object), _current(_msg->first()), _current_key(0) {}

            virtual ~ZMsgIterator() {}

            virtual bool valid() override { return !_current.isNull(); }

            virtual Php::Value current() override { return _current; }

            virtual Php::Value key() override { return _current_key; }

            virtual void next() override {
                _current = _msg->next();
                if(!_current.isNull())
                    _current_key++;
            }

            virtual void rewind() override {
                _current = _msg->first();
                _current_key = 0;
            }
        };

        return new ZMsgIterator(this);
    }

    static Php::Class<ZMsg> php_register() {
        Php::Class<ZMsg> o("ZMsg");
        o.method("__construct", &ZMsg::__construct);

        o.method("append_picture", &ZMsg::append_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });
        o.method("prepend_picture", &ZMsg::prepend_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });
        o.method("pop_picture", &ZMsg::pop_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });

        o.method("append", &ZMsg::append, {
            Php::ByRef("frame", "ZFrame", false, true)
        });

        o.method("prepend", &ZMsg::prepend, {
            Php::ByRef("frame", "ZFrame", false, true)
        });

        o.method("pop", &ZMsg::pop);

        o.method("append_string", &ZMsg::append_string, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("prepend_string", &ZMsg::prepend_string, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("pop_string", &ZMsg::pop_string);

        o.method("send", &ZMsg::send, {
            Php::ByRef("socket", "IZSocket", false, true)
        });

        o.method("remove", &ZMsg::remove, {
            Php::ByRef("frame", "ZFrame", false, true)
        });

        o.method("first", &ZMsg::first);
        o.method("next", &ZMsg::next);
        o.method("last", &ZMsg::last);

        o.method("get_size", &ZMsg::get_size);
        o.method("get_content_size", &ZMsg::get_content_size);

        o.method("dump", &ZMsg::dump);
        return o;
    }

};

