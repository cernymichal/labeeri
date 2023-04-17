#include "Entity.h"

Entity::Entity() {
}

Entity::~Entity() {
    m_transform->m_destroyed = true;
}

const std::shared_ptr<Transform>& Entity::transform() const {
    return m_transform;
}
