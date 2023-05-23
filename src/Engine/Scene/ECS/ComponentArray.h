#pragma once

#include "Engine/Scene/ECS/Common.h"

namespace labeeri::Engine::ECS {

/**
 * @brief Component array inferface. Exists because of templated component arrays.
 */
class IComponentArray {
public:
    virtual ~IComponentArray() = default;

    virtual void entityDestroyed(EntityId entity) = 0;
};

/**
 * @brief Holds all of the instances of a component type.
 *
 * @tparam T The type of the component.
 */
template <typename T>
class ComponentArray : public IComponentArray {
public:
    /**
     * @brief Insert a new component into the array associated with a particular entity.
     *
     * @param entity The entity to associate the component with.
     * @param component The component to insert. (is moved inside)
     * @return A pointer to inserted the component.
     */
    T* insert(EntityId entity, T&& component) {
        assert(m_entityToIndex.find(entity) == m_entityToIndex.end() && "Component added to same entity more than once.");

        size_t insertIndex = m_size++;
        m_components[insertIndex] = std::move(component);
        m_entityToIndex[entity] = insertIndex;
        m_indexToEntity[insertIndex] = entity;

        return &m_components[insertIndex];
    }

    /**
     * @brief Remove a certain entity and its component from the array.
     *
     * @param entity The entity to remove.
     */
    void remove(EntityId entity) {
        assert(m_entityToIndex.find(entity) != m_entityToIndex.end() && "Removing non-existent component.");

        size_t replaced = m_entityToIndex[entity];
        size_t last = m_size - 1;

        if (last != replaced) {
            m_components[replaced] = std::move(m_components[last]);
            EntityId lastEntity = m_indexToEntity[last];
            m_entityToIndex[lastEntity] = replaced;
            m_indexToEntity[replaced] = lastEntity;
        }
        else
            m_components[replaced] = std::move(T());

        m_entityToIndex.erase(entity);
        m_indexToEntity.erase(last);

        m_size--;
    }

    /**
     * @brief Get a component associated with an entity.
     *
     * Return nullptr if the entity doesn't have the component.
     *
     * @param entity The entity to get the component of.
     * @return A pointer to the component.
     */
    T* operator[](EntityId entity) {
        if (!m_entityToIndex.contains(entity))
            return nullptr;

        return &m_components[m_entityToIndex.at(entity)];
    }

    /**
     * @brief Called when an entity is destroyed. Used to remove the entity's components.
     *
     * @param entity The entity that was destroyed.
     */
    virtual void entityDestroyed(EntityId entity) override {
        if (m_entityToIndex.contains(entity))
            remove(entity);
    }

private:
    std::array<T, MAX_ENTITIES> m_components;
    size_t m_size = 0;
    std::unordered_map<EntityId, size_t> m_entityToIndex;
    std::unordered_map<size_t, EntityId> m_indexToEntity;
};

}  // namespace labeeri::Engine::ECS
