#include "ViewportLayer.h"

#include "Engine/Application.h"
#include "Engine/Renderer/GLRenderer.h"
#include "Engine/Window/IWindow.h"

namespace labeeri::Engine {

ViewportLayer::ViewportLayer() {
    LAB_LOGH2("ViewportLayer::ViewportLayer()");

    m_size = LAB_WINDOW->frameBufferSize();
    LAB_RENDERER->setViewportSize(m_size);
    LAB_RENDERER->setClearColor(glm::vec4(glm::vec3(0.0), 1.0));
}

void ViewportLayer::onEvent(IEvent& e) {
    e.dispatch<ApplicationRenderEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onRender));
    e.dispatch<WindowResizeEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onResize));
    e.dispatch<MouseButtonPressEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onMouseButtonPress));
    e.dispatch<KeyboardPressEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onKeyboardPress));
}

bool ViewportLayer::onRender(const ApplicationRenderEvent& e) {
    LAB_RENDERER->clear((int)ClearBuffer::Color | (int)ClearBuffer::Depth);  // TODO remove color clear

    if (!LAB_CURRENT_SCENE) return false;

    // TODO orthogonal projection if no camera
    auto viewMatrix = m_camera->viewMatrix();
    auto projectionMatrix = m_camera->projectionMatrix(m_size);

    LAB_RENDERER->beginScene(LAB_CURRENT_SCENE->time(), m_camera->transform()->worldPosition(), viewMatrix, projectionMatrix);

    LAB_RENDERER->submitLight(RendererDirectionalLight(glm::vec3(1.0, -10.0, -5.0), RendererLightProperties(glm::vec3(0.1), glm::vec3(0.15, 0.15, 0.3), glm::vec3(0.15, 0.15, 0.3)*3.3f)));
    LAB_RENDERER->submitLight(RendererPointLight(glm::vec3(5.0, 5.0, -5.0), RendererLightProperties(glm::vec3(0), glm::vec3(1.0, 0.9, 0.8), glm::vec3(1.0, 0.9, 0.8)), RendererLightAttenutaion(1.0, 0.027, 0.0028)));

    for (auto& entity : LAB_CURRENT_SCENE->entities()) {
        if (entity->m_model)
            entity->m_model->draw(entity->transform()->modelMatrix());
    }

    LAB_RENDERER->endScene();

    LAB_LOG_RENDERAPI_ERROR();

    return false;
}

bool ViewportLayer::onResize(const WindowResizeEvent& e) {
    m_size = e.windowSize();
    LAB_RENDERER->setViewportSize(m_size);

    return false;
}

bool ViewportLayer::onMouseButtonPress(const MouseButtonPressEvent& e) {
    if (e.button() == MouseButton::Left && LAB_APP.focus() != ApplicationFocus::Viewport) {
        LAB_APP.focusViewport();
        return true;
    }

    return false;
}

bool ViewportLayer::onKeyboardPress(const KeyboardPressEvent& e) {
    if (e.key() == KeyboardKey::Escape && LAB_APP.focus() == ApplicationFocus::Viewport) {
        LAB_APP.focusUI();
        return true;
    }

    if (e.key() == KeyboardKey::F5) {
        LAB_WINDOW->setFullscreen(!LAB_WINDOW->fullscreen());
        return true;
    }

    return false;
}

}  // namespace labeeri::Engine