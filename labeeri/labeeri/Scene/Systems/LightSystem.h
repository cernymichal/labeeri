#pragma once

#include "Scene/ECS/ISystem.h"

namespace labeeri {

/**
 * @brief A system holding all lights in the scene and binding them.
 */
class LightSystem : public ECS::ISystem {
public:
    virtual ECS::ComponentSignature signature(const ECS::Instance& ecs) const override;

    /**
     * @brief Binds all lights in the scene to the renderer.
     */
    void bindLights() const;
};

}  // namespace labeeri
