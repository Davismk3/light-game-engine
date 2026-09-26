#include "time.hpp"

void Timer::timerInitialize() {
    m_start_time = glfwGetTime();
    m_previous_time = m_start_time;
    m_current_time = m_start_time;
    m_delta_time = 0.0f;
}

void Timer::timerUpdate() {
    m_current_time = glfwGetTime();
    m_delta_time = static_cast<float>(m_current_time - m_previous_time);
    m_previous_time = m_current_time;
}

float Timer::timerDeltaTime() const {
    return m_delta_time;
}

float Timer::timerElapsedTime() const {
    return static_cast<float>(m_current_time - m_start_time);
}
