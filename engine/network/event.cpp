#include "event.hpp"

Event::Event() {
    m_event_type = EventType::None;
}

Event::Event(EventType type) {
    m_event_type = type;
}

Event::Event(EventType type, const Packet& packet) {
    m_event_type = type;
    m_packet = packet;
}

EventType Event::eventType() const {
    return m_event_type;
}

const Packet& Event::packet() const {
    return m_packet;
}

const Peer& Event::peer() const {
    return m_peer;
}
