#ifndef GEARX_shape3D_NORMAL_HPP
#define GEARX_shape3D_NORMAL_HPP

#include <cmath>
#include "../../vector.hpp"

namespace gearx::shape_3d
{

    enum class Normal : int {
        INSIDE = -1,
        NONE = 0,
        OUTSIDE = 1,
    };
    
    static Normal _normal;


    Normal operator ! (Normal normal);

    template <typename T>
    T normal_cast(Normal normal) {
        return 0.0f;
    }

    template<>
    float normal_cast<float>(Normal normal);

    static void setNormal(Normal normal) {
        _normal = normal;
    }

} // namespace gearx::shape_3d



#endif