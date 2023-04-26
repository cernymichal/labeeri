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
    Camera(const std::shared_ptr<Transform>& transform);

    /**
     * @brief TODO
     */
    const std::shared_ptr<Transform>& transform() const;

    /**
     * @brief TODO
     */
    glm::mat4 viewMatrix() const;

    /**
     * @brief TODO
     */
    glm::mat4 projectionMatrix(glm::uvec2 viewportSize) const;

private:
    std::shared_ptr<Transform> m_transform;
};

}  // namespace labeeri::Engine
