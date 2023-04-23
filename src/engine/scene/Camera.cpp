#include "Camera.h"

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

}  // namespace labeeri::engine