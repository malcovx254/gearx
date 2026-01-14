/*
RAII  the simple wrapper of UIRenderState class.
*/

#ifndef GEARX_UI_UIRENDERSCOPE2D_HPP
#define GEARX_UI_UIRENDERSCOPE2D_HPP

#include "ui_render_state.hpp"
namespace gearx::ui
{
    class UIRenderScope2D {
        UIRenderState& m_state;
    public:
        UIRenderScope2D(UIRenderState& state, int w, int h) : m_state(state) {
            m_state.switchTo2D(w, h);
        }
        ~UIRenderScope2D() {
            m_state.switchTo3D();
        }
    };
} // namespace gearx::ui


#endif