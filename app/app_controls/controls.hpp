#pragma once

#include "../../engine_v2/engine_platform/input.hpp"
#include "../app_controls/controls_state.hpp"
#include "../app_screen/screen.hpp"

void developerControls(Input& input, ScreenManager& screen_manager);
void userControls(Input& input, ScreenManager& screen_manager, ControlsState& controls_state);
