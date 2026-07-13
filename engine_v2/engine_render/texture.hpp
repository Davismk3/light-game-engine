#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include <string>
#include <glad/gl.h>
#include <stdexcept>

class Texture {
public:
    ~Texture();
    
    void textureLoad(const std::string& path);
    void textureBind() const;
    void textureShutdown();

private:
    unsigned int m_texture_id = 0;
    int m_width = 0;
    int m_height = 0;
    int m_channels = 0;
};
