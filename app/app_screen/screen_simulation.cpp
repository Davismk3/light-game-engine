#include "screen_simulation.hpp"

void SimulationScreen::initialize() {
    std::cout << "at simulation\n";

    // Place Additional Simulation Initialization Logic Here:

    ButtonBounds bounds;
    bounds.height = 0.1f;
    bounds.width = 0.2f;
    bounds.u = 0.5f;
    bounds.v = 0.5f;
    ButtonStyle style;
    style.held_color = {0.5f, 1.0f, 0.5f};
    style.hover_color = {0.5f, 0.75f, 0.5f};
    style.idle_color = {0.5f, 0.5f, 0.5f};
    style.opacity = 1.0f;

    m_menu.addButton(bounds, style);

    m_menu.initialize();
    m_menu.buildMesh();

    // -
}

void SimulationScreen::shutdown(ControlsState& controls_state) {
    controls_state.simulation_to_title = false;

    // Place Additional Simulation Shutdown Logic Here:

    // -
}

void SimulationScreen::processInput(Input& input, ControlsState& controls_state) {
    
    // Place Additional Simulation Input Logic Here:

    m_menu.processInput(input);
    if (m_menu.m_buttons[0].isHeld(input)) {
        controls_state.simulation_to_title = true;
    }

    // -
}

void SimulationScreen::update(float& delta_time) {

    // Place Additional Simulation Update Logic Here:

    // -
}

void SimulationScreen::render() {

    // Place Additional Simulation Render Logic Here:

    drawClear(1.0f, 0.0f, 0.0f, 1.0f);
    m_menu.draw();

    // -
}
