#include "circle_cache.hpp"


int getIndexOfSinCosCacheNearestToAngle(float targetAngle, NearestOption option) {
    auto& slices = SinCosCache::slices;
    
    targetAngle = normalizeAngleDeg(targetAngle);
    const float delta = 360.0 / (float) slices;
    
    int result = (int)(targetAngle / delta) % slices;

    switch (option) {

        case LOWER: {
            return result;
        }
        case UPPER: {
            if (result == slices - 1)
                return 0;
            else
                return (result+1) % slices;
        }
        default: {
            float lower = (float)result * delta;
            float upper = lower + delta;
            if ((targetAngle - lower) >= (upper - targetAngle)) {
                // upper case
                if (result == slices - 1) 
                    return 0;
                return (result+1) % slices;
            } else
                // lower case
                return result;
        }
    };
}