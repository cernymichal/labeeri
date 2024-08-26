#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Renderer/Framebuffer.h"
#include "Engine/Scene/ECS/Entity.h"
#include "Engine/WindowLayer/IWindowLayer.h"

namespace labeeri::Engine {

/**
 * @brief A window layer that renders the scene from a camera.
 */
class ViewportLayer : public IWindowLayer {
public:
    Entity m_camera;

    /**
     * @brief Creates the viewport layer and its framebuffers.
     */
    ViewportLayer();

    virtual void onEvent(IEvent& e) override;

private:
    uvec2 m_size = uvec2(0);
    Ref<Framebuffer> m_viewFramebuffer;
    Ref<Framebuffer> m_idFramebuffer;

    bool onRender(const ApplicationRenderEvent& e);

    bool onResize(const WindowResizeEvent& e);

    bool onMouseButtonPress(const MouseButtonPressEvent& e);

    bool onKeyboardPress(const KeyboardPressEvent& e);

    void updateViewFramebuffer();

    void updateIdFramebuffer();

    EntityId clickObject(const uvec2& mousePosition);
};

}  // namespace labeeri::Engine
