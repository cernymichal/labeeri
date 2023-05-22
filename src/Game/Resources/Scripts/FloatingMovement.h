#pragma once

#include "Engine/API.h"

namespace labeeri {

/**
 * @brief TODO
 */
class FloatingMovement : public IScript {
public:
    /**
     * @brief TODO
     */
    explicit FloatingMovement(Entity entity, float maxDelta = 1.0f)
        : IScript(entity), m_maxDelta(maxDelta) {
    }

protected:
    virtual void onFixedUpdate(const FixedUpdateEvent& e) override {
        auto transform = m_entity.getComponent<Transform>();
        transform->moveWorld(vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * m_maxDelta * FIXED_UPDATE_INTERVAL, 0));
    }

private:
    float m_maxDelta;
};

}  // namespace labeeri::Engine
