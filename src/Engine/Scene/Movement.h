#pragma once

#include "Engine/Events/IEventReceiver.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Scene/Transform.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Movement : IEventReceiver {
public:
    /**
     * @brief TODO
     */
    explicit Movement(const Ref<Transform>& transform, float speed = 4.0f);

    /**
     * @brief TODO
     */
    void update(double deltaTime);

    virtual void onEvent(IEvent& e) override;

private:
    glm::vec3 m_velocity = glm::vec3(0.0f);
    Ref<Transform> m_transform;
    float m_speed;

    bool onKeyboardPress(const KeyboardPressEvent& e);

    bool onKeyboardRelease(const KeyboardReleaseEvent& e);
};

}  // namespace labeeri::Engine
