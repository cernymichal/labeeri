#include "Model.h"

#include "Engine/Renderer/IRenderer.h"
#include "Engine/Resources/Resources.h"

namespace labeeri::Engine {

Model::Model(const Ref<Material>& material, const Ref<Mesh>& mesh) : m_material(material), m_mesh(mesh) {
}

void Model::draw(const glm::mat4& modelMatrix) const {
    auto& shader = m_material->m_shader;
    if (!shader)
        shader = Shaders::flat();

    LAB_RENDERER->useShaderProgram(shader);
    LAB_RENDERER->bindMesh(m_mesh);
    LAB_RENDERER->bindPVM(modelMatrix);
    m_material->bindUniforms();

    LAB_RENDERER->drawMesh();

    LAB_LOG_RENDERAPI_ERROR();
}

}  // namespace labeeri::Engine
