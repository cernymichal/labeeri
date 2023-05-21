#include "FlycamController.h"

#include "Engine/Scene/Components/RigidBody.h"
#include "Engine/Scene/Components/Transform.h"

namespace labeeri::Engine {

static glm::vec3 directionFromKey(KeyboardKey key) {
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

void FlycamController::onUpdate(const UpdateEvent& e) {
    auto transform = m_entity.getComponent<Transform>();
    auto rigidBody = m_entity.getComponent<RigidBody>();

    auto horizontalDirection = glm::vec3(m_direction.x, 0, m_direction.z);
    auto verticalDirection = glm::vec3(0, m_direction.y, 0);

    if (horizontalDirection != glm::vec3(0.0f)) {
        auto directionWorld = glm::normalize(transform->rotation() * horizontalDirection);
        rigidBody->m_velocity = directionWorld * m_speed;
    }
    else
        rigidBody->m_velocity = glm::vec3(0.0f);

    rigidBody->m_velocity += verticalDirection * m_speed;
}

void FlycamController::onMouseMove(const MouseMoveEvent& e) {
    m_viewAngles += e.m_delta * -m_mouseSensitivity;

    m_viewAngles.y = glm::clamp(m_viewAngles.y, -glm::half_pi<float>(), glm::half_pi<float>());
    m_viewAngles.x = glm::mod(m_viewAngles.x, glm::two_pi<float>());

    m_entity.getComponent<Transform>()->setRotation(glm::vec3(m_viewAngles.y, m_viewAngles.x, 0.0f));
}

void FlycamController::onKeyboardPress(const KeyboardPressEvent& e) {
    glm::vec3 direction = directionFromKey(e.m_key);
    m_direction += direction;
}

void FlycamController::onKeyboardRelease(const KeyboardReleaseEvent& e) {
    glm::vec3 direction = directionFromKey(e.m_key);
    m_direction -= direction;
}

}  // namespace labeeri::Engine
