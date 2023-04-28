#pragma once

#include "Engine/Resources/Material.h"

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

class Model {
public:
    std::shared_ptr<Material> m_material;
    std::shared_ptr<Mesh> m_mesh;

    /**
     * @brief TODO
     */
    Model(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh);

private:
    /**
     * @brief TODO
     */
    void draw(const glm::mat4& modelMatrix) const;

    friend class ViewportLayer;
};

}  // namespace labeeri::Engine
