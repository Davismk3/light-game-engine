#pragma once

#include <cstdint>
#include <string>

class Address {
public:
    Address();
    Address(const std::string& host, uint16_t port);
    // Ex: Address address("127.0.0.1", 7777);

    std::string host() const;
    uint16_t port() const;

private:
    std::string m_host;
    uint16_t m_port;
};
