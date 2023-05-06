#pragma once

namespace labeeri::Engine {

constexpr auto LAB_FORWARD = glm::vec3(0.0f, 0.0f, -1.0f);
constexpr auto LAB_UP = glm::vec3(0.0f, 1.0f, 0.0f);
constexpr auto LAB_RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);

class Entity;

/**
 * @brief TODO
 */
class Transform {
public:
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
    void move(const glm::vec3& offset);

    /**
     * @brief TODO
     */
    void setWorldPosition(const glm::vec3& position);

    /**
     * @brief TODO
     */
    void moveWorld(const glm::vec3& offset);

    /**
     * @brief TODO
     */
    void setRotation(const glm::quat& rotation);

    /**
     * @brief TODO
     */
    void rotate(const glm::quat& offset);

    /**
     * @brief TODO
     */
    void setScale(const glm::vec3& scale);

    /**
     * @brief TODO
     */
    void scale(const glm::vec3& amount);

    /**
     * @brief TODO
     */
    void setParent(const std::shared_ptr<Transform>& parent);

    /**
     * @brief TODO
     */
    const std::shared_ptr<Transform>& parent() const {
        return m_parent;
    }

    /**
     * @brief TODO
     */
    const std::list<Transform*>& children() const {
        return m_children;
    }

    /**
     * @brief TODO
     */
    const std::shared_ptr<Entity>& entity() const {
        return m_entity.lock();
    }

    /**
     * @brief TODO
     */
    glm::vec3 position() const {
        return m_position;
    }

    /**
     * @brief TODO
     */
    glm::vec3 worldPosition() const;

    /**
     * @brief TODO
     */
    glm::quat rotation() const {
        return m_rotation;
    }

    /**
     * @brief TODO
     */
    glm::vec3 scale() const {
        return m_scale;
    }

    /**
     * @brief TODO
     */
    const glm::mat4& modelMatrix() const;

    /**
     * @brief TODO
     */

    glm::vec3 forward() const;

    /**
     * @brief TODO
     */
    glm::vec3 up() const;

    /**
     * @brief TODO
     */
    glm::vec3 right() const;

    /**
     * @brief TODO
     */
    Transform& operator=(const Transform& other);

private:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::quat m_rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
    glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

    mutable glm::mat4 m_modelMatrix = glm::mat4(1.0);
    mutable bool m_modelMatrixValid = true;

    std::shared_ptr<Transform> m_parent;
    std::list<Transform*> m_children;

    std::weak_ptr<Entity> m_entity;

    /**
     * @brief TODO
     */
    bool modelMatrixValid() const;

    /**
     * @brief TODO
     */
    void updateModelMatrix() const;

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

}  // namespace labeeri::Engine
