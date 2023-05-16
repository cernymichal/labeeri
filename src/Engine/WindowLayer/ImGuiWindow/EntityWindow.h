#pragma once

#include "Engine/Scene/Entity.h"
#include "Engine/WindowLayer/ImGuiWindow/IImGuiWindow.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class EntityWindow : public IImGuiWindow {
public:
    /**
     * @brief TODO
     */
    explicit EntityWindow(const Ref<Entity>& entity, uint32_t id) : m_entity(entity) {
        m_name = std::format("Entity {:d}", id);
    }

    virtual const std::string& name() const override {
        return m_name;
    }

    virtual bool draw() override;

private:
    Ref<Entity> m_entity;
    std::string m_name;
    glm::vec3 m_position = glm::vec3(0);
    glm::vec3 m_rotationEuler = glm::vec3(0);
};

}  // namespace labeeri::Engine
