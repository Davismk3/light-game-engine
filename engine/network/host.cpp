#include "host.hpp"

Host::Host() {
    m_host = nullptr;
    m_peer = nullptr;
}

Host::~Host() {
    disconnect();

    if (m_host != nullptr) {
        enet_host_destroy(m_host);
        m_host = nullptr;
    }
}

bool Host::listen(uint16_t port) {
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;

    m_host = enet_host_create(
        &address,
        32, // max clients
        2,  // channels
        0,  // incoming bandwidth, 0 = unlimited
        0   // outgoing bandwidth, 0 = unlimited
    );

    return m_host != nullptr;
}

bool Host::connect(const Address& address) {
    m_host = enet_host_create(
        nullptr,
        1, // one outgoing connection
        2,
        0,
        0
    );

    if (m_host == nullptr) return false;

    ENetAddress enetAddress;
    enet_address_set_host(&enetAddress, address.host().c_str());
    enetAddress.port = address.port();

    m_peer = enet_host_connect(m_host, &enetAddress, 2, 0);

    return m_peer != nullptr;
}

bool Host::poll(Event& event) {
    if (m_host == nullptr) {
        event = Event(EventType::None);
        return false;
    }

    ENetEvent enetEvent;

    if (enet_host_service(m_host, &enetEvent, 0) <= 0) {
        event = Event(EventType::None);
        return false;
    }

    if (enetEvent.type == ENET_EVENT_TYPE_CONNECT) {
        m_peer = enetEvent.peer;
        event = Event(EventType::Connect);
        return true;
    }

    if (enetEvent.type == ENET_EVENT_TYPE_DISCONNECT) {
        if (m_peer == enetEvent.peer) m_peer = nullptr;
        event = Event(EventType::Disconnect);
        return true;
    }

    if (enetEvent.type == ENET_EVENT_TYPE_RECEIVE) {
        Packet packet(enetEvent.packet->data, enetEvent.packet->dataLength);
        event = Event(EventType::Receive, packet);
        enet_packet_destroy(enetEvent.packet);
        return true;
    }

    event = Event(EventType::None);
    return false;
}

void Host::flush() {
    if (m_host != nullptr) enet_host_flush(m_host);
}

bool Host::disconnect() {
    if (m_peer == nullptr) return false;

    enet_peer_disconnect(m_peer, 0);
    m_peer = nullptr;

    return true;
}

bool Host::isConnected() {
    return m_peer != nullptr;
}

bool Host::isRunning() {
    return m_host != nullptr;
}

bool Host::sendPacket(const Packet& packet) {
    if (m_peer == nullptr || packet.empty()) return false;

    ENetPacket* enetPacket = enet_packet_create(
        packet.data(),
        packet.size(),
        ENET_PACKET_FLAG_RELIABLE
    );

    if (enetPacket == nullptr) return false;

    return enet_peer_send(m_peer, 0, enetPacket) == 0;
}
