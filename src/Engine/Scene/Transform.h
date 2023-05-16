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
    ~Transform() {
        while (!m_children.empty())
            m_children.front()->setParent(m_parent);

        m_children.clear();
        removeParent();
    }

    /**
     * @brief TODO
     */
    void setPosition(const glm::vec3& position) {
        m_position = position;
        m_modelMatrixValid = false;
    }

    /**
     * @brief TODO
     */
    void move(const glm::vec3& offset) {
        setPosition(position() + glm::vec3(modelMatrix() * glm::vec4(offset, 0.0f)));
    }

    /**
     * @brief TODO
     */
    void setWorldPosition(const glm::vec3& position) {
        if (!m_parent) {
            setPosition(position);
            return;
        }

        glm::mat4 parentInverseModelMatrix = glm::inverse(m_parent->modelMatrix());
        glm::vec3 localPosition = glm::vec3(parentInverseModelMatrix * glm::vec4(position, 1.0f));
        setPosition(localPosition);
    }

    /**
     * @brief TODO
     */
    void moveWorld(const glm::vec3& offset) {
        setPosition(position() + offset);
    }

    /**
     * @brief TODO
     */
    void setRotation(const glm::quat& rotation) {
        m_rotation = rotation;
        m_modelMatrixValid = false;
    }

    /**
     * @brief TODO
     */
    void rotate(const glm::quat& offset) {
        setRotation(m_rotation * offset);
    }

    /**
     * @brief TODO
     */
    void setScale(const glm::vec3& scale) {
        m_scale = scale;
        m_modelMatrixValid = false;
    }

    /**
     * @brief TODO
     */
    void scale(const glm::vec3& amount) {
        setScale(m_scale * amount);
    }

    /**
     * @brief TODO
     */
    void setParent(Transform* parent) {
        if (!m_parent && !parent)
            return;

        removeParent();

        m_parent = parent;
        m_modelMatrixValid = false;

        if (!m_parent)
            return;

        m_parent->m_children.push_back(this);

        setWorldPosition(position());
    }

    void setParent(const Ref<Transform>& parent) {
        setParent(parent.get());
    }

    /**
     * @brief TODO
     */
    const Transform& parent() const {
        return *m_parent;
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
    const Ref<Entity>&& entity() const {
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
    glm::vec3 worldPosition() const {
        return glm::vec3(modelMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    }

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
    const glm::mat4& modelMatrix() const {
        if (!modelMatrixValid())
            updateModelMatrix();

        return m_modelMatrix;
    }

    /**
     * @brief TODO
     */

    glm::vec3 forward() const {
        return glm::normalize(glm::vec3(modelMatrix() * glm::vec4(LAB_FORWARD, 0.0f)));
    }

    /**
     * @brief TODO
     */
    glm::vec3 up() const {
        return glm::normalize(glm::vec3(modelMatrix() * glm::vec4(LAB_UP, 0.0f)));
    }

    /**
     * @brief TODO
     */
    glm::vec3 right() const {
        return glm::normalize(glm::vec3(modelMatrix() * glm::vec4(LAB_RIGHT, 0.0f)));
    }

    /**
     * @brief TODO
     */
    Transform& operator=(const Transform& other) {
        if (this == &other)
            return *this;

        setWorldPosition(other.worldPosition());
        setRotation(other.rotation());
        return *this;
    }

private:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::quat m_rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
    glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

    mutable glm::mat4 m_modelMatrix = glm::mat4(1.0);
    mutable bool m_modelMatrixValid = true;

    Transform* m_parent = nullptr;
    std::list<Transform*> m_children;

    std::weak_ptr<Entity> m_entity;

    /**
     * @brief TODO
     */
    bool modelMatrixValid() const {
        if (!m_parent)
            return m_modelMatrixValid;

        return m_parent->modelMatrixValid() && m_modelMatrixValid;
    }

    /**
     * @brief TODO
     */
    void updateModelMatrix() const {
        glm::mat4 localModelMatrix = glm::mat4(1.0f);
        localModelMatrix = glm::translate(localModelMatrix, m_position);
        localModelMatrix *= glm::mat4_cast(m_rotation);
        localModelMatrix = glm::scale(localModelMatrix, m_scale);

        m_modelMatrix = localModelMatrix;

        if (m_parent)
            m_modelMatrix = m_parent->modelMatrix() * m_modelMatrix;

        m_modelMatrixValid = true;

        for (auto& child : m_children)
            child->m_modelMatrixValid = false;
    }

    /**
     * @brief TODO
     */
    void removeParent() {
        if (!m_parent)
            return;

        setPosition(worldPosition());

        m_parent->m_children.remove(this);
        m_parent = nullptr;
        m_modelMatrixValid = false;
    }

    friend Entity;
};

}  // namespace labeeri::Engine
