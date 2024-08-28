#pragma once

/**
 * @brief Script for controlling a spotlight that the player entity has.
 */
class FlashlightController : public IScript {
public:
    /**
     * @param player The player entity.
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
