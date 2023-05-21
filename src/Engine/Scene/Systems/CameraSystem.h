#pragma once

#include "Engine/Scene/ECS/ISystem.h"

namespace labeeri::Engine {

class Entity;

/**
 * @brief TODO
 */
class CameraSystem : public ECS::ISystem {
public:
    virtual ECS::ComponentSignature signature(const ECS::Instance& ecs) const override;
};

}  // namespace labeeri::Engine
