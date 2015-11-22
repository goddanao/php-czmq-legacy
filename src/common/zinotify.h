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

        o.method("watch", &ZInotify::watch);
        o.method("remove", &ZInotify::remove);
        o.method("recv", &ZInotify::recv);

        o.constant("IN_ACCESS", IN_ACCESS);
        o.constant("IN_MODIFY", IN_MODIFY);
        o.constant("IN_ATTRIB", IN_ATTRIB);
        o.constant("IN_CLOSE_WRITE", IN_CLOSE_WRITE);
        o.constant("IN_CLOSE_NOWRITE", IN_CLOSE_NOWRITE);
        o.constant("IN_OPEN", IN_OPEN);
        o.constant("IN_MOVED_FROM", IN_MOVED_FROM);
        o.constant("IN_MOVED_TO", IN_MOVED_TO);
        o.constant("IN_CREATE", IN_CREATE);
        o.constant("IN_DELETE", IN_DELETE);
        o.constant("IN_DELETE_SELF", IN_DELETE_SELF);
        o.constant("IN_MOVE_SELF", IN_MOVE_SELF);

        o.constant("IN_UNMOUNT", IN_UNMOUNT);
        o.constant("IN_Q_OVERFLOW", IN_Q_OVERFLOW);
        o.constant("IN_IGNORED", IN_IGNORED);

        o.constant("IN_CLOSE", IN_CLOSE);
        o.constant("IN_MOVE", IN_MOVE);

        o.constant("IN_ONLYDIR", IN_ONLYDIR);
        o.constant("IN_DONT_FOLLOW", IN_DONT_FOLLOW);
        o.constant("IN_EXCL_UNLINK", IN_EXCL_UNLINK);
        o.constant("IN_MASK_ADD", IN_MASK_ADD);
        o.constant("IN_ISDIR", IN_ISDIR);
        // o.constant("IN_ONESHOT", IN_ONESHOT);

        o.constant("IN_ALL_EVENTS", IN_ALL_EVENTS);

        // IZSocket intf support
        o.method("get_fd", &ZInotify::get_fd);

        return o;
    }

};