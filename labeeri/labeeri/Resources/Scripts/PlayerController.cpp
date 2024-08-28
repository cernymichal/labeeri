#include "PlayerController.h"

#include "Scene/Components/RigidBody.h"
#include "Scene/Components/Transform.h"

namespace labeeri {

static vec3 directionFromKey(KeyboardKey key) {
    vec3 direction(0.0f);
    if (key == KeyboardKey::W)
        direction = VEC_FORWARD;
    else if (key == KeyboardKey::S)
        direction = -VEC_FORWARD;
    else if (key == KeyboardKey::A)
        direction = -VEC_RIGHT;
    else if (key == KeyboardKey::D)
        direction = VEC_RIGHT;

    return direction;
}

PlayerController::PlayerController(Entity player, f32 speed, f64 mouseSensitivity)
    : IScript(player), m_speed(speed), m_mouseSensitivity(mouseSensitivity) {
    auto transform = m_entity.getComponent<Transform>();
    vec3 eulerAngles = glm::eulerAngles(transform->rotation());
    m_viewAngles = {eulerAngles.y, eulerAngles.x};
}

void PlayerController::onUpdate(const UpdateEvent& e) {
    auto transform = m_entity.getComponent<Transform>();
    auto rigidBody = m_entity.getComponent<RigidBody>();

    if (m_direction != vec3(0.0f)) {
        auto directionWorld = glm::normalize(quat(vec3(0.0f, m_viewAngles.x, 0.0f)) * m_direction);
        rigidBody->m_velocity = directionWorld * m_speed * (m_sprinting ? 2.0f : 1.0f);
    }
    else
        rigidBody->m_velocity = vec3(0.0f);
}

void PlayerController::onMouseMove(const MouseMoveEvent& e) {
    m_viewAngles += e.m_delta * -m_mouseSensitivity;

    m_viewAngles.y = glm::clamp(m_viewAngles.y, -glm::half_pi<f32>(), glm::half_pi<f32>());
    m_viewAngles.x = glm::mod(m_viewAngles.x, glm::two_pi<f32>());

    m_entity.getComponent<Transform>()->setRotation(vec3(m_viewAngles.y, m_viewAngles.x, 0.0f));
}

void PlayerController::onKeyboardPress(const KeyboardPressEvent& e) {
    vec3 direction = directionFromKey(e.m_key);
    m_direction += direction;

    if (e.m_key == KeyboardKey::LeftShift)
        m_sprinting = true;
}

void PlayerController::onKeyboardRelease(const KeyboardReleaseEvent& e) {
    vec3 direction = directionFromKey(e.m_key);
    m_direction -= direction;

    if (e.m_key == KeyboardKey::LeftShift)
        m_sprinting = false;
}

}  // namespace labeeri
