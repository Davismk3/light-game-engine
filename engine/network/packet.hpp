#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <enet/enet.h>

class Packet {
public:
    Packet();
    Packet(const std::vector<uint8_t>& bytes);
    Packet(const void* data, size_t size);

    const uint8_t* data() const;
    size_t size() const;
    bool empty() const;

private:
    std::vector<uint8_t> m_bytes;
};
