#pragma once

#include "Engine/Scene/ECS/ISystem.h"

namespace labeeri::Engine {

class Entity;

/**
 * @brief Physics system handeling RigidBody updates and collisions.
 */
class PhysicsSystem : public ECS::ISystem {
public:
    virtual ECS::ComponentSignature signature(const ECS::Instance& ecs) const override;

    /**
     * @brief Update the RigidBody components and check for collisions.
     *
     * @param deltaTime The time since the last update.
     */
    void update(f64 deltaTime);

    /**
     * @brief Check if the entity collides with any other entity.
     *
     * @param entity The entity to check for collisions.
     * @return true If the entity collides with any other entity.
     */
    bool collides(Entity entity) const;
};

}  // namespace labeeri::Engine
