#pragma once

#include "Engine/Scene/ECS/ISystem.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class RenderSystem : public ECS::ISystem {
public:
    virtual ECS::ComponentSignature signature(const ECS::Instance& ecs) const override;

    /**
     * @brief TODO
     */
    void drawOpaque();

    /**
     * @brief TODO
     */
    void drawTransparent();

    /**
     * @brief TODO
     */
    void drawIds();
};

/**
 * @brief TODO
 */
class LightSystem : public ECS::ISystem {
public:
    virtual ECS::ComponentSignature signature(const ECS::Instance& ecs) const override;

    /**
     * @brief TODO
     */
    void bindLights();
};

}  // namespace labeeri::Engine
