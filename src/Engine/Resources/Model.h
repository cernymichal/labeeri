#pragma once

#include "Engine/Renderer/Mesh.h"
#include "Engine/Resources/Material.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Model {
public:
    Ref<Material> m_material;
    Ref<Mesh> m_mesh;

    /**
     * @brief TODO
     */
    Model(const Ref<Material>& material, const Ref<Mesh>& mesh) : m_material(material), m_mesh(mesh) {
    }

private:
    /**
     * @brief TODO
     */
    void draw(const glm::mat4& modelMatrix) const;

    friend class ViewportLayer;
};

}  // namespace labeeri::Engine
