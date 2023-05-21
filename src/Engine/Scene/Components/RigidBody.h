#pragma once

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class RigidBody {
public:
    vec3 m_velocity = vec3(0.0f);
    vec3 m_acceleration = vec3(0.0f);
    bool m_static = false;

    /**
     * @brief TODO
     */
    static RigidBody Static() {
        RigidBody rigidBody;
        rigidBody.m_static = true;
        return rigidBody;
    }
};

}  // namespace labeeri::Engine
