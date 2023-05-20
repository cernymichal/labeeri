#pragma once

#include "Engine/Scene/ECS/ISystem.h"

namespace labeeri::Engine::ECS {

/**
 * @brief TODO
 */
class SystemManager {
public:
    /**
     * @brief TODO
     */
    template <typename T>
    std::shared_ptr<T> registerSystem() {
        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once.");

        m_systems[typeName] = std::make_shared<T>();

        return std::static_pointer_cast<T>(m_systems[typeName]);
    }

    /**
     * @brief TODO
     */
    template <typename T>
    void setSignature(ComponentSignature signature) {
        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");

        m_signatures[typeName] = signature;
    }

    /**
     * @brief TODO
     */
    void entityDestroyed(EntityId entity) {
        for (const auto& system : m_systems | std::views::values)
            system->m_entities.erase(entity);
    }

    /**
     * @brief TODO
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

}  // namespace labeeri::Engine::ECS