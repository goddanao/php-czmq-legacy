#pragma once

class ZParameters : public Php::Parameters {
public:
    ZParameters(std::vector<Php::Value> params) : Php::Parameters(NULL) {
        swap(params);
    }
};
