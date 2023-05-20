#pragma once

#include "Engine/Scene/ECS/Instance.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Entity {
public:
    EntityId m_id;

    /**
     * @brief TODO
     */
    Entity(EntityId id = NULL_ENTITY) : m_id(id) {
    }

    /**
     * @brief TODO
     */
    operator EntityId() const {
        return m_id;
    }

    /**
     * @brief TODO
     */
    operator bool() const {
        return m_id != NULL_ENTITY && m_id <= MAX_ENTITIES;
    }

    /**
     * @brief TODO
     */
    bool operator!() const {
        return !static_cast<bool>(*this);
    }

    /**
     * @brief TODO
     */
    bool operator==(const Entity& other) const {
        return m_id == other.m_id;
    }

    /**
     * @brief TODO
     */
    static Entity Create(const ECS::Instance& ecs);

    /**
     * @brief TODO
     */
    static Entity Create() {
        return Create(*ECS::CURRENT_INSTANCE);
    }

    /**
     * @brief TODO
     */
    void destroy(const ECS::Instance& ecs) {
        ecs.m_entityManager->destroyEntity(*this);
        ecs.m_componentManager->entityDestroyed(*this);
        ecs.m_systemManager->entityDestroyed(*this);
        m_id = NULL_ENTITY;
    }

    /**
     * @brief TODO
     */
    void destroy() {
        destroy(*ECS::CURRENT_INSTANCE);
    }

    /**
     * @brief TODO
     */
    template <typename T>
    T* addComponent(T&& component, const ECS::Instance& ecs) const {
        T* placedComponent = ecs.m_componentManager->addComponent<T>(*this, std::forward<T>(component));

        auto signature = ecs.m_entityManager->getSignature(*this);
        signature.set(ecs.m_componentManager->getComponentType<T>(), true);
        ecs.m_entityManager->setSignature(*this, signature);

        ecs.m_systemManager->entitySignatureChanged(*this, signature);

        return placedComponent;
    }

    /**
     * @brief TODO
     */
    template <typename T>
    T* addComponent(T&& component) const {
        return addComponent<T>(std::forward<T>(component), *ECS::CURRENT_INSTANCE);
    }

    /**
     * @brief TODO
     */
    template <typename T>
    void removeComponent(const ECS::Instance& ecs) const {
        ecs.m_componentManager->removeComponent<T>(*this);

        auto signature = ecs.m_entityManager->getSignature(*this);
        signature.set(ecs.m_componentManager->getComponentType<T>(), false);
        ecs.m_entityManager->setSignature(*this, signature);

        ecs.m_systemManager->entitySignatureChanged(*this, signature);
    }

    /**
     * @brief TODO
     */
    template <typename T>
    void removeComponent() const {
        removeComponent<T>(*ECS::CURRENT_INSTANCE);
    }

    /**
     * @brief TODO
     */
    template <typename T>
    T* getComponent(const ECS::Instance& ecs) const {
        return ecs.m_componentManager->getComponent<T>(*this);
    }

    /**
     * @brief TODO
     */
    template <typename T>
    T* getComponent() const {
        return getComponent<T>(*ECS::CURRENT_INSTANCE);
    }
};

}  // namespace labeeri::Engine
