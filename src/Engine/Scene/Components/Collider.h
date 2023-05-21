#pragma once

#include "Engine/Scene/Components/Transform.h"

namespace labeeri::Engine {

enum class ColliderType : uint8_t {
    AABB  // Axis Aligned Bounding Box
};

/**
 * @brief TODO
 */
class Collider {
public:
    ColliderType m_type;
    glm::vec3 m_center;
    glm::vec3 m_extents;

    explicit Collider(ColliderType type = ColliderType::AABB, glm::vec3 extents = glm::vec3(0.5f), glm::vec3 center = glm::vec3(0.0f))
        : m_type(type), m_center(center), m_extents(extents) {}

    /**
     * @brief TODO
     */
    static Collider AABB(glm::vec3 extents = glm::vec3(0.5f), glm::vec3 center = glm::vec3(0.0f)) {
        return Collider(ColliderType::AABB, extents, center);
    }
};

}  // namespace labeeri::Engine
