#include "Look.h"

namespace labeeri::Engine {

Look::Look(const std::shared_ptr<Transform>& transform, double sensitivity) : m_transform(transform), m_sensitivity(sensitivity) {
}

void Look::onEvent(Event& e) {
    e.dispatch<MouseMoveEvent>(LAB_BIND_EVENT_FUNC(Look::onMouseMove));
}

bool Look::onMouseMove(const MouseMoveEvent& e) {
    m_viewAngles += e.delta() * -m_sensitivity;

    m_viewAngles.y = glm::clamp(m_viewAngles.y, -glm::half_pi<float>(), glm::half_pi<float>());
    m_viewAngles.x = glm::mod(m_viewAngles.x, glm::two_pi<float>());

    m_transform->setRotation(glm::vec3(m_viewAngles.y, m_viewAngles.x, 0.0f));

    return false;
}

}  // namespace labeeri::Engine