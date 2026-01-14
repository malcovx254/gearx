#ifndef GEARX_SHAPE2D_HPP
#define GEARX_SHAPE2D_HPP


namespace gearx::shape2D {
    class Shape2D {
            Vec2 m_pos;
        public:
            Shape2D(){};
            ~Shape2D{};
            void translate(){};
            void translate(float x, float z) {
                
            };
            virtual void render() const = 0;
    };
} //namespace gearx::shape2D
#endif