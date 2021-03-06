#pragma once

#include "../common.h"

class ZStdIn : public ZHandle, public Php::Base {
public:
    ZStdIn() : ZHandle(STDIN_FILENO, false, "fd"), Php::Base() { }

    Php::Value recv(Php::Parameters &param){
        Php::Value result;
        result.reserve(4096);
        int num_read = read(get_fd(), (void *) result.rawValue(), 4096);
        result.reserve(num_read);
        return result;
    }

    Php::Value send(Php::Parameters &param) {
        const char *pointer = param[0].rawValue();
        return (write(get_fd(), pointer, param[0].size()) == param[0].size());
    }

	static Php::Class<ZStdIn> php_register() {
        Php::Class<ZStdIn> o("ZStdIn");
        o.method("recv", &ZStdIn::recv);
        o.method("send", &ZStdIn::send, {
            Php::ByVal("data", Php::Type::String, true)
        });

        // IZDescriptor intf support
        ZHandle::register_izdescriptor((Php::Class<ZStdIn> *) &o);

        return o;
    }

};

class ZStdOut : public ZHandle, public Php::Base {
public:
    ZStdOut() : ZHandle(STDOUT_FILENO, false, "fd"), Php::Base() { }

    Php::Value recv(Php::Parameters &param){
        Php::Value result;
        result.reserve(4096);
        int num_read = read(get_fd(), (void *) result.rawValue(), 4096);
        result.reserve(num_read);
        return result;
    }

    Php::Value send(Php::Parameters &param) {
        const char *pointer = param[0].rawValue();
        return (write(get_fd(), pointer, param[0].size()) == param[0].size());
    }

	static Php::Class<ZStdOut> php_register() {
        Php::Class<ZStdOut> o("ZStdOut");
        o.method("recv", &ZStdOut::recv);
        o.method("send", &ZStdOut::send, {
            Php::ByVal("data", Php::Type::String, true)
        });

        // IZDescriptor intf support
        ZHandle::register_izdescriptor((Php::Class<ZStdOut> *) &o);

        return o;
    }

};

class ZStdErr : public ZHandle, public Php::Base {
public:
    ZStdErr() : ZHandle(STDERR_FILENO, false, "fd"), Php::Base() { }

    Php::Value recv(Php::Parameters &param){
        Php::Value result;
        result.reserve(4096);
        int num_read = read(get_fd(), (void *) result.rawValue(), 4096);
        result.reserve(num_read);
        return result;
    }

    Php::Value send(Php::Parameters &param) {
        const char *pointer = param[0].rawValue();
        return (write(get_fd(), pointer, param[0].size()) == param[0].size());
    }

	static Php::Class<ZStdErr> php_register() {
        Php::Class<ZStdErr> o("ZStdErr");
        o.method("recv", &ZStdErr::recv);
        o.method("send", &ZStdErr::send, {
            Php::ByVal("data", Php::Type::String, true)
        });

        // IZDescriptor intf support
        ZHandle::register_izdescriptor((Php::Class<ZStdErr> *) &o);

        return o;
    }

};