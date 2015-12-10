#pragma once

class ZEmitter {
private:
    std::map<std::string, std::vector<Php::Value>> _listeners;
    std::vector<Php::Value> _onces;

public:
    ZEmitter() { }

    virtual void on(Php::Parameters &param) {
        auto it = _listeners.find(param[0].stringValue());
        if (it == _listeners.end()) {
            _listeners.insert(std::pair<std::string, std::vector<Php::Value>>(param[0].stringValue(), std::vector<Php::Value>({param[1]})));
        } else {
            it->second.push_back(param[1]);
        }
    }

    virtual void once(Php::Parameters &param) {
        int sz = _onces.size();
        Php::Function cb([this, param, sz](Php::Parameters &pp) -> Php::Value {

            ZParameters rm_param({param[0], _onces[sz]});
            removeListener(rm_param);
            _onces.erase(_onces.begin() + sz);

            param[1](pp[0]);
            return nullptr;
        });
        _onces.push_back(cb);

        ZParameters on_param({param[0], cb});
        on(on_param);
    }

    virtual void removeListener(Php::Parameters &param) {
        auto it = _listeners.find(param[0].stringValue());
        if (it != _listeners.end()) {
            int idx = 0;
            for(Php::Value &v : it->second) {
                if(v == param[1]) {
                    it->second.erase(it->second.begin() + idx);
                    if(it->second.size() == 0) {
                        _listeners.erase(it);
                    }
                    break;
                }
                idx++;
            }
        }
    }

    virtual void removeAllListeners(Php::Parameters &param) {
        if(param.size() == 0) {
            _listeners.clear();
        } else {
            const char *event = param[0].stringValue().c_str();
            auto it = _listeners.find(param[0].stringValue());
            if (it != _listeners.end()) {
                _listeners.erase(it);
            }
        }
    }

    virtual Php::Value listeners(Php::Parameters &param) {
        Php::Value result;
        auto it = _listeners.find(param[0].stringValue());
        if (it != _listeners.end()) {
            result = it->second;
        } else {
            result = Php::Array();
        }
        return result;
    }

    virtual void emit(Php::Parameters &param) {
        auto it = _listeners.find(param[0].stringValue());
        if (it != _listeners.end()) {
            for(Php::Value &v : it->second) {
                v(param[1]);
            }
        }
    }

//    static Php::Class<ZEmitter> php_register() {
//        Php::Class<ZEmitter> o("ZEmitter");
//        o.method("on", &ZEmitter::on, {
//            Php::ByVal("event", Php::Type::String, true),
//            Php::ByVal("listener", Php::Type::Callable, true)
//        });
//        o.method("once", &ZEmitter::once, {
//            Php::ByVal("event", Php::Type::String, true),
//            Php::ByVal("listener", Php::Type::Callable, true)
//        });
//        o.method("removeListener", &ZEmitter::removeListener, {
//            Php::ByVal("event", Php::Type::String, true),
//            Php::ByVal("listener", Php::Type::Callable, true)
//        });
//        o.method("removeAllListeners", &ZEmitter::removeAllListeners, {
//            Php::ByVal("event", Php::Type::String, false)
//        });
//        o.method("listeners", &ZEmitter::listeners, {
//            Php::ByVal("event", Php::Type::String, true)
//        });
//        o.method("emit", &ZEmitter::emit, {
//            Php::ByVal("event", Php::Type::String, true),
//            Php::ByVal("arguments", Php::Type::Array, true)
//        });
//        return o;
//    }
};
