#ifndef GEARX_UI_ORBIT_GIZMO_HPP
#define GEARX_UI_ORBIT_GIZMO_HPP


#include "../color/color.hpp"
#include "axis_controller.hpp"
#include "ui_render_scope2d.hpp"

namespace gearx::ui
{
    class PerspectiveGizmo
    :public Controller {
    private:
        SphericalCoord camera;
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
            //glRotatef(camera.pitch, 1, 0, 0);
            //glRotatef(camera.yaw,   0, 1, 0);

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

        void drawUI2(int width, int height) {
            // --- 3D gizmo 描画 ---
            render();

            // --- 3D → 2D 座標変換 ---
            Vec3 pX  = axisX.getScreenPosition();
            Vec3 pY  = axisY.getScreenPosition();
            Vec3 pZ  = axisZ.getScreenPosition();
            Vec3 pNX = axisNX.getScreenPosition();
            Vec3 pNY = axisNY.getScreenPosition();
            Vec3 pNZ = axisNZ.getScreenPosition();

            // --- 2D UI モード（RAII） ---
            {
                Scoped2D ui2d(uiRM, width, height);

                axisX.drawLabel2D(Vec2{pX.x,  pX.y});
                axisY.drawLabel2D(Vec2{pY.x,  pY.y});
                axisZ.drawLabel2D(Vec2{pZ.x,  pZ.y});
                axisNX.drawLabel2D(Vec2{pNX.x, pNX.y});
                axisNY.drawLabel2D(Vec2{pNY.x, pNY.y});
                axisNZ.drawLabel2D(Vec2{pNZ.x, pNZ.y});
            }
        }


        // orbit click and rotate x or y or z axis
    };


} // namespace gearx::ui


#endif