#include "solid_renderfunctions.hpp"


namespace gearx::shape_3d {

    void box(float x, float y, float z, Normal normal){
        x = x / 2.0;
        y = y / 2.0;
        z = z / 2.0;
        float n = normal_cast<float>(normal);
        glBegin(GL_QUADS);
            // 前面 (+y)
            // 通常はglNormal3f( 0.0f, 0.0f, (n == 0.0f) ? ※(1.0f) : -1.0f*n);
            // ※ObroundCylinderのlineの側面が一つだけ異なるので、-1.0fにしている
            glNormal3f( 0.0f, 0.0f, (n == 0.0f) ? -1.0f : -1.0f*n);
            glVertex3f(-x, -y, -z);
            glVertex3f( x, -y, -z);
            glVertex3f( x,  y, -z);
            glVertex3f(-x,  y, -z);

            // 背面 (-y)
            // 通常はglNormal3f( 0.0f, 0.0f, (n == 0.0f) ? ※(1.0f) : 1.0f*n);
            glNormal3f( 0.0f, 0.0f, (n == 0.0f) ? -1.0f : 1.0f*n);
            glVertex3f(-x, -y,  z);
            glVertex3f( x, -y,  z);
            glVertex3f( x,  y,  z);
            glVertex3f(-x,  y,  z);

            // 左面 (-x)
            glNormal3f( -1.0f*n, 0.0f, (n == 0.0f) ? 1.0f : 0.0f);
            glVertex3f(-x, -y, -z);
            glVertex3f(-x, -y,  z);
            glVertex3f(-x,  y,  z);
            glVertex3f(-x,  y, -z);

            // 右面 (+x)
            glNormal3f( 1.0f*n, 0.0f, (n == 0.0f) ? 1.0f : 0.0f);
            glVertex3f( x, -y, -z);
            glVertex3f( x, -y,  z);
            glVertex3f( x,  y,  z);
            glVertex3f( x,  y, -z);

            // 底面 (-z)
            glNormal3f( 0.0f, -1.0f*n, (n == 0.0f) ? 1.0f : 0.0f);
            glVertex3f(-x, -y, -z);
            glVertex3f( x, -y, -z);
            glVertex3f( x, -y,  z);
            glVertex3f(-x, -y,  z);

            // 上面 (+z)
            glNormal3f( 0.0f, 1.0f*n, (n == 0.0f) ? 1.0f : 0.0f);
            glVertex3f(-x,  y, -z);
            glVertex3f( x,  y, -z);
            glVertex3f( x,  y,  z);
            glVertex3f(-x,  y,  z);


        glEnd();
    }

    void boxFromDiagonal(Vec3 min, Vec3 max, Normal normal) {
        const float x0 = std::min(min.x, max.x);
        const float y0 = std::min(min.y, max.y);
        const float z0 = std::min(min.z, max.z);
        const float x1 = std::max(min.x, max.x);
        const float y1 = std::max(min.y, max.y);
        const float z1 = std::max(min.z, max.z);

        float n = normal_cast<float>(normal);
        glBegin(GL_QUADS);
        // 前面 (z = z0) 法線 (0,0,-1)
        glNormal3f( 0.0f, 0.0f, (n == 0.0f) ? 1.0f : -1.0f*n);
        glVertex3f(x0, y0, z0);
        glVertex3f(x1, y0, z0);
        glVertex3f(x1, y1, z0);
        glVertex3f(x0, y1, z0);

        // 背面 (z = z1) 法線 (0,0,1)
        glNormal3f( 0.0f, 0.0f, (n == 0.0f) ? 1.0f : 1.0f*n);
        glVertex3f(x1, y0, z1);
        glVertex3f(x0, y0, z1);
        glVertex3f(x0, y1, z1);
        glVertex3f(x1, y1, z1);

        // 左側面 (x = x0) 法線 (-1,0,0)
        glNormal3f( -1.0f*n, 0.0f, (n == 0.0f) ? 1.0f : 0.0f);
        glVertex3f(x0, y0, z0);
        glVertex3f(x0, y0, z1);
        glVertex3f(x0, y1, z1);
        glVertex3f(x0, y1, z0);

        // 右側面 (x = x1) 法線 (1,0,0)
        glNormal3f( 1.0f*n, 0.0f, (n == 0.0f) ? 1.0f : 0.0f);
        glVertex3f(x1, y0, z1);
        glVertex3f(x1, y0, z0);
        glVertex3f(x1, y1, z0);
        glVertex3f(x1, y1, z1);

        // 底面 (y = y0) 法線 (0,-1,0)
        glNormal3f( 0.0f, -1.0f*n, (n == 0.0f) ? 1.0f : 0.0f);
        glVertex3f(x0, y0, z0);
        glVertex3f(x1, y0, z0);
        glVertex3f(x1, y0, z1);
        glVertex3f(x0, y0, z1);

        // 上面 (y = y1) 法線 (0,1,0)
        glNormal3f( 0.0f, 1.0f*n, (n == 0.0f) ? 1.0f : 0.0f);
        glVertex3f(x0, y1, z1);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y1, z0);
        glVertex3f(x0, y1, z0);
        
        glEnd();
    }

 
    void cylinder(float topRadius, float baseRadius, float height, Normal normal) {
        auto& sin = SinCosCache::sin;
        auto& cos = SinCosCache::cos;
        auto slices = SinCosCache::slices;
        
        float n = normal_cast<float>(normal);

        glBegin(GL_QUADS);
        for (int i = 0; i < slices - 1; i++) {
            glNormal3f( n*cos[i], 0.0f, (n == 0.0f) ? 1.0f : n*sin[i]); // 側面の法線
            glVertex3f(topRadius*cos[i],       height/2,   topRadius*sin[i]);
            glVertex3f(topRadius*cos[i+1],     height/2,   topRadius*sin[i+1]);
            glVertex3f(baseRadius*cos[i+1], -height/2,   baseRadius*sin[i+1]);
            glVertex3f(baseRadius*cos[i],   -height/2,   baseRadius*sin[i]);
        }

        // for文の最後 i = slices-1として実行　インデックスにi+1をすると配列の範囲外になることを防ぐ 
            glNormal3f( n*cos[slices-1], 0.0f, (n == 0.0f) ? 1.0f : n*sin[slices-1]);
            glVertex3f(topRadius*cos[slices-1],       height/2,   topRadius*sin[slices-1]);
            glVertex3f(topRadius*cos[0],              height/2,   topRadius*sin[0]);
            glVertex3f(baseRadius*cos[0],          -height/2,   baseRadius*sin[0]);
            glVertex3f(baseRadius*cos[slices-1],   -height/2,   baseRadius*sin[slices-1]);
        glEnd();
    }
 
    void partialCylinder(float topRadius, float baseRadius, float startAngle, float sweepAngle, float height, Normal normal) {
        auto& sin = SinCosCache::sin;
        auto& cos = SinCosCache::cos;
        auto slices = SinCosCache::slices;

        startAngle = normalizeAngleDeg(startAngle);
        sweepAngle = normalizeAngleDeg(sweepAngle);

        const float delta = sweepAngle - startAngle; 
        const float sincosCacheDelta = 360.0f / (float)slices;

        // 度数法から弧度法に変換
        float startAngleRad = DegToRad(startAngle);
        float sweepAngleRad = DegToRad(sweepAngle);
        const float cosStart = std::cos(startAngleRad), sinStart = std::sin(startAngleRad);
        const float cosSweep = std::cos(sweepAngleRad), sinSweep = std::sin(sweepAngleRad);

        int startIdx, endIdx;
        float n = normal_cast<float>(normal);
        
        if (delta > 0) { 
            if (delta < sincosCacheDelta) {
            // FIX
                return;
            
            } else {
                startIdx = getIndexOfSinCosCacheNearestToAngle(startAngle, NearestOption::UPPER);
                endIdx = (sweepAngle == 360.0) ? slices - 1 : getIndexOfSinCosCacheNearestToAngle(sweepAngle, NearestOption::LOWER);
                
                glBegin(GL_QUADS);
                // first
                glNormal3f( n*cosStart, n*0.0f, (n == 0.0f) ? 1.0f : n*sinStart);
                glVertex3f(topRadius*cosStart,     height/2,   topRadius*sinStart);
                glVertex3f(topRadius*cos[startIdx],     height/2,   topRadius*sin[startIdx]);
                glVertex3f(baseRadius*cos[startIdx],   -height/2,   baseRadius*sin[startIdx]);
                glVertex3f(baseRadius*cosStart,   -height/2,   baseRadius*sinStart);
                // use sincosCache
                for (int i = startIdx; (i < endIdx)&&(i != slices-1); i++ ) {
                    glNormal3f( n*cos[i], 0.0f, (n == 0.0f) ? 1.0f : n*sin[i]); // 側面の法線
                    glVertex3f(topRadius*cos[i],       height/2,   topRadius*sin[i]);
                    glVertex3f(topRadius*cos[i+1],     height/2,   topRadius*sin[i+1]);
                    glVertex3f(baseRadius*cos[i+1], -height/2,   baseRadius*sin[i+1]);
                    glVertex3f(baseRadius*cos[i],   -height/2,   baseRadius*sin[i]);
                }
            // last
                glNormal3f( n*cos[endIdx], 0.0f, (n == 0.0f) ? 1.0f : n*sin[endIdx]);
                glVertex3f(topRadius*cos[endIdx],  height/2,   topRadius*sin[endIdx]);
                glVertex3f(topRadius*cosSweep,  height/2,   topRadius*sinSweep);
                glVertex3f(baseRadius*cosSweep,-height/2,   baseRadius*sinSweep);
                glVertex3f(baseRadius*cos[endIdx],-height/2,   baseRadius*sin[endIdx]);
            }
            glEnd();              

        }  else if (delta < 0) {
            if (std::fabs(delta) < sincosCacheDelta) {
                cylinder(topRadius, baseRadius, height);
                return;
            }
            // is same of 
            //partialCylinder(topRadius, baseRadius, startAngle, 360.0f, height);
            //partialCylinder(topRadius, baseRadius, 0.0f, sweepAngle, height);
                endIdx = getIndexOfSinCosCacheNearestToAngle(sweepAngle, NearestOption::UPPER);
                startIdx = getIndexOfSinCosCacheNearestToAngle(startAngle, NearestOption::LOWER);
                 //FIX assert((endIdx <= slices - 1) && (endIdx > startIdx));

                glBegin(GL_QUADS);
                // first
                glNormal3f( n*cosSweep, 0.0f, (n == 0.0f) ? 1.0f : n*sinSweep);
                glVertex3f(topRadius*cosSweep,  height/2,   topRadius*sinSweep);
                glVertex3f(topRadius*cos[endIdx],  height/2,   topRadius*sin[endIdx]);
                glVertex3f(baseRadius*cos[endIdx],-height/2,   baseRadius*sin[endIdx]);
                glVertex3f(baseRadius*cosSweep,-height/2,   baseRadius*sinSweep);

                // use sincosCache
                for (int i = endIdx; i < slices-1; i++ ) {
                    glNormal3f( n*cos[i], 0.0f, (n == 0.0f) ? 1.0f : n*sin[i]); // 側面の法線
                    glVertex3f(topRadius*cos[i],       height/2,   topRadius*sin[i]);
                    glVertex3f(topRadius*cos[i+1],     height/2,   topRadius*sin[i+1]);
                    glVertex3f(baseRadius*cos[i+1], -height/2,   baseRadius*sin[i+1]);
                    glVertex3f(baseRadius*cos[i],   -height/2,   baseRadius*sin[i]);
                }
                glNormal3f( n*cos[slices-1], 0.0f, (n == 0.0f) ? 1.0f : n*sin[slices-1]); // 側面の法線
                glVertex3f(topRadius*cos[slices-1],       height/2,   topRadius*sin[slices-1]);
                glVertex3f(topRadius*cos[0],     height/2,   topRadius*sin[0]);
                glVertex3f(baseRadius*cos[0], -height/2,   baseRadius*sin[0]);
                glVertex3f(baseRadius*cos[slices-1],   -height/2,   baseRadius*sin[slices-1]);

                for (int i = 0; i < startIdx; i++ ) {
                    glNormal3f( n*cos[i], 0.0f, (n == 0.0f) ? 1.0f : n*sin[i]); // 側面の法線
                    glVertex3f(topRadius*cos[i],       height/2,   topRadius*sin[i]);
                    glVertex3f(topRadius*cos[i+1],     height/2,   topRadius*sin[i+1]);
                    glVertex3f(baseRadius*cos[i+1], -height/2,   baseRadius*sin[i+1]);
                    glVertex3f(baseRadius*cos[i],   -height/2,   baseRadius*sin[i]);
                }
            
                glNormal3f( n*cosStart, 0.0f, (n == 0.0f) ? 1.0f : n*sinStart);
                glVertex3f(topRadius*cos[startIdx],     height/2,   topRadius*sin[startIdx]);
                glVertex3f(topRadius*cosStart,     height/2,   topRadius*sinStart);
                glVertex3f(baseRadius*cosStart,   -height/2,   baseRadius*sinStart);
                glVertex3f(baseRadius*cos[startIdx],   -height/2,   baseRadius*sin[startIdx]);

            glEnd();         
        }
    }


} // namespace gearx::shape_3d