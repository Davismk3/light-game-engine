#pragma once

#include "screen.hpp"
#include "../app_controls/controls_state.hpp"
#include "../../engine_v2/engine_platform/input.hpp"
#include "../../engine_v2/engine_platform/button.hpp"
#include "../../engine_v2/engine_utility/vector.hpp"
#include "../../engine_v2/engine_render/draw.hpp"
#include "../../engine_v2/engine_render/menu.hpp"

class TitleScreen : public Screen {
public: 
    ~TitleScreen() = default;

    void initialize() override;
    void processInput(Input& input, ControlsState& controls_state) override;
    void update(float& delta_time) override;
    void render() override;
    void shutdown(ControlsState& controls_state) override;

private:
    Menu m_menu;
};
