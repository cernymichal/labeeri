#pragma once

#include "Engine/Resources/Scripts/IScript.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class FlycamController : public IScript {
public:
    /**
     * @brief TODO
     */
    explicit FlycamController(Entity entity, float speed = 4.0f, double mouseSensitivity = 0.002)
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
    glm::vec2 m_viewAngles = glm::vec2(0.0f);
    glm::vec3 m_direction = glm::vec3(0.0f);
};

}  // namespace labeeri::Engine