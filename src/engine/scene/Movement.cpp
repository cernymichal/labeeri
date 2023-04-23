#include "Movement.h"

namespace labeeri::engine {

Movement::Movement(const std::shared_ptr<Transform>& transform) : m_transform(transform) {
}

void Movement::update(double deltaTime) {
    m_transform->move(m_velocity * static_cast<float>(deltaTime));
}

}  // namespace labeeri::engine
