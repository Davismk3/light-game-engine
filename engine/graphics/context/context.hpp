#pragma once

class GraphicsContext {
public:
    void graphicsContextInitialize();
    void beginFrame();
    void endFrame();

    void depthWriteEnable();
    void depthWriteDisable();

    void titleScreenGraphics();
};
