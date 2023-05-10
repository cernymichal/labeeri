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
    explicit EntityWindow(const Ref<Entity>& entity);

    /**
     * @brief TODO
     */
    virtual void draw() override;

private:
    Ref<Entity> m_entity;
    std::string m_name;
    glm::vec3 m_position;
    glm::quat m_rotation;
};

}  // namespace labeeri::Engine
