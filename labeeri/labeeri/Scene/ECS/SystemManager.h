#pragma once

#include "Scene/ECS/ISystem.h"

namespace labeeri::ECS {

/**
 * @brief ECS systems manager.
 */
class SystemManager {
public:
    /**
     * @brief Add a system to the manager.
     *
     * @tparam T The type of the system.
     * @tparam Args The types of the arguments to pass to the system constructor.
     * @param args The arguments to pass to the system constructor.
     * @return The added system.
     */
    template <typename T, typename... Args>
    std::shared_ptr<T> registerSystem(Args... args) {
        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once.");

        m_systems[typeName] = std::make_shared<T>(std::forward<Args>(args)...);

        return std::static_pointer_cast<T>(m_systems[typeName]);
    }

    /**
     * @brief Set a component signature for a system.
     *
     * @tparam T The type of the system.
     * @param signature The signature to set.
     */
    template <typename T>
    void setSignature(ComponentSignature signature) {
        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");

        m_signatures[typeName] = signature;
    }

    /**
     * @brief Called when an entity is destroyed. Erases it from all systems.
     *
     * @param entity The destroyed entity.
     */
    void entityDestroyed(EntityId entity) {
        for (const auto& system : m_systems | std::views::values)
            system->m_entities.erase(entity);
    }

    /**
     * @brief Called when an entity's signature changes. Updates all systems.
     *
     * @param entity The entity whose signature changed.
     * @param entitySignature The new signature of the entity.
     */
    void entitySignatureChanged(EntityId entity, ComponentSignature entitySignature) {
        for (const auto& element : m_systems) {
            const auto& type = element.first;
            const auto& system = element.second;
            const auto& signature = m_signatures[type];

            if ((entitySignature & signature) == signature)
                system->m_entities.insert(entity);
            else
                system->m_entities.erase(entity);
        }
    }

private:
    std::unordered_map<const char*, ComponentSignature> m_signatures;
    std::unordered_map<const char*, std::shared_ptr<ISystem>> m_systems;
};

}  // namespace labeeri::ECS