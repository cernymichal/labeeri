#include "Model.h"

#include <GL/glew.h>

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

    glDeleteVertexArrays(1, &m_vertexArrayObject);
    glDeleteBuffers(1, &m_elementBufferObject);
    glDeleteBuffers(1, &m_vertexBufferObject);
}

void Mesh::draw() const {
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, m_triangleCount * 3, GL_UNSIGNED_INT, nullptr);
    //glBindVertexArray(0);

    LAB_LOG_OGL_ERROR();
}

Model::Model(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh) : m_material(material), m_mesh(mesh) {
}

void Model::draw(double time, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    auto& shader = m_material->m_shader;
    if (!shader)
        shader = Shaders::basic();

    glUseProgram(*shader);

    m_material->bindUniforms(time, modelMatrix, viewMatrix, projectionMatrix);
    m_mesh->draw();

    // glUseProgram(0);

    LAB_LOG_OGL_ERROR();
}

}  // namespace labeeri::Engine
