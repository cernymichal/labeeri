#include "ViewportLayer.h"

#include <GL/glew.h>

#include "Engine/Application.h"

namespace labeeri::Engine {

ViewportLayer::ViewportLayer() {
    LAB_LOGH2("ViewportLayer::ViewportLayer()");

    m_size = LAB_APP.frameBufferSize();
    glViewport(0, 0, m_size.x, m_size.y);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void ViewportLayer::onEvent(Event& e) {
    e.dispatch<ApplicationRenderEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onRender));
    e.dispatch<WindowResizeEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onResize));
    e.dispatch<MouseButtonPressEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onMouseButtonPress));
    e.dispatch<KeyboardPressEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onKeyboardPress));
}

bool ViewportLayer::onRender(const ApplicationRenderEvent& e) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // TODO remove color clear

    if (!LAB_CURRENT_SCENE)
        return false;

    // TODO orthogonal projection if no camera
    auto viewMatrix = m_camera->viewMatrix();
    auto projectionMatrix = m_camera->projectionMatrix(m_size);

    for (auto& entity : LAB_CURRENT_SCENE->entities()) {
        if (entity->m_model)
            entity->m_model->draw(LAB_CURRENT_SCENE->time(), entity->transform()->modelMatrix(), viewMatrix, projectionMatrix);
    }

    LAB_LOG_OGL_ERROR();

    return false;
}

bool ViewportLayer::onResize(const WindowResizeEvent& e) {
    m_size = e.windowSize();
    glViewport(0, 0, m_size.x, m_size.y);

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

    return false;
}

}  // namespace labeeri::Engine
