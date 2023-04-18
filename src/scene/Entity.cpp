#include "Entity.h"

Entity::Entity() {
}

Entity::~Entity() {
    m_transform->destroy();
}

const std::shared_ptr<Transform>& Entity::transform() const {
    return m_transform;
}
