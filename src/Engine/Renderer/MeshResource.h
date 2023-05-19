#pragma once

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class MeshResource {
public:
    const LAB_GL_HANDLE m_vertexArrayObject;
    const LAB_GL_HANDLE m_vertexBufferObject;
    const LAB_GL_HANDLE m_elementBufferObject;
    const uint32_t m_triangleCount;

    /**
     * @brief TODO
     */
    MeshResource(LAB_GL_HANDLE vertexArrayObject, LAB_GL_HANDLE vertexBufferObject, LAB_GL_HANDLE elementBufferObject, uint32_t triangleCount)
        : m_vertexArrayObject(vertexArrayObject), m_vertexBufferObject(vertexBufferObject), m_elementBufferObject(elementBufferObject), m_triangleCount(triangleCount) {
    }

    /**
     * @brief TODO
     */
    MeshResource(MeshResource&& other) noexcept
        : m_vertexArrayObject(other.m_vertexArrayObject), m_vertexBufferObject(other.m_vertexBufferObject), m_elementBufferObject(other.m_elementBufferObject), m_triangleCount(other.m_triangleCount) {
        other.m_moved = true;
    }

    MeshResource& operator=(const MeshResource&) = delete;

    MeshResource& operator=(MeshResource&& other) noexcept {
        if (this == &other)
            return *this;

        this->~MeshResource();
        new (this) MeshResource(std::move(other));
        return *this;
    }

    /**
     * @brief TODO
     */
    ~MeshResource();

private:
    bool m_moved = false;
};

}  // namespace labeeri::Engine
