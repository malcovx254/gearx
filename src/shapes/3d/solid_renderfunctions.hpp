#ifndef GEARX_SHAPE3D_SOLID_RENDERFUNCTIONS_HPP
#define GEARX_SHAPE3D_SOLID_RENDERFUNCTIONS_HPP

#include<iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <GL/gl.h>

#include "../../vector.hpp"
#include "normal.hpp"
#include "../cache/circle_cache.hpp"
#include "flat_renderfunctions.hpp"

namespace gearx::shape_3d {

    void box(float x, float y, float z, Normal normal = _normal);
    void boxFromDiagonal(Vec3 min, Vec3 max, Normal normal = _normal); 
    void cylinder(float topRadius, float baseRadius, float height, Normal normal = _normal);

    void partialCylinder(float topRadius, float baseRadius, float startAngle, float sweepAngle, float height, Normal normal = _normal);

} // namespace gearx::shape_3d


#endif