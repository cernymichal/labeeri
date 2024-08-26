#pragma once

namespace labeeri::Engine {

/**
 * @brief A shared mesh resource.
 */
class MeshResource {
public:
    const LAB_GL_HANDLE m_vertexArrayObject;
    const LAB_GL_HANDLE m_vertexBufferObject;
    const LAB_GL_HANDLE m_elementBufferObject;
    const u32 m_triangleCount;

    /**
     * @param vertexArrayObject The vertex array object.
     * @param vertexBufferObject The vertex buffer object.
     * @param elementBufferObject The element buffer object.
     * @param triangleCount The number of triangles in the mesh.
     */
    MeshResource(LAB_GL_HANDLE vertexArrayObject, LAB_GL_HANDLE vertexBufferObject, LAB_GL_HANDLE elementBufferObject, u32 triangleCount)
        : m_vertexArrayObject(vertexArrayObject), m_vertexBufferObject(vertexBufferObject), m_elementBufferObject(elementBufferObject), m_triangleCount(triangleCount) {
    }

    /**
     * @param other The mesh resource to move.
     */
    MeshResource(MeshResource&& other) noexcept
        : m_vertexArrayObject(other.m_vertexArrayObject), m_vertexBufferObject(other.m_vertexBufferObject), m_elementBufferObject(other.m_elementBufferObject), m_triangleCount(other.m_triangleCount) {
        other.m_moved = true;
    }

    MeshResource& operator=(const MeshResource&) = delete;

    /**
     * @param other The mesh resource to move.
     */
    MeshResource& operator=(MeshResource&& other) noexcept {
        if (this == &other)
            return *this;

        this->~MeshResource();
        new (this) MeshResource(std::move(other));
        return *this;
    }

    /**
     * @brief Destroy the mesh resource. Calls deleteMesh on the renderer.
     */
    ~MeshResource();

private:
    bool m_moved = false;
};

}  // namespace labeeri::Engine
