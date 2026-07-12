#include "context.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

void GraphicsContext::graphicsContextInitialize() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphicsContext::beginFrame() {
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsContext::endFrame() {
    // possibly debug overlays
}

void GraphicsContext::depthWriteEnable() {
    glDepthMask(GL_TRUE);
}

void GraphicsContext::depthWriteDisable() {
    glDepthMask(GL_FALSE);
}

void GraphicsContext::titleScreenGraphics() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}
