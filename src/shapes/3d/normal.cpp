#include "normal.hpp"

namespace gearx::shape_3d
{
    Normal operator ! (Normal normal) {
        switch (normal)
        {
        case gearx::shape_3d::Normal::NONE:
            return normal;
        case gearx::shape_3d::Normal::OUTSIDE:
            return Normal::INSIDE;
        case gearx::shape_3d::Normal::INSIDE:
            return Normal::OUTSIDE;
        default:
            return normal;
        }
    }

    template<> 
    float normal_cast<float>(Normal normal) {
        return static_cast<float> (static_cast<int>(normal));
    }

} // namespace gearx::shape_3d
