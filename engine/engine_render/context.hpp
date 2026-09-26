#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class GraphicsContext {
public:
    void graphicsContextInitialize();

    void beginFrame();

    void beginOpaquePass();
    void beginTranslucentPass();
    void beginTranslucentPassV2();
    void beginTranslucentTwoPassA();
    void beginTranslucentTwoPassB();
    void beginOverlayPass();

    void endFrame();

    void resize(int width, int height);
};