#pragma once

#include "Engine/Scene/ECS/ISystem.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class LightSystem : public ECS::ISystem {
public:
    virtual ECS::ComponentSignature signature(const ECS::Instance& ecs) const override;

    /**
     * @brief TODO
     */
    void bindLights() const;
};

}  // namespace labeeri::Engine
