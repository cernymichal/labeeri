#pragma once

#include "Events/IEvent.h"
#include "Scene/ECS/Entity.h"

namespace labeeri {

/**
 * @brief Entity clicked event.
 */
class EntityClickEvent : public IEvent {
public:
    const Entity m_entity;

    EntityClickEvent(Entity entity) : m_entity(entity) {
    }

    EVENT_CLASS_TYPE(EntityClick)

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Application) | static_cast<i32>(EventCategory::Scene))
};

}  // namespace labeeri
