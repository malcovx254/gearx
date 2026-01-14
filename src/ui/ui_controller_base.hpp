#ifndef GEARX_UI_UICONTROLLERBASE_HPP
#define GEARX_UI_UICONTROLLERBASE_HPP

namespace gearx::ui
{
    class Controller {
    public:
        virtual void render() const noexcept = 0;
    };

} // namespace gearx::ui

#endif