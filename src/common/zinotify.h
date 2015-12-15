#pragma once

#include "../common.h"

class ZInotify : public ZHandle, public Php::Base {
private:
    std::map<int,std::string> _map;

public:

    ZInotify() : ZHandle(inotify_init(), true, "fd"), Php::Base() { }

	Php::Value watch(Php::Parameters &param) {
        int wd;
	    if ((wd = inotify_add_watch (get_fd(), param[0].stringValue().c_str(), param[1].numericValue())) < 0)
	        throw new Php::Exception("failed to add watch to inotify instance");
        _map.insert({ wd, param[0].stringValue() });
        return wd;
	}

	void remove(Php::Parameters &param) {
	    auto found = _map.find(param[0].numericValue());
        if (_map.end() != found) {
            _map.erase(found);
            inotify_rm_watch(get_fd(), param[0].numericValue());
        }
	}

    Php::Value recv(Php::Parameters &param){
        char buf[sizeof(struct inotify_event) + PATH_MAX];
        int len, i, j;
        Php::Value result;
        j = 0;
        if((len = read(get_fd(), buf, sizeof(buf))) > 0) {
            i = 0;
            while (i < len) {
                struct inotify_event *ie = (struct inotify_event*) &buf[i];
                auto found = _map.find(ie->wd);
                if (_map.end() == found)
                    continue;

                result[j]["path"] = found->second;
                result[j]["evts"] = (int) ie->mask;
                j++;

                i += sizeof(struct inotify_event) + ie->len;
            }
        }

        return result;
    }

	static Php::Class<ZInotify> php_register() {
        Php::Class<ZInotify> o("ZInotify");

        o.method("watch", &ZInotify::watch, {
            Php::ByVal("file", Php::Type::String, true),
            Php::ByVal("events", Php::Type::Numeric, true)
        });
        o.method("remove", &ZInotify::remove, {
            Php::ByVal("watch_id", Php::Type::Numeric, true)
        });
        o.method("recv", &ZInotify::recv);

        o.constant("IN_ACCESS", ZUtils::sprintf("0x%08x", IN_ACCESS));
        o.constant("IN_MODIFY", ZUtils::sprintf("0x%08x", IN_MODIFY));
        o.constant("IN_ATTRIB", ZUtils::sprintf("0x%08x", IN_ATTRIB));
        o.constant("IN_CLOSE_WRITE", ZUtils::sprintf("0x%08x", IN_CLOSE_WRITE));
        o.constant("IN_CLOSE_NOWRITE", ZUtils::sprintf("0x%08x", IN_CLOSE_NOWRITE));
        o.constant("IN_OPEN", ZUtils::sprintf("0x%08x", IN_OPEN));
        o.constant("IN_MOVED_FROM", ZUtils::sprintf("0x%08x", IN_MOVED_FROM));
        o.constant("IN_MOVED_TO", ZUtils::sprintf("0x%08x", IN_MOVED_TO));
        o.constant("IN_CREATE", ZUtils::sprintf("0x%08x", IN_CREATE));
        o.constant("IN_DELETE", ZUtils::sprintf("0x%08x", IN_DELETE));
        o.constant("IN_DELETE_SELF", ZUtils::sprintf("0x%08x", IN_DELETE_SELF));
        o.constant("IN_MOVE_SELF", ZUtils::sprintf("0x%08x", IN_MOVE_SELF));

        o.constant("IN_UNMOUNT", ZUtils::sprintf("0x%08x", IN_UNMOUNT));
        o.constant("IN_Q_OVERFLOW", ZUtils::sprintf("0x%08x", IN_Q_OVERFLOW));
        o.constant("IN_IGNORED", ZUtils::sprintf("0x%08x", IN_IGNORED));

        o.constant("IN_CLOSE", ZUtils::sprintf("0x%08x", IN_CLOSE));
        o.constant("IN_MOVE", ZUtils::sprintf("0x%08x", IN_MOVE));

        o.constant("IN_ONLYDIR", ZUtils::sprintf("0x%08x", IN_ONLYDIR));
        o.constant("IN_DONT_FOLLOW", ZUtils::sprintf("0x%08x", IN_DONT_FOLLOW));
        o.constant("IN_EXCL_UNLINK", ZUtils::sprintf("0x%08x", IN_EXCL_UNLINK));
        o.constant("IN_MASK_ADD", ZUtils::sprintf("0x%08x", IN_MASK_ADD));
        o.constant("IN_ISDIR", ZUtils::sprintf("0x%08x", IN_ISDIR));

    #ifdef IN_ONESHOT
        o.constant("IN_ONESHOT", ZUtils::sprintf("0x%08x", IN_ONESHOT));
    #endif

        o.constant("IN_ALL_EVENTS", ZUtils::sprintf("0x%08x", IN_ALL_EVENTS));

        // IZDescriptor intf support
        ZHandle::register_izdescriptor((Php::Class<ZInotify> *) &o);

        return o;
    }

};