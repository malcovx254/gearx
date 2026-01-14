#ifndef GEARX_MATH_ANGLEUTILS_HPP
#define GEARX_MATH_ANGLEUTILS_HPP

#include <cmath>

float DegToRad(float degree) {
    return degree * M_PI / 180.0;
}
float RadToDeg(float radian){
    return radian * 180.0 / M_PI;
}

float normalizeDeg(float angle) {
    float _angle =  std::fmod(angle, 360.0f);
    if (_angle == 0.0f && angle > 0.0f)
        return 360.0f;
    angle = _angle;
    if (angle < 0.0f) angle += 360.0f;
    return angle;
}

float normalizeRad(float angle) {
    // todo
    return 0.0f;
}

#endif