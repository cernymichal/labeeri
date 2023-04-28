#include "Model.h"

#include "Engine/Renderer/IRenderer.h"
#include "Engine/Resources/Resources.h"

namespace labeeri::Engine {

Mesh::Mesh(LAB_GL_HANDLE vertexArrayObject, LAB_GL_HANDLE vertexBufferObject, LAB_GL_HANDLE elementBufferObject, uint32_t triangleCount)
    : m_elementBufferObject(elementBufferObject), m_vertexBufferObject(vertexBufferObject), m_vertexArrayObject(vertexArrayObject), m_triangleCount(triangleCount) {
}

Mesh::Mesh(Mesh&& other) noexcept
    : m_elementBufferObject(other.m_elementBufferObject), m_vertexBufferObject(other.m_vertexBufferObject), m_vertexArrayObject(other.m_vertexArrayObject), m_triangleCount(other.m_triangleCount) {
    other.m_moved = true;
}

Mesh::~Mesh() {
    if (m_moved)
        return;

    LAB_RENDERER->deleteMesh(*this);
}

Model::Model(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh) : m_material(material), m_mesh(mesh) {
}

void Model::draw(const glm::mat4& modelMatrix) const {
    auto& shader = m_material->m_shader;
    if (!shader)
        shader = Shaders::basic();

    LAB_RENDERER->useShaderProgram(shader);
    LAB_RENDERER->bindMesh(*m_mesh);
    LAB_RENDERER->bindPVM(modelMatrix);
    m_material->bindUniforms();

    LAB_RENDERER->drawMesh(*m_mesh);

    LAB_LOG_OGL_ERROR();
}

}  // namespace labeeri::Engine
