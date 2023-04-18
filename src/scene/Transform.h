#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <list>
#include <memory>

class Entity;

/**
 * @brief TODO
 */
class Transform {
public:
    /**
     * @brief TODO
     */
    Transform();

    /**
     * @brief TODO
     */
    ~Transform();

    /**
     * @brief TODO
     */
    void setPosition(const glm::vec3& position);

    /**
     * @brief TODO
     */
    void setRotation(const glm::quat& rotation);

    /**
     * @brief TODO
     */
    void setScale(const glm::vec3& scale);

    /**
     * @brief TODO
     */
    void setParent(const std::shared_ptr<Transform>& parent);

    /**
     * @brief TODO
     */
    glm::vec3 position() const;

    /**
     * @brief TODO
     */
    glm::vec3 worldPosition();

    /**
     * @brief TODO
     */
    glm::quat rotation() const;

    /**
     * @brief TODO
     */
    glm::vec3 scale() const;

    /**
     * @brief TODO
     */
    const glm::mat4& modelMatrix();

private:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::quat m_rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
    glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::mat4 m_modelMatrix = glm::mat4(1.0);
    bool m_modelMatrixValid = true;

    std::shared_ptr<Transform> m_parent;
    std::list<Transform*> m_children;

    /**
     * @brief TODO
     */
    bool modelMatrixValid() const;

    /**
     * @brief TODO
     */
    void updateModelMatrix();

    /**
     * @brief TODO
     */
    void removeParent();

    /**
     * @brief TODO
     */
    void destroy();

    friend Entity;
};
