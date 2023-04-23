#include "Entity.h"

namespace labeeri::engine {

Entity::Entity() {
}

Entity::~Entity() {
    m_transform->destroy();
}

const std::shared_ptr<Transform>& Entity::transform() const {
    return m_transform;
}

void Entity::fixedUpdate() {
    if (!m_enabled)
        return;

    if (m_onFixedUpdate)
        m_onFixedUpdate(*this);
}

void Entity::update(double deltaTime) {
    if (!m_enabled)
        return;

    if (m_onUpdate)
        m_onUpdate(*this, deltaTime);

    if (m_movement)
        m_movement->update(deltaTime);
}

}  // namespace labeeri::engine
