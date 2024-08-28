#pragma once

#include "Resources/Scripts/IScript.h"

namespace labeeri {

/**
 * @brief Script for controlling a flying entity.
 */
class FlycamController : public IScript {
public:
    /**
     * @param entity The entity to control.
     * @param speed The speed to move the entity.
     * @param mouseSensitivity The mouse sensitivity to rotate the entity.
     */
    explicit FlycamController(Entity entity, f32 speed = 2.0f, f64 mouseSensitivity = 0.002);

protected:
    virtual void onUpdate(const UpdateEvent& e) override;

    virtual void onMouseMove(const MouseMoveEvent& e) override;

    virtual void onKeyboardPress(const KeyboardPressEvent& e) override;

    virtual void onKeyboardRelease(const KeyboardReleaseEvent& e) override;

private:
    f32 m_speed;
    f64 m_mouseSensitivity;
    bool m_sprinting = false;
    vec2 m_viewAngles = vec2(0.0f);
    vec3 m_direction = vec3(0.0f);
};

}  // namespace labeeri
