#pragma once

#include "Engine/Events/IEventReceiver.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Scene/Transform.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Look : IEventReceiver {
public:
    /**
     * @brief TODO
     */
    explicit Look(const Ref<Transform>& transform, double sensitivity = 0.002);

    virtual void onEvent(IEvent& e) override;

private:
    Ref<Transform> m_transform;
    double m_sensitivity;
    glm::vec2 m_viewAngles = glm::vec2(0.0f);

    bool onMouseMove(const MouseMoveEvent& e);
};

}  // namespace labeeri::Engine
