#pragma once

#include "Engine/Renderer/Mesh.h"
#include "Engine/Resources/Material.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Model {
public:
    MaterialRef m_material;
    MeshRef m_mesh;

    /**
     * @brief TODO
     */
    Model(MaterialRef material, MeshRef mesh);

private:
    /**
     * @brief TODO
     */
    void draw(const glm::mat4& modelMatrix) const;

    friend class ViewportLayer;
};

using ModelRef = std::shared_ptr<Model>;

}  // namespace labeeri::Engine
