#include "address.hpp"

Address::Address()
    : m_host(""), m_port(0) {
}

Address::Address(const std::string& host, uint16_t port)
    : m_host(host), m_port(port) {
}

std::string Address::host() const {
    return m_host;
}

uint16_t Address::port() const {
    return m_port;
}
