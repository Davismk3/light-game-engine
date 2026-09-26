#pragma once

// Floor Division
template <typename T>
inline T floorDivision(T value, T divisor) {
    T quotient = value / divisor;
    T remainder = value % divisor;

    if (remainder != 0 && ((remainder < 0) != (divisor < 0))) --quotient;

    return quotient;
}

// Floor Modulus
template <typename T>
inline T floorModulus(T value, T divisor) {
    T remainder = value % divisor;
    
    if (remainder < 0) remainder += divisor;

    return remainder;
}

// Smooth Step Function
inline float smoothStep(float value) {
    if (value < 0.0f) value = 0.0f;
    else if (value > 1.0f) value = 1.0f;
    return value * value * (3.0f - 2.0f * value);
}
