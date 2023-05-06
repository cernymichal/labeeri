#include "Transform.h"

namespace labeeri::Engine {

Transform::~Transform() {
    destroy();
}

void Transform::setPosition(const glm::vec3& position) {
    m_position = position;
    m_modelMatrixValid = false;
}

void Transform::move(const glm::vec3& offset) {
    setPosition(position() + glm::vec3(modelMatrix() * glm::vec4(offset, 0.0f)));
}

void Transform::setWorldPosition(const glm::vec3& position) {
    if (!m_parent) {
        setPosition(position);
        return;
    }

    glm::mat4 parentInverseModelMatrix = glm::inverse(m_parent->modelMatrix());
    glm::vec3 localPosition = glm::vec3(parentInverseModelMatrix * glm::vec4(position, 1.0f));
    setPosition(localPosition);
}

void Transform::moveWorld(const glm::vec3& offset) {
    setPosition(position() + offset);
}

void Transform::setRotation(const glm::quat& rotation) {
    m_rotation = rotation;
    m_modelMatrixValid = false;
}

void Transform::rotate(const glm::quat& offset) {
    setRotation(m_rotation * offset);
}

void Transform::setScale(const glm::vec3& scale) {
    m_scale = scale;
    m_modelMatrixValid = false;
}

void Transform::scale(const glm::vec3& amount) {
    setScale(m_scale * amount);
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

    setWorldPosition(position());
}

glm::vec3 Transform::worldPosition() const {
    return glm::vec3(modelMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

const glm::mat4& Transform::modelMatrix() const {
    if (!modelMatrixValid())
        updateModelMatrix();

    return m_modelMatrix;
}

glm::vec3 Transform::forward() const {
    return glm::normalize(glm::vec3(modelMatrix() * glm::vec4(LAB_FORWARD, 0.0f)));
}

glm::vec3 Transform::up() const {
    return glm::normalize(glm::vec3(modelMatrix() * glm::vec4(LAB_UP, 0.0f)));
}

glm::vec3 Transform::right() const {
    return glm::normalize(glm::vec3(modelMatrix() * glm::vec4(LAB_RIGHT, 0.0f)));
}

Transform& Transform::operator=(const Transform& other) {
    setWorldPosition(other.worldPosition());
    setRotation(other.rotation());
    return *this;
}

bool Transform::modelMatrixValid() const {
    if (!m_parent)
        return m_modelMatrixValid;

    return m_parent->modelMatrixValid() && m_modelMatrixValid;
}

void Transform::updateModelMatrix() const {
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

}  // namespace labeeri::Engine
