#pragma once

#include "Engine/Renderer/MeshResource.h"
#include "Engine/Resources/MaterialResource.h"

namespace labeeri::Engine {

/**
 * @brief A shared model resource. Pair of a material and a mesh.
 */
class ModelResource {
public:
    Ref<MaterialResource> m_material;
    Ref<MeshResource> m_mesh;

    /**
     * @param material The material of the model.
     * @param mesh The mesh of the model.
     */
    ModelResource(const Ref<MaterialResource>& material, const Ref<MeshResource>& mesh) : m_material(material), m_mesh(mesh) {
    }
};

}  // namespace labeeri::Engine
