#pragma once

#include "Engine/Renderer/MeshResource.h"
#include "Engine/Resources/MaterialResource.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class ModelResource {
public:
    Ref<MaterialResource> m_material;
    Ref<MeshResource> m_mesh;

    /**
     * @brief TODO
     */
    ModelResource(const Ref<MaterialResource>& material, const Ref<MeshResource>& mesh) : m_material(material), m_mesh(mesh) {
    }
};

}  // namespace labeeri::Engine
