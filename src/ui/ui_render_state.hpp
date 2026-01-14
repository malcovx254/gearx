#ifndef GEARX_UI_UIRENDERSTATE_HPP
#define GEARX_UI_UIRENDERSTATE_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

namespace gearx::ui
{
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


} // namespace gearx::ui


#endif