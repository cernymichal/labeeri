#pragma once

#include "Engine/Scene/ECS/ComponentArray.h"

namespace labeeri::Engine::ECS {

/**
 * @brief TODO
 */
class ComponentManager {
public:
    /**
     * @brief TODO
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
     * @brief TODO
     */
    template <typename T>
    ComponentType getComponentType() const {
        const char* typeName = typeid(T).name();

        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");

        return m_componentTypes.at(typeName);
    }

    /**
     * @brief TODO
     */
    template <typename T>
    T* addComponent(EntityId entity, T&& component) {
        return getComponentArray<T>()->insert(entity, std::forward<T>(component));
    }

    /**
     * @brief TODO
     */
    template <typename T>
    void removeComponent(EntityId entity) {
        getComponentArray<T>()->remove(entity);
    }

    /**
     * @brief TODO
     */
    template <typename T>
    T* getComponent(EntityId entity) const {
        return (*getComponentArray<T>())[entity];
    }

    /**
     * @brief TODO
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

}  // namespace labeeri::Engine::ECS
