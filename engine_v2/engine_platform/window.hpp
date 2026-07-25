#pragma once

#include "../engine_config.hpp"
#include "stb_image.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

struct GLFWwindow;

struct FramebufferExtent {
    int width = 0;
    int height = 0;
};

class Window {
public:
    void windowInitialize();
    void windowClose();
    void windowShutdown();
    
    void windowPollEvents();
    void windowSwapBuffers();
    bool windowShouldClose() const;

    GLFWwindow* windowNativeHandle() const;
    bool windowConsumeFramebufferResize(FramebufferExtent& extent);

    FramebufferExtent m_framebuffer_extent;
    bool m_framebuffer_resized = false;

private:
    GLFWwindow* m_native_handle = nullptr;  // initialize as null pointer
};
