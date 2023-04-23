#pragma once

#include "Transform.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
class Camera {
public:
    float m_FOV = 95.0f;
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
    glm::mat4 projectionMatrix(int viewportWidth, int viewportHeight) const;

private:
    std::shared_ptr<Transform> m_transform;
};

}  // namespace labeeri::engine
