#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Scene/Camera.h"
#include "Engine/WindowLayer/IWindowLayer.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class ViewportLayer : public IWindowLayer {
public:
    Ref<Camera> m_camera;

    /**
     * @brief TODO
     */
    ViewportLayer();

    virtual void onEvent(IEvent& e) override;

private:
    glm::uvec2 m_size = glm::uvec2(0);

    bool onRender(const ApplicationRenderEvent& e);

    bool onResize(const WindowResizeEvent& e);

    bool onMouseButtonPress(const MouseButtonPressEvent& e);

    bool onKeyboardPress(const KeyboardPressEvent& e);
};

}  // namespace labeeri::Engine
