#include "Viewport.h"

#include "Application.h"
#include "log.h"

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

Viewport::Viewport(Application& app) : Renderable(app) {
    LAB_LOGH2("Viewport::Viewport()");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Viewport::render() {
    auto [width, height] = m_app.frameBufferSize();
    glViewport(0, 0, width, height);  // TODO move to callback

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // TODO remove color clear

    if (!m_app.m_scene)
        return;

    // TODO orthogonal projection if no camera
    auto viewMatrix = m_camera->viewMatrix();
    auto projectionMatrix = m_camera->projectionMatrix(width, height);

    for (auto& entity : m_app.m_scene->entities()) {
        if (entity->m_model)
            entity->m_model->draw(m_app.m_scene->time(), entity->transform()->modelMatrix(), viewMatrix, projectionMatrix);
    }

    LAB_LOG_OGL_ERROR();
}

}  // namespace labeeri::engine
