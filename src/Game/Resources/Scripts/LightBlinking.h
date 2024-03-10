#pragma once

#include "Engine/API.h"

namespace labeeri {

/**
 * @brief Script to make a light entity blink every now and then.
 */
class LightBlinking : public IScript {
public:
    /**
     * @param minDelay Minimum delay between blink batches.
     * @param maxDelay Maximum delay between blink batches.
     * @param duration Duration of a single blink.
     */
    explicit LightBlinking(Entity entity, double minDelay = 4.0, double maxDelay = 12.0, double seriesMinDelay = 0.1, double seriesMaxDelay = 0.25, double seriesChance = 0.6, double blinkDuration = 0.08)
        : IScript(entity), m_minDelay(minDelay), m_maxDelay(maxDelay), m_seriesMinDelay(seriesMinDelay), m_seriesMaxDelay(seriesMaxDelay), m_seriesChance(seriesChance), m_blinkDuration(blinkDuration) {
    }

protected:
    virtual void onFixedUpdate(const FixedUpdateEvent& e) override {
        auto currentTime = LAB_CURRENT_SCENE->time();
        if (currentTime < m_nextBlink)
            return;

        auto light = m_entity.getComponent<Light>();

        if (!m_blinked) {
            m_originalIntensity = light->m_intensity;
            light->m_intensity = 0.1f;
            m_blinked = true;
        }
        else if (currentTime - m_nextBlink >= m_blinkDuration) {
            light->m_intensity = m_originalIntensity;
            m_blinked = false;
            if (random<double>() < m_seriesChance)
                m_nextBlink = currentTime + random<double>(m_seriesMinDelay, m_seriesMaxDelay);
            else
                m_nextBlink = currentTime + random<double>(m_minDelay, m_maxDelay);
        }
    }

private:
    double m_minDelay;
    double m_maxDelay;
    double m_seriesMinDelay;
    double m_seriesMaxDelay;
    double m_seriesChance;
    double m_blinkDuration;

    double m_nextBlink = 0.0;
    bool m_blinked = false;
    float m_originalIntensity = 1.0f;
};

}  // namespace labeeri
