#pragma once

#include <cstdint>
#include <enet/enet.h>

#include "address.hpp"
#include "event.hpp"
#include "packet.hpp"

class Host {
public: 
    Host();
    ~Host();

    bool listen(uint16_t port);
    bool connect(const Address& address);
    bool poll(Event& event);
    void flush();
    bool disconnect();

    bool isConnected();
    bool isRunning();

    bool sendPacket(const Packet& packet);

private:
    ENetHost* m_host;
    ENetPeer* m_peer;  // LATER FIX THIS. server currently allows one peer/client, whereas later it should allow multiple clients
};
