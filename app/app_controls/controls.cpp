#include "controls.hpp"

void developerControls(Input& input, ScreenManager& screen_manager) {
    //if (input.inputMousePressed(MouseButton::left)) input.inputSetMouseCaptured(true);
    if (input.inputKeyPressed(Key::Escape)) input.inputSetMouseCaptured(false);
    if (input.inputKeyPressed(Key::A)) screen_manager.current_screen = ScreenType::Simulation;
    if (input.inputKeyPressed(Key::S)) screen_manager.current_screen = ScreenType::Title;
}

void userControls(Input& input, ScreenManager& screen_manager, ControlsState& controls_state) {
    if (input.inputMouseCaptured()) {
        controls_state.click_left_mouse = input.inputMousePressed(MouseButton::left);
    }
    if (controls_state.title_to_simulation) screen_manager.current_screen = ScreenType::Simulation;
    if (controls_state.simulation_to_title) screen_manager.current_screen = ScreenType::Title;
}
