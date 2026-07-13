#include "texture.hpp"

void Texture::textureLoad(const std::string& path) {
    textureShutdown();

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);

    if (!data) throw std::runtime_error("Failed to load texture: " + path);

    GLenum format = GL_RGB;
    if (m_channels == 4) format = GL_RGBA;
    else if (m_channels == 3) format = GL_RGB;
    else if (m_channels == 1) format = GL_RED;

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int mipmap_level = 0;

    glTexImage2D(GL_TEXTURE_2D, mipmap_level, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Texture::textureBind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::textureShutdown() {
    if (m_texture_id != 0) {
        glDeleteTextures(1, &m_texture_id);
        m_texture_id = 0;
    }
}

Texture::~Texture() {
    textureShutdown();
}
