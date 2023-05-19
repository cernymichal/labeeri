#pragma once

#include "Engine/Events/IEvent.h"
#include "Engine/Scene/ECS/Entity.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class EntityClickEvent : public IEvent {
public:
    const Entity m_entity;

    EntityClickEvent(Entity entity) : m_entity(entity) {
    }

    EVENT_CLASS_TYPE(EntityClick)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Application) | static_cast<int>(EventCategory::Scene))
};

}  // namespace labeeri::Engine
