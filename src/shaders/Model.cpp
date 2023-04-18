#include "Model.h"

Mesh::Mesh(GLuint vertexArrayObject, GLuint vertexBufferObject, GLuint elementBufferObject, uint32_t triangleCount)
    : m_elementBufferObject(elementBufferObject), m_vertexBufferObject(vertexBufferObject), m_vertexArrayObject(vertexArrayObject), m_triangleCount(triangleCount) {
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_vertexArrayObject);
    glDeleteBuffers(1, &m_elementBufferObject);
    glDeleteBuffers(1, &m_vertexBufferObject);
}

void Mesh::draw() const {
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, m_triangleCount * 3, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

Model::Model(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh) : m_material(material), m_mesh(mesh) {
}

void Model::draw(double time, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    glUseProgram(m_material->m_shader->m_program);

    m_material->bindUniforms(time, modelMatrix, viewMatrix, projectionMatrix);
    m_mesh->draw();

    glUseProgram(0);
}
