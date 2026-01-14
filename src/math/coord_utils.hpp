#ifndef GEARX_COORDUTILS_HPP
#define GEARX_COORDUTILS_HPP

#include <cmath>

float dist2(Vec2 &pos1, Vec2 &pos2);
float dist3(Vec3 &pos1, Vec3 &pos2);

enum Rule {
    XY_TO_XYZ0,
    XY_TO_XZY0,
    XYZ_TO_XY,
    XYZ_TO_XZ,
} 

template <typename T>
T coord_cast();

template <Vec3> 
Vec3 coord_cast(const Vec2& v2, Rule rule=XY_TO_XYZ0);

template <Vec2>
Vec2 coord_cast(const Vec3& v3, Rule rule=XYZ_TO_XY);

template <Vec3>
Vec3 coord_cast(const SphericalCoord& coord);

template <SphericalCoord>
SphericalCoord coord_cast(const Vec3& v3);



#endif 