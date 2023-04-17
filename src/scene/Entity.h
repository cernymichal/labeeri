#pragma once

#include "../shaders/Material.h"
#include "Transform.h"

/**
 * @brief TODO
 */
class Entity {
public:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;

    /**
     * @brief TODO
     */
    Entity();

    /**
     * @brief TODO
     */
    ~Entity();

    /**
     * @brief TODO
     */
    const std::shared_ptr<Transform>& transform() const;

private:
    std::shared_ptr<Transform> m_transform = std::make_shared<Transform>();
};
