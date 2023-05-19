#pragma once

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class RigidBody {
public:
    glm::vec3 m_velocity = glm::vec3(0.0f);
    glm::vec3 m_acceleration = glm::vec3(0.0f);
};

}  // namespace labeeri::Engine
