#ifndef GEARX_UI_AXISCONTORLLER_HPP
#define GEARX_UI_AXISCONTROLLER_HPP

#include <string>
#include "../vector.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

namespace gearx::ui
{
    enum class Axis {
        X,
        Y,
        Z,
        NX,
        NY,
        NZ,
    };    

    class AxisController {
        friend class PerspectiveGizmo;

        Axis axis;
        Vec3 m_pos;          // 軸球の3D位置
        float m_radius;      // 軸球半径
        float m_offset;      // 軸棒長さ
        bool  hasStick;
        std::string m_label;
        float m_color[4];
        float m_highlight_color[4];

    public:
        AxisController() : axis(Axis::X), m_pos(), m_radius(0), m_offset(0),
                        hasStick(false), m_label(""),
                        m_color{0,0,0,1}, m_highlight_color{0,0,0,1} {}

        AxisController(Axis ax,
                    float sphere_radius,
                    float offset,
                    const float color[3],
                    const float highlight_color[3])
            : axis(ax),
            m_radius(sphere_radius),
            m_offset(offset),
            hasStick(ax == Axis::X || ax == Axis::Y || ax == Axis::Z),
            m_color{color[0], color[1], color[2], 1.0f},
            m_highlight_color{highlight_color[0], highlight_color[1], highlight_color[2], 1.0f}
        {
            switch (ax) {
            case Axis::X:  m_pos = Vec3( 1, 0, 0) * offset; m_label = "X";  break;
            case Axis::Y:  m_pos = Vec3( 0, 1, 0) * offset; m_label = "Y";  break;
            case Axis::Z:  m_pos = Vec3( 0, 0, 1) * offset; m_label = "Z";  break;
            case Axis::NX: m_pos = Vec3(-1, 0, 0) * offset; m_label = "-X"; break;
            case Axis::NY: m_pos = Vec3( 0,-1, 0) * offset; m_label = "-Y"; break;
            case Axis::NZ: m_pos = Vec3( 0, 0,-1) * offset; m_label = "-Z"; break;
            }
        }

        // -----------------------------
        // 3D 描画（軸棒 + 軸球）
        // -----------------------------
        void render3D() const noexcept {
            glPushMatrix();

            // 軸棒
            if (hasStick) {
                glColor4fv(m_color);
                glPushMatrix();
                if (axis == Axis::X) glRotatef(90, 0, 1, 0);
                if (axis == Axis::Y) glRotatef(-90, 1, 0, 0);

                GLUquadric* quad = gluNewQuadric();
                gluCylinder(quad, 0.03, 0.03, m_offset, 16, 1);
                gluDeleteQuadric(quad);

                glPopMatrix();
            }

            // 軸球
            glTranslatef(m_pos.x, m_pos.y, m_pos.z);
            glColor4fv(m_color);
            glutSolidSphere(m_radius, 32, 32);

            glPopMatrix();
        }

        // -----------------------------
        // 3D → スクリーン座標変換
        // -----------------------------
        Vec3 getScreenPosition() const {
            GLdouble model[16], proj[16];
            GLint viewport[4];
            glGetDoublev(GL_MODELVIEW_MATRIX, model);
            glGetDoublev(GL_PROJECTION_MATRIX, proj);
            glGetIntegerv(GL_VIEWPORT,        viewport);

            GLdouble sx, sy, sz;
            gluProject(m_pos.x, m_pos.y, m_pos.z,
                    model, proj, viewport,
                    &sx, &sy, &sz);

            return Vec3{(float)sx, (float)sy, (float)sz};
        }

        // -----------------------------
        // 2D ラベル描画
        // -----------------------------
        void drawLabel2D(const Vec2& screenPos) const {
            glColor4fv(m_color);
            glRasterPos2f(screenPos.x + 6, screenPos.y + 6);

            for (char c : m_label) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    };
} // namespace gearx::ui


#endif