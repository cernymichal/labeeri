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
        : IScript(entity), m_speed(speed), m_mouseSensitivity(mouseSensitivity) {
    }

protected:
    virtual void onMouseMove(const MouseMoveEvent& e) override;

    virtual void onKeyboardPress(const KeyboardPressEvent& e) override;

    virtual void onKeyboardRelease(const KeyboardReleaseEvent& e) override;

private:
    float m_speed;
    double m_mouseSensitivity;
    glm::vec2 m_viewAngles = glm::vec2(0.0f);
};

}  // namespace labeeri::Engine
