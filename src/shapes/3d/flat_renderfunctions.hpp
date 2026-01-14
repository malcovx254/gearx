#ifndef GEARX_SHAPES_3D_FLAT_RENDERFUNCTIONS_HPP
#define GEARX_SHAPES_3D_FLAT_RENDERFUNCTIONS_HPP

#include <cassert>
#include <cmath>
#include <vector>
#include <GL/gl.h>
#include "normal.hpp"
#include "../cache/circle_cache.hpp"

namespace gearx::shape_3d {
    void disk( float radius, float y_position=0, Normal normal = _normal);
    void hollowDisk( float innerRadius, float outerRadius, float y_position=0, Normal normal = _normal);
    void partialDisk( float radius, float startAngle, float sweepAngle, float y_position=0, Normal normal = _normal);
    
} //namespace gearx::shape_3d


#endif