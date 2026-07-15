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
