#pragma once

#include <cstdint>

#include "Material.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
class Mesh {
public:
    const GLuint m_vertexArrayObject;
    const GLuint m_vertexBufferObject;
    const GLuint m_elementBufferObject;
    const uint32_t m_triangleCount;

    /**
     * @brief TODO
     */
    Mesh(GLuint vertexArrayObject, GLuint vertexBufferObject, GLuint elementBufferObject, uint32_t triangleCount);

    Mesh(const Mesh&) = delete;

    /**
     * @brief TODO
     */
    Mesh(Mesh&& other) noexcept;

    /**
     * @brief TODO
     */
    ~Mesh();

    /**
     * @brief TODO
     */
    void draw() const;

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
    void draw(double time, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const;

    friend class Viewport;
};

}  // namespace labeeri::engine
