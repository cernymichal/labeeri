#pragma once

#include "Engine/API.h"

namespace labeeri {

/**
 * @brief TODO
 */
class MaxwellInteraction : public IScript {
public:
    /**
     * @brief TODO
     */
    explicit MaxwellInteraction(Entity entity)
        : IScript(entity) {
    }

protected:
    virtual void onEntityClick(const EntityClickEvent& e) override {
        m_enabled = !m_enabled;
    }

    virtual void onFixedUpdate(const FixedUpdateEvent& e) override {
        if (!m_enabled)
            return;

        auto transform = m_entity.getComponent<Transform>();
        transform->rotate(m_rotation);
    }

private:
    bool m_enabled = false;
    quat m_rotation = glm::radians(vec3(0.0f, -2.0f, 0.0f));
};

}  // namespace labeeri
