#pragma once

#include "../engine_config.hpp"
#include "stb_image.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

struct GLFWwindow;

class Window {
public:
    void windowInitialize();
    void windowClose();
    void windowShutdown();
    
    void windowPollEvents();
    void windowSwapBuffers();
    bool windowShouldClose() const;

    GLFWwindow* windowNativeHandle() const;

private:
    GLFWwindow* m_native_handle = nullptr;  // initialize as null pointer
};
