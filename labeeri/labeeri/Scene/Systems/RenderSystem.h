#pragma once

#include "Scene/ECS/ISystem.h"

namespace labeeri {

/**
 * @brief A system holding all renderable entities in the scene for rendering.
 */
class RenderSystem : public ECS::ISystem {
public:
    virtual ECS::ComponentSignature signature(const ECS::Instance& ecs) const override;

    /**
     * @brief Draw all opaque objects
     */
    void drawOpaque() const;

    /**
     * @brief Draw all transparent objects
     */
    void drawTransparent() const;

    /**
     * @brief Draw integer ids of all objects
     */
    void drawIds() const;
};

}  // namespace labeeri
