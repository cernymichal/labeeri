#pragma once

#include "Engine/Scene/ECS/Common.h"

namespace labeeri::Engine::ECS {

/**
 * @brief TODO
 */
class IComponentArray {
public:
    virtual ~IComponentArray() = default;

    /**
     * @brief TODO
     */
    virtual void entityDestroyed(EntityId entity) = 0;
};

/**
 * @brief TODO
 */
template <typename T>
class ComponentArray : public IComponentArray {
public:
    /**
     * @brief TODO
     */
    T& insert(EntityId entity, T&& component) {
        assert(m_entityToIndex.find(entity) == m_entityToIndex.end() && "Component added to same entity more than once.");

        size_t insertIndex = m_size++;
        m_components[insertIndex] = std::move(component);
        m_entityToIndex[entity] = insertIndex;
        m_indexToEntity[insertIndex] = entity;

        return m_components[insertIndex];
    }

    /**
     * @brief TODO
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
            new (&m_components[replaced]) T();

        m_entityToIndex.erase(entity);
        m_indexToEntity.erase(last);

        m_size--;
    }

    /**
     * @brief TODO
     */
    T& operator[](EntityId entity) {
        assert(m_entityToIndex.find(entity) != m_entityToIndex.end() && "Retrieving non-existent component.");

        return m_components[m_entityToIndex.at(entity)];
    }

    /**
     * @brief TODO
     */
    void entityDestroyed(EntityId entity) override {
        if (m_entityToIndex.find(entity) != m_entityToIndex.end())
            remove(entity);
    }

private:
    std::array<T, MAX_ENTITIES> m_components;
    size_t m_size;
    std::unordered_map<EntityId, size_t> m_entityToIndex;
    std::unordered_map<size_t, EntityId> m_indexToEntity;
};

}  // namespace labeeri::Engine::ECS
