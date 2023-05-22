#pragma once

#include "Engine/API.h"

namespace labeeri {

/**
 * @brief TODO
 */
class RotatingMovement : public IScript {
public:
    /**
     * @brief TODO
     */
    explicit RotatingMovement(Entity entity, quat rotation)
        : IScript(entity), m_rotation(rotation) {
    }

protected:
    virtual void onFixedUpdate(const FixedUpdateEvent& e) override {
        auto transform = m_entity.getComponent<Transform>();
        transform->rotate(m_rotation);
    }

private:
    quat m_rotation;
};

}  // namespace labeeri::Engine
