#pragma once

#include "Engine/Resources/Scripts/IScript.h"

namespace labeeri::Engine {

/**
 * @brief Script that controls the player entity on a 2D plane, with sprint.
 */
class PlayerController : public IScript {
public:
    /**
     * @param player The player entity.
     * @param speed The speed to move the player.
     * @param mouseSensitivity The mouse sensitivity to rotate the player.
     */
    explicit PlayerController(Entity player, float speed = 2.0f, double mouseSensitivity = 0.002)
        : IScript(player), m_speed(speed), m_mouseSensitivity(mouseSensitivity) {
    }

protected:
    virtual void onUpdate(const UpdateEvent& e) override;

    virtual void onMouseMove(const MouseMoveEvent& e) override;

    virtual void onKeyboardPress(const KeyboardPressEvent& e) override;

    virtual void onKeyboardRelease(const KeyboardReleaseEvent& e) override;

private:
    float m_speed;
    double m_mouseSensitivity;
    bool m_sprinting = false;
    vec2 m_viewAngles = vec2(0.0f);
    vec3 m_direction = vec3(0.0f);
};

}  // namespace labeeri::Engine
