#include "Viewport.h"

#include <GL/glew.h>

#include "Application.h"

namespace labeeri::engine {

Camera::Camera(const std::shared_ptr<Transform>& transform) : m_transform(transform) {
}

const std::shared_ptr<Transform>& Camera::transform() const {
    return m_transform;
}

glm::mat4 Camera::viewMatrix() const {
    glm::vec3 cameraPosition = m_transform->worldPosition();
    glm::vec3 center = cameraPosition + m_transform->forward();

    return glm::lookAt(cameraPosition, center, m_transform->up());
}

glm::mat4 Camera::projectionMatrix(int width, int height) const {
    float aspectRatio = (float)width / (float)height;

    return glm::perspective(glm::radians(m_FOV), aspectRatio, m_near, m_far);
}

Viewport::Viewport() {
    LAB_LOGH2("Viewport::Viewport()");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Viewport::render() {
    auto [width, height] = LAB_APP.frameBufferSize();
    glViewport(0, 0, width, height);  // TODO move to callback

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

}  // namespace labeeri::engine
