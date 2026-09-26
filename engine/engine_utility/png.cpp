#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "png.hpp"

void savePNG(const std::string& path, int width, int height, const std::vector<std::uint8_t>& rgba) {
    constexpr int channels = 4;

    if (rgba.size() != static_cast<std::size_t>(width * height * channels)) {
        throw std::runtime_error("PNG pixel-buffer size is incorrect");
    }

    std::filesystem::create_directories(std::filesystem::path(path).parent_path());

    if (!stbi_write_png(path.c_str(), width, height, channels, rgba.data(), width * channels)) {
        throw std::runtime_error("Failed to save PNG: " + path);
    }
}
