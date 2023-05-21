#pragma once

#include "Engine/Scene/ECS/Entity.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Transform {
public:
    /**
     * @brief TODO
     */
    explicit Transform(Entity entity = NULL_ENTITY) : m_entity(entity) {
    }

    /**
     * @brief TODO
     */
    Transform(Transform&& other) noexcept
        : m_position(other.m_position), m_rotation(other.m_rotation), m_scale(other.m_scale), m_modelMatrix(other.m_modelMatrix), m_modelMatrixValid(other.m_modelMatrixValid), m_entity(other.m_entity), m_parent(other.m_parent), m_children(other.m_children), m_moved(other.m_moved) {
        other.m_moved = true;
    }

    /**
     * @brief TODO
     */
    ~Transform() {
        if (m_moved)
            return;

        while (!m_children.empty()) {
            auto childTransform = m_children.front().getComponent<Transform>();
            if (childTransform)
                childTransform->setParent(m_parent);
            else
                m_children.pop_front();
        }

        m_children.clear();
        removeParent();
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

    /**
     * @brief TODO
     */
    Transform& operator=(Transform&& other) noexcept {
        if (this == &other)
            return *this;

        this->~Transform();
        new (this) Transform(std::move(other));
        return *this;
    }

    /**
     * @brief TODO
     */
    void setPosition(const vec3& position) {
        m_position = position;
        m_modelMatrixValid = false;
    }

    /**
     * @brief TODO
     */
    void move(const vec3& offset) {
        setPosition(position() + vec3(modelMatrix() * vec4(offset, 0.0f)));
    }

    /**
     * @brief TODO
     */
    void setWorldPosition(const vec3& position) {
        if (!m_parent) {
            setPosition(position);
            return;
        }

        mat4 parentInverseModelMatrix = glm::inverse(m_parent.getComponent<Transform>()->modelMatrix());
        vec3 localPosition = vec3(parentInverseModelMatrix * vec4(position, 1.0f));
        setPosition(localPosition);
    }

    /**
     * @brief TODO
     */
    void moveWorld(const vec3& offset) {
        setPosition(position() + offset);
    }

    /**
     * @brief TODO
     */
    void setRotation(const quat& rotation) {
        m_rotation = rotation;
        m_modelMatrixValid = false;
    }

    /**
     * @brief TODO
     */
    void rotate(const quat& offset) {
        setRotation(offset * m_rotation);
    }

    /**
     * @brief TODO
     */
    void setScale(const vec3& scale) {
        m_scale = scale;
        m_modelMatrixValid = false;
    }

    /**
     * @brief TODO
     */
    void scale(const vec3& amount) {
        setScale(m_scale * amount);
    }

    /**
     * @brief TODO
     */
    void setParent(Entity parent) {
        if (!m_parent && !parent)
            return;

        removeParent();

        m_parent = parent;
        m_modelMatrixValid = false;

        if (!m_parent || !m_entity)
            return;

        m_parent.getComponent<Transform>()->m_children.push_back(m_entity);

        setWorldPosition(position());
    }

    /**
     * @brief TODO
     */
    Entity parent() const {
        return m_parent;
    }

    /**
     * @brief TODO
     */
    const std::list<Entity>& children() const {
        return m_children;
    }

    /**
     * @brief TODO
     */
    vec3 position() const {
        return m_position;
    }

    /**
     * @brief TODO
     */
    vec3 worldPosition() const {
        return vec3(modelMatrix() * vec4(0.0f, 0.0f, 0.0f, 1.0f));
    }

    /**
     * @brief TODO
     */
    quat rotation() const {
        return m_rotation;
    }

    /**
     * @brief TODO
     */
    vec3 scale() const {
        return m_scale;
    }

    /**
     * @brief TODO
     */
    const mat4& modelMatrix() const {
        if (!modelMatrixValid())
            updateModelMatrix();

        return m_modelMatrix;
    }

    /**
     * @brief TODO
     */

    vec3 forward() const {
        return glm::normalize(vec3(modelMatrix() * vec4(LAB_FORWARD, 0.0f)));
    }

    /**
     * @brief TODO
     */
    vec3 up() const {
        return glm::normalize(vec3(modelMatrix() * vec4(LAB_UP, 0.0f)));
    }

    /**
     * @brief TODO
     */
    vec3 right() const {
        return glm::normalize(vec3(modelMatrix() * vec4(LAB_RIGHT, 0.0f)));
    }

private:
    vec3 m_position = vec3(0.0f, 0.0f, 0.0f);
    quat m_rotation = quat(vec3(0.0f, 0.0f, 0.0f));
    vec3 m_scale = vec3(1.0f, 1.0f, 1.0f);

    mutable mat4 m_modelMatrix = mat4(1.0);
    mutable bool m_modelMatrixValid = true;

    Entity m_entity;
    Entity m_parent = NULL_ENTITY;
    std::list<Entity> m_children;

    bool m_moved = false;

    /**
     * @brief TODO
     */
    bool modelMatrixValid() const {
        if (!m_parent)
            return m_modelMatrixValid;

        auto parentTransform = m_parent.getComponent<Transform>();
        if (!parentTransform)
            return m_modelMatrixValid;

        return parentTransform->modelMatrixValid() && m_modelMatrixValid;
    }

    /**
     * @brief TODO
     */
    void updateModelMatrix() const {
        mat4 localModelMatrix = mat4(1.0f);
        localModelMatrix = glm::translate(localModelMatrix, m_position);
        localModelMatrix *= glm::mat4_cast(m_rotation);
        localModelMatrix = glm::scale(localModelMatrix, m_scale);

        m_modelMatrix = localModelMatrix;

        if (m_parent) {
            auto parentTransform = m_parent.getComponent<Transform>();
            if (parentTransform)
                m_modelMatrix = parentTransform->modelMatrix() * m_modelMatrix;
        }

        m_modelMatrixValid = true;

        for (auto& child : m_children) {
            auto childTransform = child.getComponent<Transform>();
            if (childTransform)
                childTransform->m_modelMatrixValid = false;
        }
    }

    /**
     * @brief TODO
     */
    void removeParent() {
        if (!m_parent || !m_entity)
            return;

        setPosition(worldPosition());

        auto parentTransform = m_parent.getComponent<Transform>();
        if (parentTransform)
            parentTransform->m_children.remove(m_entity);

        m_parent = NULL_ENTITY;
        m_modelMatrixValid = false;
    }
};

}  // namespace labeeri::Engine
