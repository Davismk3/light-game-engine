#include "screen.hpp"

#include "screen_title.hpp"
#include "screen_simulation.hpp"

void ScreenManager::changeScreen(ControlsState& controls_state) {
    if (current_screen != previous_screen) {
        if (screen_ptr) screen_ptr->shutdown(controls_state);

        switch (current_screen) {
            case ScreenType::Title:
                screen_ptr = std::make_unique<TitleScreen>();
                break;
            case ScreenType::Simulation:
                screen_ptr = std::make_unique<SimulationScreen>();
                break;
            case ScreenType::None:
                screen_ptr.reset();
                break;
        }
        if (screen_ptr) screen_ptr->initialize();

        previous_screen = current_screen;
    }
}

void ScreenManager::initialize() {
    current_screen = ScreenType::Title;
    previous_screen = current_screen;
    screen_ptr = std::make_unique<TitleScreen>();
}
