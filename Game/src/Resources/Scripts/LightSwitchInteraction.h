#pragma once

/**
 * @brief Script for turning light on and off.
 */
class LightSwitchInteraction : public IScript {
public:
    explicit LightSwitchInteraction(Entity entity)
        : IScript(entity) {
    }

protected:
    virtual void onEntityClick(const EntityClickEvent& e) override {
        auto light = m_entity.getComponent<Light>();

        if (m_enabled) {
            m_intensity = light->m_intensity;
            light->m_intensity = 0.0f;
        }
        else
            light->m_intensity = m_intensity;

        m_enabled = !m_enabled;
    }

private:
    bool m_enabled = true;
    f32 m_intensity = 1.0f;
};
