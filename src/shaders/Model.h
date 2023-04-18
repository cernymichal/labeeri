#pragma once

#include <cstdint>

#include "Material.h"

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

    /**
     * @brief TODO
     */
    ~Mesh();

    /**
     * @brief TODO
     */
    void draw() const;
};

class Model {
    std::shared_ptr<Material> m_material;
    std::shared_ptr<Mesh> m_mesh;

    /**
     * @brief TODO
     */
    Model(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh);

    /**
     * @brief TODO
     */
    void draw(double time, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const;

    friend class Viewport;
};
