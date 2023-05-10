#include "EntityWindow.h"

#include <imgui.h>

namespace labeeri::Engine {

EntityWindow::EntityWindow(const Ref<Entity>& entity) : m_entity(entity), m_position(entity->transform()->position()), m_rotation(entity->transform()->rotation()) {
    m_name = std::format("Entity {:p}", (void*)entity.get());
}

void EntityWindow::draw() {
    ImGui::Begin(m_name.c_str());

    if (ImGui::InputFloat3("Location", glm::value_ptr(m_position)))
        m_entity->transform()->setPosition(m_position);

    if (ImGui::SliderFloat4("Rotation", glm::value_ptr(m_rotation), -1.0f, 1.0f))
        m_entity->transform()->setRotation(m_rotation);

    ImGui::End();
}

}  // namespace labeeri::Engine
