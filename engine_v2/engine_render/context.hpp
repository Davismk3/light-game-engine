#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class GraphicsContext {
public:
    void graphicsContextInitialize();

    void beginFrame();

    void beginOpaquePass();
    void beginTransparentPass();
    void beginOverlayPass();

    void endFrame();
};

/*
Use like this:

m_graphics_context.beginFrame(clear_color);

m_graphics_context.beginOpaquePass();
drawWorld();

m_graphics_context.beginTransparentPass();
drawTransparentObjectsBackToFront();

m_graphics_context.beginUiPass();
drawUi();

m_graphics_context.endFrame();
*/