#pragma once

#include "Engine/Scene/Components/Transform.h"

namespace labeeri::Engine {

enum class ColliderType : uint8_t {
    AABB  // Axis Aligned Bounding Box
};

/**
 * @brief Component describing a collider of an entity.
 */
class Collider {
public:
    ColliderType m_type;
    vec3 m_center;
    vec3 m_extents;
    bool m_enabled = true;

    /**
     * @brief Creates a new collider.
     *
     * @param type Type of the collider.
     * @param extents Size of the collider from the center.
     * @param center Center of the collider in relation to the entity transform's postion.
     */
    explicit Collider(ColliderType type = ColliderType::AABB, vec3 extents = vec3(0.5f), vec3 center = vec3(0.0f))
        : m_type(type), m_center(center), m_extents(extents) {}

    /**
     * @brief Creates a new AABB collider.
     *
     * @param extents Size of the collider from the center.
     * @param center Center of the collider in relation to the entity transform's postion.
     * @return The created collider component.
     */
    static Collider AABB(vec3 extents = vec3(0.5f), vec3 center = vec3(0.0f)) {
        return Collider(ColliderType::AABB, extents, center);
    }
};

}  // namespace labeeri::Engine
