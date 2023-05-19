#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/SceneEvent.h"
#include "Engine/Renderer/Framebuffer.h"
#include "Engine/Scene/ECS/Entity.h"
#include "Engine/Scene/Systems/RenderSystem.h"
#include "Engine/WindowLayer/IWindowLayer.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class ViewportLayer : public IWindowLayer {
public:
    Entity m_camera;

    /**
     * @brief TODO
     */
    ViewportLayer();

    virtual void onEvent(IEvent& e) override;

private:
    glm::uvec2 m_size = glm::uvec2(0);
    Ref<Framebuffer> m_viewFramebuffer;
    Ref<Framebuffer> m_idFramebuffer;

    bool onRender(const ApplicationRenderEvent& e);

    bool onResize(const WindowResizeEvent& e);

    bool onMouseButtonPress(const MouseButtonPressEvent& e);

    bool onKeyboardPress(const KeyboardPressEvent& e);

    void updateViewFramebuffer();

    void updateIdFramebuffer();

    void clickOnObject(const glm::uvec2& mousePosition);
};

}  // namespace labeeri::Engine
