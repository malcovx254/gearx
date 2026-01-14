#ifndef GEARX_SHAPES_3D_SHAPE3D_HPP
#define GEARX_SHAPES_3D_SHAPE3D_HPP

#include <cassert>
#include <vector>
#include <GL/gl.h>

#include "../../vector.hpp"
#include "../cache/circle_cache.hpp"
#include "normal.hpp"
#include "flat_renderfunctions.hpp"
#include "solid_renderfunctions.hpp"


namespace gearx::shape_3d {

    class PrismBase {
    protected:
        Vec3 m_pos;     // 中心位置
        float m_height; // 高さ　y軸

    public:
        PrismBase() 
        :m_pos(Vec3{0.0f}), m_height(0.0f) {
        }
        PrismBase(Vec3 pos, float height) 
        :m_pos(pos), m_height(height) {
        }

        virtual ~PrismBase(){
        }

        void translate() const {
            glTranslatef(m_pos.x, m_pos.y, m_pos.z);
        }
        virtual void rotate() const {
            // horizaontal rotation
            // vertial rotation
        }

        //virtual void renderSection(float y_position){ assert(base() <= y_position && y_position <= top() )};

        // drawing function
        virtual void render() const = 0;
        // @setter
        void setPosition(float x, float y, float z) {
            m_pos.x = x;
            m_pos.y = y;
            m_pos.z = z;
        }
        void setPosition(const Vec3 &pos) {
            m_pos = pos;
        }
        // @getter
        const Vec3 position() const {
            return m_pos;
        } 
        // @setter
        void setPosition2D(float x, float z) {
            m_pos.x = x;
            m_pos.z = z;
        }
        void setPosition2D(const Vec2& pos) {
            m_pos.x = pos.x;
            m_pos.z = pos.z;
        }
        // @getter
        const Vec2 position2D() const {
            return Vec2{m_pos.x, m_pos.z};
        }

        // @setter
        void setHeight(float height) {
            m_height = height;
        }
        void setHeightAbs(float ystart, float yend) {
            // Abs => 絶対　Absoluteの略
            // 高さの絶対座標　y軸の2点から高さと中心のy座標を計算する
            float top = std::fmax(ystart, yend);
            float base = std::fmin(ystart, yend);
            m_height = (top - base);
            m_pos.y = base + m_height / 2.0;
        }
        void setHeightRel(float basis, float relDistance) {
            // Rel => 相対 Relativeの略
            // 高さの相対距離　y軸の基準点とその相対距離から高さと中心のy座標を計算する
            m_height = abs(relDistance);
            m_pos.y = (basis + relDistance / 2.0);
        }
        // @getter
        const float height() const {
            return m_height;
        }
        // @ top 
        const float top() const {
            return m_pos.y + m_height / 2.0;
        }

        const float base() const {
            return m_pos.y - m_height / 2.0;
        }
    };

    //template<Int Polygon>
    //class Prism {};


    class Box
    :public PrismBase {
    public:
        Box(){}
        ~Box(){}

        void render() const override {
        }
    };
/*         class Box 
    :public Shape3D
    {
    protected:
        float m_width; //x
        float m_length; // z
        float m_rotation
    public:
        Box()
        :Shape3D(), m_width(0.0),m_length(0.0),m_rotation(0.0) {
        }

        Box(float length, float height, float width)
        :Shape3D(), m_rotation(0.0){
            assert(width > 0); assert(height > 0); assert(length > 0);
            m_width = width;
            m_height = height;
            m_length = length;
        }

        virtual ~Box(){
        }

        Box& setPosition(float x, float y, float z)  { m_pos.x = x; m_pos.y = y; m_pos.z = z; return *this; }
        Box& setPosition(const Vec3 &pos) { m_pos = pos; return *this; return *this; }
        Box& setPosXZ(const Vec2 &pos) { m_pos.x = pos.x; m_pos.z = pos.z; return *this; }
        Box& setPosXZ(float x, float z) { m_pos.x = x; m_pos.z = z; return *this; }
        
        Box& setTop(float top) {
            float currentBase = this->base();
            assert(top >= base);
            m_height = top - currentBase;
            m_pos.y = currentBase + m_height/2.0;
            return *this;
        }
        Box& setBase(float base) {
            float currentTop = this->top();
            assert(currentTop >= base);
            m_height = currentTop - base;
            m_pos.y = currentTop - m_height/2.0;
            return *this;
        }

        Box& setWidth(float width) {}
        Box& setHeight(float height) {}
        Box& setLength(float length) {}

        Box& setRotation(const float &rotation) {
            // @param angle 水平方向の傾き(ラジアン)
            if (rotation < 0) m_rotation = 2.0*M_PI - rotation;
            else if (rotation > 2.0*M_PI) {
                // 
            }
            m_rotation = rotation;
            return this*;
        }

        const float width() const { return m_width; }
        const float length() const { return m_length; }

        void render() const override {
                glPushMatrix();
                //glRotatef(m_angle, 1.0, 0.0, 0.0);
                glTranslatef(pos.x, pos.y, pos.z);
                _render();
                glPopMatrix();
        }

    private:
        void _render() const override {
            gearx::shape_3d::box(m_length, m_height, m_width);
        }
    }; */
    // other name is Box 
    typedef Box Cuboid;

    class Cylinder
    :public PrismBase {
        float m_holeRadius, m_radius;  // 円柱の内径、外径

    public:
        // constructor
        Cylinder() 
        :PrismBase(),m_holeRadius(0.0),m_radius(0.0) {
        }

        Cylinder(float radius, float height=0.0)
        :PrismBase(Vec3{0.0f}, height), m_holeRadius(0.0) {
            assert(radius > 0);
            assert(height >= 0);
            m_radius = radius;
        }

        virtual ~Cylinder() {
        }    

        void render() const override {
            if (m_holeRadius != 0.0f)
                gearx::shape_3d::cylinder( m_holeRadius, m_holeRadius, m_height, !_normal);
            gearx::shape_3d::cylinder(m_radius, m_radius, m_height, _normal);
            gearx::shape_3d::hollowDisk(m_holeRadius, m_radius,  m_height/2,  _normal);
            gearx::shape_3d::hollowDisk(m_holeRadius, m_radius, -m_height/2, !_normal);
        }

        //@setter
        Cylinder& setPosition(float x, float y, float z) {
            PrismBase::setPosition(x, y, z);
            return *this;
        }
        Cylinder& setPosition(const Vec3 &pos) {
            PrismBase::setPosition(pos);
            return *this;
        }

        Cylinder& setPosition2D(float x, float z) {
            PrismBase::setPosition2D(x, z);
            return *this;
        }
        Cylinder& setPosition2D(const Vec2 &pos) {
            PrismBase::setPosition2D(pos);
            return *this;
        }
        Cylinder& setHeight(float height) {
            PrismBase::setHeight(height);
            return *this;
        }
        Cylinder& setHeightAbs(float ystart, float yend) {
            PrismBase::setHeightAbs(ystart, yend);
            return *this;
        }
        Cylinder& setHeightRel(float basis, float relDistance) {
            PrismBase::setHeightRel(basis, relDistance);
            return *this;
        }
        // @setter specify Cylinder class
        Cylinder& setRadius(float radius) {
            // note: setHoleRadiusより先に使用してください
            // @exmaple cylinder.setRadius(1.0).setHoleRadius(0.5); -> OK
            // @example cylinder.setHoleRadius(0.5).setRadius(1.0); -> NG 
            assert(radius > m_holeRadius);
            m_radius = radius;
            return *this;
        }
        // @getter
        const float radius() const {
            return m_radius;
        }
        // @setter specify Cylinder class
        Cylinder& setHoleRadius(float holeRadius) {
            assert( holeRadius >= 0 && holeRadius < m_radius );
            m_holeRadius = holeRadius;
            return *this;
        }
        // @getter
        const float holeRadius() const {
            return m_holeRadius;
        }
    };



    class TruncatedCone
    :public PrismBase {
    
    private:
        float m_topHoleRadius;
        float m_topRadius;
        float m_baseHoleRadius;
        float m_baseRadius;

    public:
        // constructor
        TruncatedCone()
        :PrismBase(), m_topHoleRadius(0.0), m_topRadius(0.0), m_baseHoleRadius(0.0), m_baseRadius(0.0) {
        }

        TruncatedCone(float topRadius, float baseRadius, float height=0.0)
        :PrismBase(Vec3{ 0.0f}, height) {
            m_baseHoleRadius = 0.0;
            m_topHoleRadius = 0.0;

            assert(( topRadius > 0) || ( baseRadius > 0 ));
            m_topRadius = topRadius;
            m_baseRadius = baseRadius;
        }
        
        ~TruncatedCone() {
        }

        //@setter
        TruncatedCone& setPosition(float x, float y, float z) {
            PrismBase::setPosition(x, y, z);
            return *this;
        }
        TruncatedCone& setPosition(const Vec3 &pos) {
            PrismBase::setPosition(pos);
            return *this;
        }

        TruncatedCone& setPosition2D(float x, float z) {
            PrismBase::setPosition2D(x, z);
            return *this;
        }
        TruncatedCone& setPosition2D(const Vec2 &pos) {
            PrismBase::setPosition2D(pos);
            return *this;
        }
        TruncatedCone& setHeight(float height) {
            PrismBase::setHeight(height);
            return *this;
        }
        TruncatedCone& setHeightAbs(float ystart, float yend) {
            PrismBase::setHeightAbs(ystart, yend);
            return *this;
        }
        TruncatedCone& setHeightRel(float basis, float relDistance) {
            PrismBase::setHeightRel(basis, relDistance);
            return *this;
        }

        // @setter specify TruncatedCone class
        TruncatedCone& setRadius(float topRadius, float baseRadius) {
            assert( topRadius > m_topHoleRadius );
            assert( baseRadius > m_baseHoleRadius );
            m_topRadius = topRadius;
            m_baseRadius = baseRadius;
            return *this;
        }
        // @getter
        const float topRadius() const {
            return m_topRadius;
        }
        const float baseRadius() const {
            return m_baseRadius;
        }
        const float radius() const {
            // 上面と底面の大きいほう
            return std::fmax(m_topRadius, m_baseRadius);
        }
        // @setter specify TruncatedCone class
        TruncatedCone& setHoleRadius(float holeRadius) {
            assert( holeRadius >= 0 && holeRadius < m_topRadius && holeRadius < m_baseRadius );
            m_topHoleRadius = holeRadius;
            m_baseHoleRadius = holeRadius;
            return *this;
        }
        TruncatedCone& setHoleRadius(float topHoleRadius, float baseHoleRadius) {
            assert( topHoleRadius >= 0 && topHoleRadius <= m_topRadius );
            assert( baseHoleRadius >= 0 && baseHoleRadius <= m_baseRadius );
            m_topHoleRadius = topHoleRadius;
            m_baseHoleRadius = baseHoleRadius;
            return *this;
        }
        // @getter
        const float topHoleRadius() const {
            return m_topHoleRadius;
        }
        const float baseHoleRadius() const {
            return m_baseHoleRadius;
        }
        const float holeRadius() const {
            assert( m_topHoleRadius == m_baseHoleRadius );
            if (m_topHoleRadius == m_baseHoleRadius)
                return m_topHoleRadius;
        }
    
        void render() const override {
            if (m_topHoleRadius != m_topRadius)
                gearx::shape_3d::hollowDisk( m_topHoleRadius, m_topRadius,  m_height/2.0, _normal);
            if (m_baseHoleRadius != m_baseRadius)
                gearx::shape_3d::hollowDisk( m_baseHoleRadius, m_baseRadius,-m_height/2.0, !_normal);
            gearx::shape_3d::cylinder(m_topHoleRadius, m_baseHoleRadius, m_height, !_normal);
            gearx::shape_3d::cylinder(m_topRadius, m_baseRadius, m_height, _normal);
        }
    };

    enum class SemiCircle {
        LEFT,
        RIGHT,
        BOTH,
    };

    class ObroundCylinder
    :public PrismBase {
    private:
        SemiCircle m_option;
        float m_line, m_radius;
        float m_rotation;

    public:
        ObroundCylinder() 
        :PrismBase(), m_line(0.0), m_radius(0.0), m_rotation(0.0) {
            m_option = SemiCircle::BOTH;
        }

        ObroundCylinder(Vec2 &leftSemiCirclePos, Vec2 &rightSemiCirclePos, float radius, float height=0.0, SemiCircle option=SemiCircle::BOTH) 
        :PrismBase(Vec3{0.0f}, height), m_option(option) {
            // 半径
            assert(radius > 0);
            m_radius = radius;
            Vec2 pos1 = leftSemiCirclePos;
            Vec2 pos2 = rightSemiCirclePos;
            // 線の長さは2点間の距離 distance = sqrt(x^2 + z^2)
            m_line = dist2(pos1, pos2);
            // 位置は２点の中心（x,z座標のみ）、yは0 
            m_pos = Vec2to3( (pos1 + pos2)/2.0 );
            // 回転角 atan(z, x)
            m_rotation = DegToRad( std::atan2((pos2.z - pos1.z), (pos2.x - pos1.x)) );
            
            if ((pos1.x < pos2.x) && (pos1.z < pos2.z)) m_rotation; // do nothing
            else if ((pos1.x < pos2.x) && (pos1.z > pos2.z)) m_rotation = 360.0 - m_rotation;
            else if ((pos1.x > pos2.x) && (pos1.z < pos2.z)) m_rotation = 180.0 - m_rotation;
            else if ((pos1.x > pos2.x) && (pos1.z > pos2.z)) m_rotation = 180.0 + m_rotation;   
        }


        ObroundCylinder(float width, float length, float height=0.0, SemiCircle option=SemiCircle::BOTH)
        :PrismBase(Vec3{0.0f}, height), m_rotation(0.0), m_option(option) {
            assert( width > 0 );
            assert( length > width );
            m_radius = width / 2.0;
            m_line = length - width;
        }

        ~ObroundCylinder() {
        }

        //@setter
        ObroundCylinder& setPosition(float x, float y, float z) {
            PrismBase::setPosition(x, y, z);
            return *this;
        }
        ObroundCylinder& setPosition(const Vec3 &pos) {
            PrismBase::setPosition(pos);
            return *this;
        }

        ObroundCylinder& setPosition2D(float x, float z) {
            PrismBase::setPosition2D(x, z);
            return *this;
        }
        ObroundCylinder& setPosition2D(const Vec2 &pos) {
            PrismBase::setPosition2D(pos);
            return *this;
        }
        ObroundCylinder& setHeight(float height) {
            PrismBase::setHeight(height);
            return *this;
        }
        ObroundCylinder& setHeightAbs(float ystart, float yend) {
            PrismBase::setHeightAbs(ystart, yend);
            return *this;
        }
        ObroundCylinder& setHeightRel(float basis, float relDistance) {
            PrismBase::setHeightRel(basis, relDistance);
            return *this;
        }

        // @setter specify ObroundCylinder class
        ObroundCylinder& setRadius(float radius) {
            assert(radius > 0);
            m_radius = radius;
            return *this;
        }
        // @getter
        const float radius() const {
            return m_radius;
        }
        // @setter specify ObroundCylinder class
        ObroundCylinder& setLine(float line) {
            assert(line > 0);
            m_line = line;
            return *this;
        }
        // @getter
        const float line() const {
            return m_line;
        }
        // @setter specify ObroundCylinder class
        ObroundCylinder& setRotation(float rotation) {
            // rotation 角度は度数法で指定 (0° ~ 360°)
            assert((rotation >= 0) && (rotation <= 360));
            m_rotation = rotation;
            return *this;
        }
        // @getter
        const float rotation() const {
            return m_rotation;  // 度数法
        }
        // @setter specify ObroundCylinder class
        ObroundCylinder& setWidth(float width) {
            assert(width > 0);
            m_radius = width / 2.0;
            return *this;
        }
        // @getter
        const float width() const {
            return m_radius * 2.0;
        }
        // @setter specify ObroundCylinder class
        ObroundCylinder& setlength(float length) {
            assert(length > m_radius * 2.0);
            m_line = length - m_radius * 2.0;
        }
        // @getter
        const float length() const {
            return m_line + m_radius * 2.0;
        }

        void rotate() const override {
            glRotatef(m_rotation, 0.0, 1.0, 0.0);
        }
    
        void render() const override {
            // semicircle position
            const float xOffset = m_line*0.5; 
            // center box        
            gearx::shape_3d::box(m_line, m_height, m_radius*2.0, _normal);
           
            switch (m_option) {
                case SemiCircle::BOTH: {
                    // right semicircle                   
                    glPushMatrix();
                    glTranslatef(xOffset, 0.0, 0.0);
                    gearx::shape_3d::partialDisk(m_radius, 270.0, 90.0, m_height/2.0, _normal);
                    gearx::shape_3d::partialDisk(m_radius, 270.0, 90.0, -m_height/2.0, !_normal);
                    gearx::shape_3d::partialCylinder( m_radius, m_radius, 270.0, 90.0, m_height, _normal);
                    glPopMatrix(); 
                      // left semicircle
                    glPushMatrix();
                    glTranslatef(-xOffset, 0.0, 0.0);
                    gearx::shape_3d::partialDisk( m_radius, 90.0, 270.0,  m_height/2.0, _normal);
                    gearx::shape_3d::partialDisk( m_radius, 90.0, 270.0, -m_height/2.0, !_normal);
                    gearx::shape_3d::partialCylinder(m_radius, m_radius, 90.0, 270.0, m_height, _normal);
                    glPopMatrix();  
                    break;
                }
                case SemiCircle::LEFT: {
                      // left semicircle
                    glPushMatrix();
                    glTranslatef(-xOffset, 0.0, 0.0);
                    gearx::shape_3d::partialDisk( m_radius, 90.0, 270.0,  m_height/2.0, _normal);
                    gearx::shape_3d::partialDisk( m_radius, 90.0, 270.0, -m_height/2.0, !_normal);
                    gearx::shape_3d::partialCylinder(m_radius, m_radius, 90.0, 270.0, m_height, _normal);
                    glPopMatrix();  
                    break;
                }
                case SemiCircle::RIGHT: {
                    // right semicircle                   
                    glPushMatrix();
                    glTranslatef(xOffset, 0.0, 0.0);
                    gearx::shape_3d::partialDisk(m_radius, 270.0, 90.0, m_height/2.0, _normal);
                    gearx::shape_3d::partialDisk(m_radius, 270.0, 90.0, -m_height/2.0, !_normal);
                    gearx::shape_3d::partialCylinder( m_radius, m_radius, 270.0, 90.0, m_height, _normal);
                    glPopMatrix(); 
                    break;
                }
                default:
                    break;
            } 
        }
    };

}   // namespace gearx::shape_3d

#endif 
