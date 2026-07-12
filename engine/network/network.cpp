#include "network.hpp"
#include <stdio.h>
#include <pthread.h>

bool Network::initialize() {
    return enet_initialize() == 0;
}

void Network::shutdown() {
    enet_deinitialize();
}
