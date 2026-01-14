#ifndef GEARX_SHAPES_CACHE_CIRCLE_CACHE_HPP
#define GEARX_SHAPES_CACHE_CIRCLE_CACHE_HPP

#include <cmath>
#include <vector>




enum NearestOption {
    LOWER,
    UPPER,
    NEAREST
};


struct SinCosCache {
    static size_t slices;
    static std::vector<float> sin, cos;

    static void init() {
        sin.resize(slices);
        cos.resize(slices);
        
        float angle = 0.0;
        const float delta = 2.0 * M_PI / (float)slices;
        
        for( int i = 0; i < slices; i++) {
            sin[i] = std::sin(angle);
            cos[i] = std::cos(angle);

            angle+= delta;
        }
    }
};

    
int getIndexOfSinCosCacheNearestToAngle(float targetAngle, NearestOption option=NearestOption::NEAREST);




#endif