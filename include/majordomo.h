#pragma once

#include "common.h"
#include "majordomo/mdp_broker.h"
#include "majordomo/mdp_worker.h"
#include "majordomo/mdp_client.h"

void php_majordomo_register(Php::Extension *extension) {

    // Majordomo
    Php::Namespace majordomo("Majordomo");

    // Majordomo Broker
    Php::Class<MajordomoBroker> mdpbroker = MajordomoBroker::php_register();
    majordomo.add(std::move(mdpbroker));

    // Majordomo Worker
    Php::Class<MajordomoWorker> mdpworker = MajordomoWorker::php_register();
    majordomo.add(std::move(mdpworker));

    // Majordomo Client
    Php::Class<MajordomoClient> mdpclient = MajordomoClient::php_register();
    majordomo.add(std::move(mdpclient));

    extension->add(std::move(majordomo));

}