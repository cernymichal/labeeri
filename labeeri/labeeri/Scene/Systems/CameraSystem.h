#pragma once

#include "Scene/ECS/ISystem.h"

namespace labeeri {

class Entity;

/**
 * @brief A system holding all cameras in the scene.
 */
class CameraSystem : public ECS::ISystem {
public:
    virtual ECS::ComponentSignature signature(const ECS::Instance& ecs) const override;
};

}  // namespace labeeri
