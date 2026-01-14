#include "coord_utils.hpp"

float dist2(Vec2 &pos1, Vec2 &pos2) {
    return std::sqrt( std::abs(pos1.x-pos2.x) + std::abs(pos1.y-pos2.y) );
}

float dist3(Vec3 &pos1, Vec3 &pos2) {
    return std::sqrt( std::abs(pos1.x-pos2.x) + std::abs(pos1.y-pos2.y) + std::abs(pos1.z-pos2.z) );
}

template <Vec3> 
Vec3 coord_cast(const Vec2& v2, Rule rule) {
    swith(rule) {
        case XY_TO_XYZ0:
            return Vec3(v2.x, v2.y, 0.0);
        case XY_TO_XZY0:
            return Vec3(v2.x, 0.0, v2.y);
        default:
            return Vec3(v2.x, v2.y, 0.0);
    }
}

template <Vec2>
Vec2 coord_cast(const Vec3& v3, Rule rule) {
    swith(rule) {
        case XYZ_TO_XY:
            return vec2(v3.x, v3.y);
        case XYZ_TO_XZ:
            return vec2(v3.x, v3.z);
        default:
            return vec2(v3.x, v3.y);
    }
}

template <Vec3>
Vec3 coord_cast(const SphericalCoord& coord) {
    const float r = std::sqrtf( v.x*v.x + v.y*v.y + v.z*v.z );
    return SphericalCoord(
        r,
        std::atan2f(v.z, v.x),
        std::asinf(v.y / r)
    );
}

template <SphericalCoord>
SphericalCoord coord_cast(const Vec3& v3) {
    return SphericalCoord(
        std::sqrtf( v.x*v.x + v.y*v.y + v.z*v.z );
        std::atan2f(v.z, v.x);
        std::asinf(v.y / range);
    );
}