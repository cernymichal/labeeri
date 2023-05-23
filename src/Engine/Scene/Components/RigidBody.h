#pragma once

namespace labeeri::Engine {

/**
 * @brief Rigidbody component.
 */
class RigidBody {
public:
    vec3 m_velocity = vec3(0.0f);
    vec3 m_acceleration = vec3(0.0f);
    bool m_static = false;

    /**
     * @brief Create a new static rigid body.
     * 
     * Useful for colliders that are not supposed to move.
     *
     * @return The created rigid body.
     */
    static RigidBody Static() {
        RigidBody rigidBody;
        rigidBody.m_static = true;
        return rigidBody;
    }
};

}  // namespace labeeri::Engine
