#include "Camera.h"

namespace labeeri::Engine {

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

glm::mat4 Camera::projectionMatrix(glm::uvec2 viewportSize) const {
    float aspectRatio = (float)viewportSize.x / (float)viewportSize.y;

    return glm::perspective(glm::radians(m_FOV), aspectRatio, m_near, m_far);
}

}  // namespace labeeri::Engine
