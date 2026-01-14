#ifndef GEARX_MATH_SPHERICALCOORD_HPP
#define GEARX_MATH_SPHERICALCOORD_HPP

#include "angle_utils.hpp"

// 3次元極座標
struct SphericalCoord {
    float range;    // 半径 r
    float pitch;    // 水平方向の回転角 θ(0 ~ 2π)
    float yaw;      // 垂直方向の回転角 φ(0 ~ 2π)    
    
    SphericalCoord() 
    :range(0.0), pitch(0.0), yaw(0.0) {
    }

    SphericalCoord(float range, float pitch, float yaw)
    :range(range), pitch(pitch), yaw(yaw) {
    }

    // const float pitchDeg() const 
    // const float pitchRad() const
    // const float yawDeg() const 
    // const float yawRad() const


};


#endif
