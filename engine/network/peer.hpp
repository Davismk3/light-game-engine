#pragma once

#include "packet.hpp"

class Peer {
public:
    bool isConnected() const;
    void disconnect();
    bool send(const Packet& packet);

private:
};