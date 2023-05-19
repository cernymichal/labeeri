#pragma once

#include "Engine/Resources/Scripts/IScript.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class CharacterController : public IScript {
public:
    /**
     * @brief TODO
     */
    explicit CharacterController(Entity entity, float speed = 4.0f, double mouseSensitivity = 0.002)
        : m_speed(speed), m_mouseSensitivity(mouseSensitivity), IScript(entity) {
    }

protected:
    virtual void onMouseMove(const MouseMoveEvent& e);

    virtual void onKeyboardPress(const KeyboardPressEvent& e);

    virtual void onKeyboardRelease(const KeyboardReleaseEvent& e);

private:
    float m_speed;
    double m_mouseSensitivity;
    glm::vec2 m_viewAngles = glm::vec2(0.0f);
};

}  // namespace labeeri::Engine
