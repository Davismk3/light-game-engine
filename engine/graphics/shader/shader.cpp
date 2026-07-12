#include <glad/gl.h>
#include "shader.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace {
    std::string loadSource(const std::filesystem::path& path) {
        std::ifstream file(path);
        if (!file) throw std::runtime_error("Failed to open shader: " + path.string());
        std::stringstream stream;
        stream << file.rdbuf();

        return stream.str();
    }
}

void Shader::shaderInitialize(const std::string& vertex_path, const std::string& fragment_path) {
    int success;
    char infoLog[512];
    
    std::string vertex_source = loadSource(vertex_path);
    std::string fragment_source = loadSource(fragment_path);

    // Vertex Shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_source_cstr = vertex_source.c_str();
    glShaderSource(vertex_shader, 1, &vertex_source_cstr, nullptr);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);  // report compile errors if any
    if(!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog); 
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment Shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_source_cstr = fragment_source.c_str();
    glShaderSource(fragment_shader, 1, &fragment_source_cstr, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);  // report compile errors if any
    if(!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog); 
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Linking
    m_shader_id = glCreateProgram();
    glAttachShader(m_shader_id, vertex_shader);
    glAttachShader(m_shader_id, fragment_shader);
    glLinkProgram(m_shader_id);
    glGetProgramiv(m_shader_id, GL_LINK_STATUS, &success);  // report linking errors if any
    if(!success) {
        glGetProgramInfoLog(m_shader_id, 512, NULL, infoLog); 
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::shaderUse() const {
    glUseProgram(m_shader_id);
}

void Shader::shaderShutdown() {
    if (m_shader_id != 0) {
        glDeleteProgram(m_shader_id);
        m_shader_id = 0;
    }
}

void Shader::shaderSetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(m_shader_id, name.c_str()), (int)value);
}

void Shader::shaderSetInt(const std::string &name, int value) const { 
    glUniform1i(glGetUniformLocation(m_shader_id, name.c_str()), value); 
}

void Shader::shaderSetFloat(const std::string &name, float value) const { 
    glUniform1f(glGetUniformLocation(m_shader_id, name.c_str()), value); 
} 

void Shader::shaderSetVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(m_shader_id, name.c_str()), x, y, z);
}

void Shader::shaderSetMat4(const std::string& name, const Matrix4F& matrix) const {
    glUniformMatrix4fv(
        glGetUniformLocation(m_shader_id, name.c_str()),
        1,
        GL_TRUE,
        matrix.matrixData()
    );
}

unsigned int Shader::shaderId() const {
    return m_shader_id;
}

Shader::~Shader() {
    shaderShutdown();
}
