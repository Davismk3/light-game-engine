#include "screen_title.hpp"

void TitleScreen::initialize() {
    std::cout << "at title\n";

    // Place Additional Title Initialization Logic Here:

    ButtonBounds bounds;
    bounds.height = 0.1f;
    bounds.width = 0.2f;
    bounds.u = -0.5f;
    bounds.v = -0.5f;
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

void TitleScreen::shutdown(ControlsState& controls_state) {
    controls_state.title_to_simulation = false;

    // Place Additional Title Shutdown Logic Here:

    // -
}

void TitleScreen::processInput(Input& input, ControlsState& controls_state) {

    // Place Additional Title Input Logic Here:

    m_menu.processInput(input);
    if (m_menu.m_buttons[0].isHeld(input)) {
        controls_state.title_to_simulation = true;
    }

    // -
}

void TitleScreen::update(float& delta_time) {

    // Place Additional Title Update Logic Here:

    // -
}

void TitleScreen::render() {
    
    // Place Additional Title Render Logic Here:

    drawClear(0.0f, 0.0f, 1.0f, 1.0f);
    m_menu.draw();

    // -
}
