#include "Viewport.h"

#include <GL/glew.h>

#include "Application.h"

namespace labeeri::engine {

Viewport::Viewport() {
    LAB_LOGH2("Viewport::Viewport()");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Viewport::render() {
    auto [width, height] = LAB_APP.frameBufferSize();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // TODO remove color clear

    if (!LAB_CURRENT_SCENE)
        return;

    // TODO orthogonal projection if no camera
    auto viewMatrix = m_camera->viewMatrix();
    auto projectionMatrix = m_camera->projectionMatrix(width, height);

    for (auto& entity : LAB_CURRENT_SCENE->entities()) {
        if (entity->m_model)
            entity->m_model->draw(LAB_CURRENT_SCENE->time(), entity->transform()->modelMatrix(), viewMatrix, projectionMatrix);
    }

    LAB_LOG_OGL_ERROR();
}

void Viewport::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

}  // namespace labeeri::engine
