#pragma once

#include "Engine/Resources/Scripts/IScript.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class PlayerController : public IScript {
public:
    /**
     * @brief TODO
     */
    explicit PlayerController(Entity entity, float speed = 2.0f, double mouseSensitivity = 0.002)
        : IScript(entity), m_speed(speed), m_mouseSensitivity(mouseSensitivity) {
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
    glm::vec2 m_viewAngles = glm::vec2(0.0f);
    glm::vec3 m_direction = glm::vec3(0.0f);
};

}  // namespace labeeri::Engine
