#pragma once

#include "Engine/Scene/Transform.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Camera {
public:
    float m_FOV = 90.0f;
    float m_near = 0.1f;
    float m_far = 50.0f;

    /**
     * @brief TODO
     */
    explicit Camera(const std::shared_ptr<Transform>& transform) : m_transform(transform) {
    }

    /**
     * @brief TODO
     */
    const std::shared_ptr<Transform>& transform() const {
        return m_transform;
    }

    /**
     * @brief TODO
     */
    glm::mat4 viewMatrix() const {
        glm::vec3 cameraPosition = m_transform->worldPosition();
        glm::vec3 center = cameraPosition + m_transform->forward();

        return glm::lookAt(cameraPosition, center, m_transform->up());
    }

    /**
     * @brief TODO
     */
    glm::mat4 projectionMatrix(glm::uvec2 viewportSize) const {
        float aspectRatio = (float)viewportSize.x / (float)viewportSize.y;

        return glm::perspective(glm::radians(m_FOV), aspectRatio, m_near, m_far);
    }

private:
    std::shared_ptr<Transform> m_transform;
};

}  // namespace labeeri::Engine
