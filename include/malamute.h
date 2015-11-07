#pragma once

#include "common.h"
#include "malamute/malamute_broker.h"
#include "malamute/malamute_client.h"

void php_malamute_register(Php::Extension *extension) {

    // Malamute Broker
    Php::Class<MalamuteBroker> broker = MalamuteBroker::php_register();
    extension->add(std::move(broker));

    // Malamute Client
    Php::Class<MalamuteClient> client = MalamuteClient::php_register();
    extension->add(std::move(client));

}