#pragma once

#include "Transform.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
class Movement {
public:
    glm::vec3 m_velocity = glm::vec3(0.0f);

    /**
     * @brief TODO
     */
    Movement(const std::shared_ptr<Transform>& transform);

    /**
     * @brief TODO
     */
    void update(double deltaTime);

private:
    std::shared_ptr<Transform> m_transform;
    float m_speed;
};

}  // namespace labeeri::engine
