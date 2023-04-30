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
    Mesh(LAB_GL_HANDLE vertexArrayObject, LAB_GL_HANDLE vertexBufferObject, LAB_GL_HANDLE elementBufferObject, uint32_t triangleCount);

    Mesh(const Mesh&) = delete;

    /**
     * @brief TODO
     */
    Mesh(Mesh&& other) noexcept;

    /**
     * @brief TODO
     */
    ~Mesh();

private:
    bool m_moved = false;
};

using MeshRef = std::shared_ptr<Mesh>;

}  // namespace labeeri::Engine
