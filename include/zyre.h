#pragma once

#include "zyre/zyre.h"

void php_zyre_register(Php::Extension *extension) {

    // Zyre
    Php::Class<Zyre> zyre = Zyre::php_register();
    extension->add(std::move(zyre));

}