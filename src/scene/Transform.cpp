#include "Transform.h"

Transform::Transform() {
    updateModelMatrix();
}

void Transform::setPosition(const glm::vec3& position) {
    m_position = position;
    updateModelMatrix();
}

void Transform::setRotation(const glm::quat& rotation) {
    m_rotation = rotation;
    updateModelMatrix();
}

void Transform::setScale(const glm::vec3& scale) {
    m_scale = scale;
    updateModelMatrix();
}

void Transform::setParent(const std::shared_ptr<Transform>& parent) {
    m_parent = parent;
    updateModelMatrix();
}

glm::vec3 Transform::position() const {
    return m_position;
}

glm::quat Transform::rotation() const {
    return m_rotation;
}

glm::vec3 Transform::scale() const {
    return m_scale;
}

const glm::mat4& Transform::modelMatrix() const {
    return m_globalModelMatrix;
}

void Transform::updateModelMatrix() {
    m_localModelMatrix = glm::mat4(1.0f);
    m_localModelMatrix = glm::translate(m_localModelMatrix, m_position);
    m_localModelMatrix *= glm::mat4_cast(m_rotation);
    m_localModelMatrix = glm::scale(m_localModelMatrix, m_scale);

    m_globalModelMatrix = m_localModelMatrix;

    if (m_parent) {
        if (m_parent->m_destroyed)
            m_parent = nullptr;
        else
            m_globalModelMatrix = m_parent->modelMatrix() * m_localModelMatrix;
    }
}
