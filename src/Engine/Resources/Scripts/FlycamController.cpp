#include "FlycamController.h"

#include "Engine/Scene/Components/RigidBody.h"
#include "Engine/Scene/Components/Transform.h"

namespace labeeri::Engine {

static vec3 directionFromKey(KeyboardKey key) {
    vec3 direction(0.0f);
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

FlycamController::FlycamController(Entity entity, f32 speed, f64 mouseSensitivity)
    : IScript(entity), m_speed(speed), m_mouseSensitivity(mouseSensitivity) {
    auto transform = m_entity.getComponent<Transform>();
    vec3 eulerAngles = glm::eulerAngles(transform->rotation());
    m_viewAngles = {eulerAngles.y, eulerAngles.x};
}

void FlycamController::onUpdate(const UpdateEvent& e) {
    auto transform = m_entity.getComponent<Transform>();
    auto rigidBody = m_entity.getComponent<RigidBody>();

    auto horizontalDirection = vec3(m_direction.x, 0, m_direction.z);
    auto verticalDirection = vec3(0, m_direction.y, 0);

    if (horizontalDirection != vec3(0.0f)) {
        auto directionWorld = glm::normalize(transform->rotation() * horizontalDirection);
        rigidBody->m_velocity = directionWorld * m_speed * (m_sprinting ? 2.0f : 1.0f);
    }
    else
        rigidBody->m_velocity = vec3(0.0f);

    rigidBody->m_velocity += verticalDirection * m_speed;
}

void FlycamController::onMouseMove(const MouseMoveEvent& e) {
    m_viewAngles += e.m_delta * -m_mouseSensitivity;

    m_viewAngles.y = glm::clamp(m_viewAngles.y, -glm::half_pi<f32>(), glm::half_pi<f32>());
    m_viewAngles.x = glm::mod(m_viewAngles.x, glm::two_pi<f32>());

    m_entity.getComponent<Transform>()->setRotation(vec3(m_viewAngles.y, m_viewAngles.x, 0.0f));
}

void FlycamController::onKeyboardPress(const KeyboardPressEvent& e) {
    vec3 direction = directionFromKey(e.m_key);
    m_direction += direction;

    if (e.m_key == KeyboardKey::LeftShift)
        m_sprinting = true;
}

void FlycamController::onKeyboardRelease(const KeyboardReleaseEvent& e) {
    vec3 direction = directionFromKey(e.m_key);
    m_direction -= direction;

    if (e.m_key == KeyboardKey::LeftShift)
        m_sprinting = false;
}

}  // namespace labeeri::Engine
