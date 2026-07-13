#pragma once

#include "../../engine_v2/engine_platform/input.hpp"
#include "../app_controls/controls_state.hpp"

#include <memory>
#include <stdexcept>

enum class ScreenType {
    Title,
    Simulation,
    None
};

class Screen {
public:
    virtual ~Screen() = default;

    virtual void initialize() = 0;
    virtual void processInput(Input& input, ControlsState& controls_state) = 0;
    virtual void update(float& delta_time) = 0;
    virtual void render() = 0;
    virtual void shutdown(ControlsState& controls_state) = 0;
};

class ScreenManager {
public:
    void changeScreen(ControlsState& controls_state);
    void initialize();
    
    ScreenType current_screen;
    ScreenType previous_screen;

    std::unique_ptr<Screen> screen_ptr;
};
