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
    void drawOpaque() const;

    /**
     * @brief TODO
     */
    void drawTransparent() const;

    /**
     * @brief TODO
     */
    void drawIds() const;
};

}  // namespace labeeri::Engine
