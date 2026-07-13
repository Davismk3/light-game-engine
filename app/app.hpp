#pragma once

#include "../engine_v2/engine_platform/window.hpp"
#include "../engine_v2/engine_platform/input.hpp"
#include "../engine_v2/engine_render/context.hpp"
#include "../engine_v2/engine_core/time.hpp"
#include "app_controls/controls_state.hpp"
#include "app_screen/screen.hpp"
#include "app_controls/controls.hpp"

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

    // Place Additional Logic Here:

    ScreenManager m_screen_manager;
    ControlsState m_controls_state;

    // -

    bool running;
};