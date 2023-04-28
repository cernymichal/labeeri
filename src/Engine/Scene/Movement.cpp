#include "Movement.h"

namespace labeeri::Engine {

glm::vec3 directionFromKey(KeyboardKey key) {
    glm::vec3 direction(0.0f);
    if (key == KeyboardKey::W)
        direction = LAB_FORWARD;
    else if (key == KeyboardKey::S)
        direction = -LAB_FORWARD;
    else if (key == KeyboardKey::A)
        direction = -LAB_RIGHT;
    else if (key == KeyboardKey::D)
        direction = LAB_RIGHT;
    else if (key == KeyboardKey::Space)
        direction = LAB_UP;
    else if (key == KeyboardKey::LeftControl)
        direction = -LAB_UP;

    return direction;
}

Movement::Movement(const std::shared_ptr<Transform>& transform, float speed) : m_transform(transform), m_speed(speed) {
}

void Movement::update(double deltaTime) {
    m_transform->move(m_velocity * static_cast<float>(deltaTime));
}

void Movement::onEvent(IEvent& e) {
    e.dispatch<KeyboardPressEvent>(LAB_BIND_EVENT_FUNC(Movement::onKeyboardPress));
    e.dispatch<KeyboardReleaseEvent>(LAB_BIND_EVENT_FUNC(Movement::onKeyboardRelease));
}

bool Movement::onKeyboardPress(const KeyboardPressEvent& e) {
    glm::vec3 direction = directionFromKey(e.key());
    m_velocity += direction * m_speed;
    return false;
}

bool Movement::onKeyboardRelease(const KeyboardReleaseEvent& e) {
    glm::vec3 direction = directionFromKey(e.key());
    m_velocity -= direction * m_speed;
    return false;
}

}  // namespace labeeri::Engine
