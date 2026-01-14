#ifndef GEARX_UI_GIZMO_HPP
#define GEARX_UI_GIZMO_HPP

#include "../vector.hpp"
#include "coord.hpp"

#include <cmath>
#include <memory>
#include <vector>
#include <string>
#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>

namespace gearx::color
{
const float red[3] = { 1.0, 0.0, 0.0 };
const float green[3] = { 0.0, 1.0, 0.0 };
const float blue[3] = { 0.0, 0.0, 1.0 };

} // namespace gearx::color

using namespace gearx::color;

namespace gearx::ui
{
    
    class UI {
    public:
        virtual void render() const = 0;
    };

    class UIRenderState {
        GLdouble savedProjection[16];
        GLdouble savedModelview[16];
        GLint savedViewport[4];

    public:
        // 3D → 2D へ切り替え
        void switchTo2D(int width, int height) {
            // 現在の状態を保存
            glGetDoublev(GL_PROJECTION_MATRIX, savedProjection);
            glGetDoublev(GL_MODELVIEW_MATRIX, savedModelview);
            glGetIntegerv(GL_VIEWPORT, savedViewport);

            // 2D 用の設定
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            gluOrtho2D(0, width, 0, height);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();

            // 深度テストは不要
            glDisable(GL_DEPTH_TEST);
        }

        // 2D → 3D へ戻す
        void switchTo3D() {
            // 行列を元に戻す
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();

            // 深度テストを復帰
            glEnable(GL_DEPTH_TEST);
        }
    };

    enum class Axis {
        X,
        Y,
        Z,
        NX,
        NY,
        NZ,
    };

    class PerspectiveGizmo 
    :public UI {


        class AxisController {
            friend class PerspectiveGizmo;  // 外クラスだけがメンバ変数、メンバ関数にアクセスできる
            // X,Y,Z, -X,-Y,-Z　各軸の軸球と軸棒、軸ラベルを付けるクラス
            Axis axis;
            bool hasStick;

            Vec3 m_pos;

            float m_radius; // sphere radius
            float m_offset; // 球を描く位置の半径であり、stickの長さとなる
            float m_stick_radius;   // stickの円柱の半径
            std::string m_label;
            float m_color[4];
            float m_highlight_color[4];
            
            AxisController()
            :m_radius(0.0),
            m_pos(Vec3()),
            m_label(std::string("")),
            m_offset(0.0),
            hasStick(false),
            m_stick_radius(0.0),
            m_color { 0.0, 0.0,  0.0, 1.0 },
            m_highlight_color { 0.0, 0.0, 0.0, 1.0 } {
                axis = Axis::X;
            }

            AxisController(Axis ax, float radius, float offset, const float color[3], const float highlight_color[3]) 
               :m_radius(radius),
                axis(ax),
                m_offset(offset),
                hasStick( ax == Axis::X || ax == Axis::Y || ax == Axis::Z ),
                m_stick_radius(radius*0.3),
                m_color { color[0], color[1], color[2], 1.0 },
                m_highlight_color { highlight_color[0], highlight_color[1], highlight_color[2], 1.0 } {

                    switch (axis) {
                        case Axis::X: {
                            m_pos = Vec3(1.0, 0.0, 0.0)*offset;
                            m_label = std::string("X");
                            }
                            break;
                        case Axis::Y: {
                            m_pos = Vec3(0.0, 1.0, 0.0)*offset;  
                            m_label = std::string("Y");    
                            }
                            break;
                        case Axis::Z: {
                            m_pos = Vec3(0.0, 0.0, 1.0)*offset;
                            m_label = std::string("Z");
                            }
                            break;
                        case Axis::NX: {
                            m_pos = Vec3(-1.0, 0.0, 0.0)*offset;
                            m_label = std::string("-X");
                            } 
                            break;
                        case Axis::NY: {
                            m_pos = Vec3(0.0, -1.0, 0.0)*offset;
                            m_label = std::string("-Y");
                            }  
                            break;
                        case Axis::NZ: {
                            m_pos = Vec3(0.0, 0.0, -1.0)*offset;
                            m_label = std::string("-Z");
                            }
                            break;
                        default:
                            m_pos = Vec3();
                            m_label = std::string("");
                            break;
                    }
            }

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

                return Vec3{ (float)sx, (float)sy, (float)sz };
            }

            // 2D ラベル描画
            void renderLabel2D(const Vec2& screenPos) const noexcept {
                glColor4fv(m_color);
                glRasterPos2f(screenPos.x + 6, screenPos.y + 6);

                for (char c : m_label.c_str()) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
                }
            }

            void highlight() {
            }

            void unhighlight() {
            }

            void renderSphere3D() const noexcept {
                glPushMatrix();
                glTranslatef(m_pos.x, m_pos.y, m_pos.z);
                glColor4fv(m_color);
                glutSolidSphere(0.1, 32, 32);

                glPopMatrix();
            }

            void renderStick3D() const noexcept {
                if (hasStick){
                    glColor4fv(m_color);
                    // 円柱を描く
                    switch (axis)
                    {
                    case Axis::X:
                        /* code */
                        break;
                    case Axis::Y:
                    case Axis::Z:
                    case Axis::NX:
                    case Axis::NY:
                    case Axis::NZ:
                        break;
                    default:
                        break;
                    }
                }
            }
        };  // AxisController Class

    private:
        SphericalCoord camera_coord;
        const int gizmoSize = 150;
        float m_radius;
        AxisController axisX, axisY, axisZ, axisNX, axisNY, axisNZ;

    public:
        PerspectiveGizmo(float radius = 0.5)
        :m_radius(radius) {
            const float axis_label_radius = radius*0.2;
            const float offset = m_radius*0.8;
            axisX = AxisController(Axis::X , axis_label_radius,   offset, red, red);
            axisY = AxisController(Axis::Y , axis_label_radius,   offset, green, green);
            axisZ = AxisController(Axis::Z , axis_label_radius,   offset, blue, blue);
            axisNX = AxisController(Axis::NX , axis_label_radius, offset, red, red);
            axisNY = AxisController(Axis::NY , axis_label_radius, offset, green, green);
            axisNZ = AxisController(Axis::NZ , axis_label_radius, offset, blue, blue);
        }


        void rende3Dr() const override {
            // 1. 軸棒と軸球を描く（普通に深度テストあり）
            axisX.renderStick3D();
            axisY.renderStick3D();
            axisZ.renderStick3D();
            // 軸球
            axisX.renderSphere3D();
            axisY.renderSphere3D();
            axisZ.renderSphere3D();
            axisNX.renderSphere3D();
            axisNY.renderSphere3D();
            axisNZ.renderSphere3D();

            // 2. 灰色の球は「見た目だけ」上からかぶせる
            glDepthMask(GL_FALSE);          // 深度バッファへの書き込みを禁止
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glColor4f(0.2f, 0.2f, 0.2f, 0.4f);
            glutSolidSphere(m_radius, 32, 32);

            glDepthMask(GL_TRUE);           // 元に戻す

        }

        void drawUI(int width, int height)
        {
            // 1. ビューポートを右上に限定
            glViewport(width - gizmoSize, height - gizmoSize, gizmoSize, gizmoSize);

            // 2. 投影行列
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            gluPerspective(35.0, 1.0, 0.01, 100.0);

            // 3. モデルビュー行列
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();

            gluLookAt(0,0,3, 0,0,0, 0,1,0);

            // カメラの回転だけ反映
            //glRotatef(cameraPitch, 1, 0, 0);
            //glRotatef(cameraYaw,   0, 1, 0);

            // 4. 深度だけクリア
            glDisable(GL_STENCIL_TEST);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_DEPTH_BUFFER_BIT);

            // 5. ライティングを一時的に無効化
            bool lighting = glIsEnabled(GL_LIGHTING);
            glDisable(GL_LIGHTING);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // --- ギズモ描画 ---
            render();

            // 6. 復元
            if (lighting) glEnable(GL_LIGHTING);

            glPopMatrix(); // MODELVIEW
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);

            glViewport(0, 0, width, height);
        }

        // orbit click and rotate x or y or z axis
    };

} // namespace gearx::ui



#endif