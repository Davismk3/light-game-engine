#include "packet.hpp"

Packet::Packet() {
}

Packet::Packet(const std::vector<uint8_t>& bytes) {
    m_bytes = bytes;
}

Packet::Packet(const void* data, size_t size) {
    const uint8_t* bytes = static_cast<const uint8_t*>(data);
    m_bytes.assign(bytes, bytes + size);
}

const uint8_t* Packet::data() const {
    return m_bytes.data();
}

size_t Packet::size() const {
    return m_bytes.size();
}

bool Packet::empty() const {
    return m_bytes.empty();
}
