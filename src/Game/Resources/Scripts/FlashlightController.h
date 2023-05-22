#pragma once

#include "Engine/API.h"

namespace labeeri {

/**
 * @brief TODO
 */
class FlashlightController : public IScript {
public:
    /**
     * @brief TODO
     */
    explicit FlashlightController(Entity player)
        : IScript(player) {
    }

protected:
    virtual void onKeyboardPress(const KeyboardPressEvent& e) {
        if (e.m_key == KeyboardKey::F) {
            auto flashlight = m_entity.getComponent<Light>();
            if (flashlight->m_intensity == 0.0f)
                flashlight->m_intensity = 1.0f;
            else
                flashlight->m_intensity = 0.0f;
        }
    }
};

}  // namespace labeeri
