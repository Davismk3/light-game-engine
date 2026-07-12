#pragma once

#include "engine/window/window.hpp"
#include "engine/input/input.hpp"
#include "engine/input/input.hpp"
#include "engine/graphics/context/context.hpp"
#include "engine/timer/timer.hpp"
#include "engine/graphics/shader/shader.hpp"

#include <memory>

class Application {
public:
    void run();

private:
    void initialize();
    void processInput();

    void update(float& delta_time);
    void render();

    void shutdown();

    Window m_window;
    Input m_input;
    GraphicsContext m_graphics_context;
    Timer m_timer;

    // Place Additional Instances Here

    // -

    bool running;
};
