#include "flat_renderfunctions.hpp"



namespace gearx::shape_3d {


    void disk(float radius, float y_position, Normal normal) {
        
        assert(radius > 0);
        auto& sin = SinCosCache::sin;
        auto& cos = SinCosCache::cos;
        auto slices = SinCosCache::slices;
        
        float n = normal_cast<float>(normal);

        glNormal3f(0.0f, n*1.0f, (n == 0.0f) ? 1.0f :0.0f);
        glBegin(GL_POLYGON); 
        for (int i = 0; i < slices; i++) {
            glVertex3f( radius*cos[i], y_position, radius*sin[i] );
        }
            glVertex3f( radius*cos[0], y_position, radius*cos[0] );
        glEnd();
        
    }

    void hollowDisk(float innerRadius, float outerRadius, float y_position, Normal normal) {
        assert(innerRadius >= 0);
        assert(innerRadius < outerRadius);
        
        auto& sin = SinCosCache::sin;
        auto& cos = SinCosCache::cos;
        auto slices = SinCosCache::slices;
        float n = normal_cast<float>(normal);
        
        glNormal3f(0.0f, n*1.0f, (n == 0.0f) ? 1.0f :0.0f);
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < slices; i++) {
            glVertex3f( outerRadius*cos[i], y_position, outerRadius*sin[i] );
            glVertex3f( innerRadius*cos[i], y_position, innerRadius*sin[i] );
        }
            glVertex3f( outerRadius*cos[0], y_position, outerRadius*sin[0] );
            glVertex3f( innerRadius*cos[0], y_position, innerRadius*sin[0] );
        glEnd();
    }

    
    void partialDisk(float radius, float startAngle, float sweepAngle, float y_position, Normal normal) {
        auto& sin = SinCosCache::sin;
        auto& cos = SinCosCache::cos;
        auto slices = SinCosCache::slices;
        
        startAngle = normalizeAngleDeg(startAngle);
        sweepAngle = normalizeAngleDeg(sweepAngle);

        const float delta = sweepAngle - startAngle; 
        const float sincosCacheDelta = 360.0 / (float)slices;

        float n = normal_cast<float>(normal);

        if (delta > 0) {
            if (delta < sincosCacheDelta)
                return;

            const int startIdx = getIndexOfSinCosCacheNearestToAngle(startAngle, NearestOption::UPPER);
            const int endIdx = (sweepAngle == 360.0) ? slices - 1 : getIndexOfSinCosCacheNearestToAngle(sweepAngle, NearestOption::LOWER);

            startAngle = DegToRad(startAngle);
            sweepAngle = DegToRad(sweepAngle);

            glNormal3f(0.0f, n*1.0f, (n == 0.0f) ? 1.0f :0.0f);
            glBegin(GL_POLYGON);
            glVertex3f( radius*std::cos(startAngle), y_position, radius*std::sin(startAngle) );
            for (int i = startIdx; i < endIdx; i++) {
                glVertex3f( radius*cos[i], y_position, radius*sin[i] );
            }
            glVertex3f( radius*std::cos(sweepAngle), y_position, radius*std::sin(sweepAngle) );
            // 下一行をコメントにすると弦になる。
            glVertex3f(0.0f, 0.0f, 0.0f);
            glEnd();

        } else if (delta < 0) {
            if (std::fabs(delta) < sincosCacheDelta) {
                disk(radius, y_position);
                return;
            }
            partialDisk(radius, startAngle, 360.0f, y_position);
            partialDisk(radius, 0.0f, sweepAngle, y_position);
        } else 
            return;
    }



} // namespace gearx::shape_3d