#pragma once

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Mesh {
public:
    const LAB_GL_HANDLE m_vertexArrayObject;
    const LAB_GL_HANDLE m_vertexBufferObject;
    const LAB_GL_HANDLE m_elementBufferObject;
    const uint32_t m_triangleCount;

    /**
     * @brief TODO
     */
    Mesh(LAB_GL_HANDLE vertexArrayObject, LAB_GL_HANDLE vertexBufferObject, LAB_GL_HANDLE elementBufferObject, uint32_t triangleCount)
        : m_vertexArrayObject(vertexArrayObject), m_vertexBufferObject(vertexBufferObject), m_elementBufferObject(elementBufferObject), m_triangleCount(triangleCount) {
    }

    /**
     * @brief TODO
     */
    Mesh(Mesh&& other) noexcept
        : m_vertexArrayObject(other.m_vertexArrayObject), m_vertexBufferObject(other.m_vertexBufferObject), m_elementBufferObject(other.m_elementBufferObject), m_triangleCount(other.m_triangleCount) {
        other.m_moved = true;
    }

    /**
     * @brief TODO
     */
    ~Mesh();

private:
    bool m_moved = false;
};

}  // namespace labeeri::Engine
