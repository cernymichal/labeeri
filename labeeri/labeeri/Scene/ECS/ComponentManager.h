#pragma once

#include "Scene/ECS/ComponentArray.h"

namespace labeeri::ECS {

/**
 * @brief Manages all the components types and their arrays.
 */
class ComponentManager {
public:
    /**
     * @brief Add a new component type to the manager.
     *
     * @tparam T The type of the component.
     */
    template <typename T>
    void registerComponent() {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Registering component type more than once.");

        m_componentTypes[typeName] = m_nextComponentType;
        m_componentArrays[typeName] = std::make_shared<ComponentArray<T>>();
        m_nextComponentType++;
    }

    /**
     * @brief Get the id of a component type.
     *
     * @tparam T The type of the component.
     * @return ComponentType The id of the component type.
     */
    template <typename T>
    ComponentType getComponentType() const {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

        return m_componentTypes.at(typeName);
    }

    /**
     * @brief Add a component to an entity.
     *
     * @tparam T The type of the component.
     * @param entity The entity to add the component to.
     * @param component The component to add. (is moved inside)
     * @return T* A pointer to the component.
     */
    template <typename T>
    T* addComponent(EntityId entity, T&& component) {
        return getComponentArray<T>()->insert(entity, std::forward<T>(component));
    }

    /**
     * @brief Remove a component from an entity.
     *
     * @tparam T The type of the component.
     * @param entity The entity to remove the component from.
     */
    template <typename T>
    void removeComponent(EntityId entity) {
        getComponentArray<T>()->remove(entity);
    }

    /**
     * @brief Get a component from an entity.
     *
     * Return nullptr if the entity doesn't have the component.
     *
     * @tparam T The type of the component.
     * @param entity The entity to get the component from.
     * @return T* A pointer to the component.
     */
    template <typename T>
    T* getComponent(EntityId entity) const {
        return (*getComponentArray<T>())[entity];
    }

    /**
     * @brief Called when an entity is destroyed. Removes the entity from all component arrays.
     *
     * @param entity The entity that was destroyed.
     */
    void entityDestroyed(EntityId entity) {
        for (const auto& array : m_componentArrays | std::views::values)
            array->entityDestroyed(entity);
    }

private:
    std::unordered_map<const char*, ComponentType> m_componentTypes;
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;
    ComponentType m_nextComponentType = 0;

    template <typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray() const {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays.at(typeName));
    }
};

}  // namespace labeeri::ECS
