#pragma once

#include "screen.hpp"
#include "../app_controls/controls_state.hpp"
#include "../../engine/engine_platform/input.hpp"
#include "../../engine/engine_object/button.hpp"
#include "../../engine/engine_utility/vector.hpp"
#include "../../engine/engine_render/draw.hpp"
#include "../../engine/engine_object/menu.hpp"

class SimulationScreen : public Screen {
public: 
    ~SimulationScreen() = default;

    void initialize() override;
    void processInput(Input& input, ControlsState& controls_state) override;
    void update(float& delta_time) override;
    void render() override;
    void shutdown(ControlsState& controls_state) override;

private:
    Menu m_menu;
};
