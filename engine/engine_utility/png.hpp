#pragma once

#include "stb_image_write.h"

#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

// Save a .png to a given path. The rgba must have a size of 'width * height * channels'
void savePNG(const std::string& path, int width, int height, const std::vector<std::uint8_t>& rgba);
