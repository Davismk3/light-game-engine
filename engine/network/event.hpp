#pragma once

#include "packet.hpp"
#include "peer.hpp"

enum class EventType {
    None,
    Connect,
    Disconnect,
    Receive
};

class Event {
public:
    Event();
    Event(EventType type);
    Event(EventType type, const Packet& packet);

    EventType eventType() const;
    const Packet& packet() const;
    const Peer& peer() const;;

private:
    EventType m_event_type;
    Packet m_packet;
    Peer m_peer;
};
