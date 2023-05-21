#pragma once

#include "Engine/Scene/ECS/ISystem.h"

namespace labeeri::Engine {

class Entity;

/**
 * @brief TODO
 */
class PhysicsSystem : public ECS::ISystem {
public:
    virtual ECS::ComponentSignature signature(const ECS::Instance& ecs) const override;

    /**
     * @brief TODO
     */
    void update(double deltaTime);

    /**
     * @brief TODO
     */
    bool collides(Entity entity) const;
};

}  // namespace labeeri::Engine
