#pragma once

#include "Engine/API.h"

namespace labeeri {

/**
 * @brief Script moving the entity up and down in world space.
 */
class FloatingMovement : public IScript {
public:
    /**
     * @param entity The entity to move.
     * @param maxDelta The maximum delta to move the entity.
     */
    explicit FloatingMovement(Entity entity, f32 maxDelta = 1.0f)
        : IScript(entity), m_maxDelta(maxDelta) {
    }

protected:
    virtual void onFixedUpdate(const FixedUpdateEvent& e) override {
        auto transform = m_entity.getComponent<Transform>();
        transform->moveWorld(vec3(0, glm::sin(LAB_CURRENT_SCENE->time()) * m_maxDelta * FIXED_UPDATE_INTERVAL, 0));
    }

private:
    f32 m_maxDelta;
};

}  // namespace labeeri
