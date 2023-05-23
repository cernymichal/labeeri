#pragma once

#include "Engine/Scene/ECS/Instance.h"

namespace labeeri::Engine {

/**
 * @brief Represents an entity in the ECS system.
 *
 * Only a wrapper around it's id.
 */
class Entity {
public:
    EntityId m_id;

    /**
     * @brief Construct a new Entity object.
     *
     * Doesn't create an entity in the ECS system!
     *
     * @param id The id of the entity.
     */
    Entity(EntityId id = NULL_ENTITY) : m_id(id) {
    }

    /**
     * @brief Casts the entity to it's id.
     */
    operator EntityId() const {
        return m_id;
    }

    /**
     * @brief Returns true if the entity is valid in the ECS system.
     */
    operator bool() const {
        return m_id != NULL_ENTITY && m_id <= MAX_ENTITIES;
    }

    /**
     * @brief Returns true if the entity is invalid in the ECS system.
     */
    bool operator!() const {
        return !static_cast<bool>(*this);
    }

    /**
     * @brief Compares two entity ids.
     */
    bool operator==(const Entity& other) const {
        return m_id == other.m_id;
    }

    /**
     * @brief Creates a new entity in the ECS system.
     *
     * @param ecs The ECS instance to create the entity in.
     * @return The created entity.
     */
    static Entity Create(const Ref<ECS::Instance>& ecs);

    /**
     * @brief Creates a new entity in the current ECS system.
     *
     * @return The created entity.
     */
    static Entity Create() {
        if (ECS::CURRENT_INSTANCE)
            return Create(ECS::CURRENT_INSTANCE);
        else
            return NULL_ENTITY;
    }

    /**
     * @brief Removes the entity from the ECS system.
     *
     * @param ecs The ECS instance to remove the entity from.
     */
    void destroy(const Ref<ECS::Instance>& ecs);

    /**
     * @brief Removes the entity from current ECS system.
     */
    void destroy() {
        if (ECS::CURRENT_INSTANCE)
            destroy(ECS::CURRENT_INSTANCE);
    }

    /**
     * @brief Adds a component to the entity.
     *
     * @tparam T The type of the component.
     * @param component The component to add.
     * @param ecs The ECS instance to add the component to.
     * @return The added component.
     */
    template <typename T>
    T* addComponent(T&& component, const Ref<ECS::Instance>& ecs) const {
        T* placedComponent = ecs->m_componentManager->addComponent<T>(*this, std::forward<T>(component));

        auto signature = ecs->m_entityManager->getSignature(*this);
        signature.set(ecs->m_componentManager->getComponentType<T>(), true);
        ecs->m_entityManager->setSignature(*this, signature);

        ecs->m_systemManager->entitySignatureChanged(*this, signature);

        return placedComponent;
    }

    /**
     * @brief Adds a component to the entity in the current ECS system.
     *
     * @tparam T The type of the component.
     * @param component The component to add.
     * @return The added component.
     */
    template <typename T>
    T* addComponent(T&& component) const {
        if (ECS::CURRENT_INSTANCE)
            return addComponent<T>(std::forward<T>(component), *ECS::CURRENT_INSTANCE);
        else
            return nullptr;
    }

    /**
     * @brief Removes a component from the entity.
     *
     * @tparam T The type of the component.
     * @param ecs The ECS instance to remove the component from.
     */
    template <typename T>
    void removeComponent(const Ref<ECS::Instance>& ecs) const {
        ecs->m_componentManager->removeComponent<T>(*this);

        auto signature = ecs->m_entityManager->getSignature(*this);
        signature.set(ecs->m_componentManager->getComponentType<T>(), false);
        ecs->m_entityManager->setSignature(*this, signature);

        ecs->m_systemManager->entitySignatureChanged(*this, signature);
    }

    /**
     * @brief Removes a component from the entity in the current ECS system.
     *
     * @tparam T The type of the component.
     */
    template <typename T>
    void removeComponent() const {
        if (ECS::CURRENT_INSTANCE)
            return removeComponent<T>(ECS::CURRENT_INSTANCE);
    }

    /**
     * @brief Gets a certain component from the entity.
     * 
     * Returns nullptr if the entity doesn't have the component.
     *
     * @tparam T The type of the component.
     * @param ecs The ECS instance to get the component from.
     * @return The component.
     */
    template <typename T>
    T* getComponent(const Ref<ECS::Instance>& ecs) const {
        return ecs->m_componentManager->getComponent<T>(*this);
    }

    /**
     * @brief Gets a certain component from the entity in the current ECS system.
     *
     * Returns nullptr if the entity doesn't have the component or if there is no current ECS system.
     * 
     * @tparam T The type of the component.
     */
    template <typename T>
    T* getComponent() const {
        if (ECS::CURRENT_INSTANCE)
            return getComponent<T>(ECS::CURRENT_INSTANCE);
        else
            return nullptr;
    }
};

}  // namespace labeeri::Engine
