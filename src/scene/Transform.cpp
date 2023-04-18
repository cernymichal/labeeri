#include "Transform.h"

Transform::Transform() {
}

Transform::~Transform() {
    destroy();
}

void Transform::setPosition(const glm::vec3& position) {
    m_position = position;
    m_modelMatrixValid = false;
}

void Transform::setRotation(const glm::quat& rotation) {
    m_rotation = rotation;
    m_modelMatrixValid = false;
}

void Transform::setScale(const glm::vec3& scale) {
    m_scale = scale;
    m_modelMatrixValid = false;
}

void Transform::setParent(const std::shared_ptr<Transform>& parent) {
    if (!m_parent && !parent)
        return;

    removeParent();

    m_parent = parent;
    m_modelMatrixValid = false;

    if (!m_parent)
        return;

    m_parent->m_children.push_back(this);

    glm::mat4 parentInverseModelMatrix = glm::inverse(m_parent->modelMatrix());
    glm::vec3 localPosition = glm::vec3(parentInverseModelMatrix * glm::vec4(m_position, 1.0f));
    setPosition(localPosition);
}

glm::vec3 Transform::position() const {
    return m_position;
}

glm::vec3 Transform::worldPosition() {
    return glm::vec3(modelMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

glm::quat Transform::rotation() const {
    return m_rotation;
}

glm::vec3 Transform::scale() const {
    return m_scale;
}

const glm::mat4& Transform::modelMatrix() {
    if (!modelMatrixValid())
        updateModelMatrix();

    return m_modelMatrix;
}

bool Transform::modelMatrixValid() const {
    if (!m_parent)
        return m_modelMatrixValid;

    return m_parent->modelMatrixValid() && m_modelMatrixValid;
}

void Transform::updateModelMatrix() {
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

void Transform::removeParent() {
    if (!m_parent)
        return;

    setPosition(worldPosition());

    m_parent->m_children.remove(this);
    m_parent = nullptr;
    m_modelMatrixValid = false;
}

void Transform::destroy() {
    for (auto& child : m_children)
        child->setParent(m_parent);

    m_children.clear();
	removeParent();
}
