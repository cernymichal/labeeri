#include "Entities.h"

namespace labeeri::engine {

std::shared_ptr<Entity> Entities::Flycam(float speed) {
    auto entity = std::make_shared<Entity>();

    entity->m_camera = std::make_shared<Camera>(entity->transform());
    entity->m_input = std::make_shared<Input>();
    entity->m_movement = std::make_shared<Movement>(entity->transform());

    entity->m_input->m_onKeyboard = [speed](Entity& self, Keyboard key, int scanCode, KeyAction action, int mods) {
        if (action == KeyAction::Repeat)
            return;

        glm::vec3 direction(0.0f);
        if (key == Keyboard::W)
            direction = LAB_FORWARD;
        else if (key == Keyboard::S)
            direction = -LAB_FORWARD;
        else if (key == Keyboard::A)
            direction = -LAB_RIGHT;
        else if (key == Keyboard::D)
            direction = LAB_RIGHT;
        else if (key == Keyboard::Space)
            direction = LAB_UP;
        else if (key == Keyboard::LeftControl)
            direction = -LAB_UP;

        if (action == KeyAction::Press)
            self.m_movement->m_velocity += direction * speed;
        else if (action == KeyAction::Release && glm::length2(self.m_movement->m_velocity * direction) != 0)
            self.m_movement->m_velocity -= direction * speed;
    };

    entity->m_input->m_onMouseMove = [](Entity& self, glm::dvec2 mousePos, glm::dvec2 mouseDelta) {
        self.transform()->rotate(glm::quat(glm::dvec3(mouseDelta.y, mouseDelta.x, 0) * -0.005));
    };

    return entity;
}

}  // namespace labeeri::engine