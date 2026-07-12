#include "application.hpp"

void Application::initialize() {
    m_window.windowInitialize();
    m_timer.timerInitialize();
    m_graphics_context.graphicsContextInitialize();
    m_input.inputAttachWindow(m_window);

    // Place Initialization Logic Here:

    // -
}

void Application::processInput() {
    m_window.windowPollEvents();
    m_input.inputUpdate();

    // Place Input Logic Here:

    // -
}

void Application::update(float& delta_time) {

    // Place Update Logic Here:

    // -
}

void Application::render() {
    m_graphics_context.beginFrame();

    // Place Render Logic Here:

    // -

    m_graphics_context.endFrame();
}

void Application::shutdown() {

    // Place Shutdown Logic Here:
    
    // -

    m_window.windowShutdown();
}

void Application::run() {
    initialize();

    running = true;
    while (!m_window.windowShouldClose()) {
        m_timer.timerUpdate();
        float delta_time = m_timer.timerDeltaTime();

        processInput();
        update(delta_time);
        render();

        m_window.windowSwapBuffers();
    }
    shutdown();
}
