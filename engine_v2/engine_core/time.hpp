#pragma once

#include <GLFW/glfw3.h>

class Timer {
public:
    void timerInitialize();
    void timerUpdate();
    float timerDeltaTime() const;
    float timerElapsedTime() const;

private:
    double m_start_time = 0.0;
    double m_previous_time = 0.0;
    double m_current_time = 0.0;
    float m_delta_time = 0.0f;  // double is overkill
};
