#pragma once

#include "Engine/Scene/ECS/Entity.h"

namespace labeeri::Engine {

/**
 * @brief Tranform component. (Position, rotation, scale)
 */
class Transform {
public:
    /**
     * @param entity The entity this transform belongs to. (for hierarchy)
     */
    explicit Transform(Entity entity = NULL_ENTITY) : m_entity(entity) {
    }

    /**
     * @param other The transform to move.
     */
    Transform(Transform&& other) noexcept
        : m_position(other.m_position), m_rotation(other.m_rotation), m_scale(other.m_scale), m_modelMatrix(other.m_modelMatrix), m_cacheValid(other.m_cacheValid), m_entity(other.m_entity), m_parent(other.m_parent), m_children(other.m_children), m_moved(other.m_moved) {
        other.m_moved = true;
    }

    /**
     * @brief Destroy the transform and remove it from the hierarchy.
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
     * @brief Set the position and rotation from another transform.
     *
     * @param other The transform to copy.
     * @return This transform.
     */
    Transform& operator=(const Transform& other) {
        if (this == &other)
            return *this;

        setWorldPosition(other.worldPosition());
        setRotation(other.rotation());
        return *this;
    }

    /**
     * @param other The transform to move.
     */
    Transform& operator=(Transform&& other) noexcept {
        if (this == &other)
            return *this;

        this->~Transform();
        new (this) Transform(std::move(other));
        return *this;
    }

    /**
     * @brief Set a new model space position.
     *
     * @param position The new position.
     */
    void setPosition(const vec3& position) {
        m_position = position;
        m_cacheValid = false;
    }

    /**
     * @brief Move in model space.
     *
     * @param offset The offset to move.
     */
    void move(const vec3& offset) {
        setPosition(position() + offset);
    }

    /**
     * @brief Set a new world space position.
     *
     * @param position The new position.
     */
    void setWorldPosition(const vec3& position) {
        if (!m_parent) {
            setPosition(position);
            return;
        }

        mat4 parentInverseModelMatrix = m_parent.getComponent<Transform>()->modelMatrixInverse();
        vec3 localPosition = vec3(parentInverseModelMatrix * vec4(position, 1.0f));
        setPosition(localPosition);
    }

    /**
     * @brief Move in world space.
     *
     * @param offset The offset to move.
     */
    void moveWorld(const vec3& offset) {
        setWorldPosition(worldPosition() + offset);
    }

    /**
     * @brief Set a new rotation.
     *
     * @param rotation The new rotation.
     */
    void setRotation(const quat& rotation) {
        m_rotation = rotation;
        m_cacheValid = false;
    }

    /**
     * @brief Rotate in model space.
     *
     * @param offset The offset to rotate.
     */
    void rotate(const quat& offset) {
        setRotation(offset * m_rotation);
    }

    /**
     * @brief Set a model space scale.
     *
     * @param scale The new scale.
     */
    void setScale(const vec3& scale) {
        m_scale = scale;
        m_cacheValid = false;
    }

    /**
     * @brief Scale in model space.
     *
     * @param amount The amount to scale.
     */
    void scale(const vec3& amount) {
        setScale(m_scale * amount);
    }

    /**
     * @brief Set a new parent.
     *
     * @param parent The new parent.
     */
    void setParent(Entity parent) {
        if (!m_parent && !parent)
            return;

        removeParent();

        m_parent = parent;
        m_cacheValid = false;

        if (!m_parent || !m_entity)
            return;

        m_parent.getComponent<Transform>()->m_children.push_back(m_entity);

        setWorldPosition(position());
    }

    /**
     * @return The transform's parent.
     */
    Entity parent() const {
        return m_parent;
    }

    /**
     * @return The transform's children.
     */
    const std::list<Entity>& children() const {
        return m_children;
    }

    /**
     * @return Model space position.
     */
    vec3 position() const {
        return m_position;
    }

    /**
     * @return World space position.
     */
    vec3 worldPosition() const {
        if (!cacheValid())
            recalculateCache();

        return m_worldPosition;
    }

    /**
     * @return Model space rotation.
     */
    quat rotation() const {
        return m_rotation;
    }

    /**
     * @return Model space scale.
     */
    vec3 scale() const {
        return m_scale;
    }

    /**
     * @return Calculated model matrix.
     */
    const mat4& modelMatrix() const {
        if (!cacheValid())
            recalculateCache();

        return m_modelMatrix;
    }

    /**
     * @return Calculated model matrix.
     */
    const mat4& modelMatrixInverse() const {
        if (!cacheValid())
            recalculateCache();

        return m_modelMatrixInverse;
    }

    /**
     * @return Forward vector in world space.
     */
    vec3 forward() const {
        return glm::normalize(vec3(modelMatrix() * vec4(LAB_FORWARD, 0.0f)));
    }

    /**
     * @return Up vector in world space.
     */
    vec3 up() const {
        return glm::normalize(vec3(modelMatrix() * vec4(LAB_UP, 0.0f)));
    }

    /**
     * @return Right vector in world space.
     */
    vec3 right() const {
        return glm::normalize(vec3(modelMatrix() * vec4(LAB_RIGHT, 0.0f)));
    }

private:
    vec3 m_position = vec3(0.0f, 0.0f, 0.0f);
    quat m_rotation = quat(vec3(0.0f, 0.0f, 0.0f));
    vec3 m_scale = vec3(1.0f, 1.0f, 1.0f);

    mutable vec3 m_worldPosition = vec3(0.0f, 0.0f, 0.0f);
    mutable mat4 m_modelMatrix = mat4(1.0);
    mutable mat4 m_modelMatrixInverse = mat4(1.0);
    mutable bool m_cacheValid = true;

    Entity m_entity;
    Entity m_parent = NULL_ENTITY;
    std::list<Entity> m_children;

    bool m_moved = false;

    /**
     * @brief Check whether the cached values are still valid.
     */
    bool cacheValid() const {
        if (!m_parent)
            return m_cacheValid;

        auto parentTransform = m_parent.getComponent<Transform>();
        if (!parentTransform)
            return m_cacheValid;

        return parentTransform->cacheValid() && m_cacheValid;
    }

    /**
     * @brief Recalculate the cached values. (model matrix, world position, ...)
     */
    void recalculateCache() const {
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

        m_modelMatrixInverse = glm::inverse(m_modelMatrix);
        m_worldPosition = vec3(m_modelMatrix * vec4(0.0f, 0.0f, 0.0f, 1.0f));
        m_cacheValid = true;

        for (auto& child : m_children) {
            auto childTransform = child.getComponent<Transform>();
            if (childTransform)
                childTransform->m_cacheValid = false;
        }
    }

    /**
     * @brief Remove the current parent.
     */
    void removeParent() {
        if (!m_parent || !m_entity)
            return;

        setPosition(worldPosition());

        auto parentTransform = m_parent.getComponent<Transform>();
        if (parentTransform)
            parentTransform->m_children.remove(m_entity);

        m_parent = NULL_ENTITY;
        m_cacheValid = false;
    }
};

}  // namespace labeeri::Engine
