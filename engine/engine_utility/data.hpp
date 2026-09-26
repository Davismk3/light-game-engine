#pragma once

#include "vector.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

constexpr std::uint64_t DATA_MAX_ELEMENTS = 10'000'000;

// Write binary data for numbers, booleans, and enums.
template<typename T>
inline void writeData(std::ostream& out, const T& value) {
    static_assert(std::is_arithmetic_v<T> || std::is_enum_v<T>);

    out.write(reinterpret_cast<const char*>(&value), sizeof(T));

    if (!out) throw std::runtime_error("Failed to write data.");
}

// Read binary data for numbers, booleans, and enums.
template<typename T>
inline void readData(std::istream& in, T& value) {
    static_assert(std::is_arithmetic_v<T> || std::is_enum_v<T>);

    in.read(reinterpret_cast<char*>(&value), sizeof(T));

    if (!in) throw std::runtime_error("Failed to read save data");
}

// Write binary data for std::vector<T>.
template<typename T>
inline void writeData(std::ostream& out, const std::vector<T>& values) {
    const std::uint64_t count = static_cast<std::uint64_t>(values.size());

    writeData(out, count);

    for (const T& value : values) writeData(out, value);
}

// Read binary data for std::vector<T>.
template<typename T>
inline void readData(std::istream& in, std::vector<T>& values) {
    std::uint64_t count;
    readData(in, count);

    if (count > DATA_MAX_ELEMENTS) throw std::runtime_error("Invalid vector size");

    values.clear();
    values.reserve(static_cast<std::size_t>(count));

    for (std::uint64_t i = 0; i < count; ++i) {
        T value{};
        readData(in, value);
        values.push_back(std::move(value));
    }
}

// Write binary data for std::array<T>.
template<typename T, std::size_t N>
inline void writeData(std::ostream& out, const std::array<T, N>& values) {
    for (const T& value : values) writeData(out, value);
}

// Read binary data for std::array<T>.
template<typename T, std::size_t N>
inline void readData(std::istream& in, std::array<T, N>& values) {
    for (T& value : values) readData(in, value);
}

// Write binary data for std::map<K, V>.
template<typename K, typename V>
inline void writeData(std::ostream& out, const std::map<K, V>& values) {
    const std::uint64_t count = static_cast<std::uint64_t>(values.size());

    writeData(out, count);

    for (const auto& [key, value] : values) {
        writeData(out, key);
        writeData(out, value);
    }
}

// Read binary data for std::map<K, V>.
template<typename K, typename V>
void readData(std::istream& in, std::map<K, V>& values) {
    std::uint64_t count;
    readData(in, count);

    if (count > DATA_MAX_ELEMENTS) throw std::runtime_error("Invalid map size");

    values.clear();

    for (std::uint64_t i = 0; i < count; ++i) {
        K key{};
        V value{};

        readData(in, key);
        readData(in, value);

        values.emplace(std::move(key), std::move(value));
    }
}

// Write binary data for Vector3<T>.
template<typename T>
inline void writeData(std::ostream& out, const Vector3<T>& value) {
    writeData(out, value.x);
    writeData(out, value.y);
    writeData(out, value.z);
}

// Read binary data for Vector3<T>.
template<typename T>
inline void readData(std::istream& in, Vector3<T>& value) {
    readData(in, value.x);
    readData(in, value.y);
    readData(in, value.z);
}
