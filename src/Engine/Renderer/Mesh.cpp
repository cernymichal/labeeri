#include "Mesh.h"

#include "Engine/Renderer/IRenderer.h"

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

}  // namespace labeeri::Engine
