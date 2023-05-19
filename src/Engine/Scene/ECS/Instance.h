#pragma once

#include "Engine/Scene/ECS/ComponentManager.h"
#include "Engine/Scene/ECS/EntityManager.h"
#include "Engine/Scene/ECS/SystemManager.h"

namespace labeeri::Engine::ECS {

/**
 * @brief TODO
 */
class Instance {
public:
    std::unique_ptr<ECS::EntityManager> m_entityManager;
    std::unique_ptr<ECS::ComponentManager> m_componentManager;
    std::unique_ptr<ECS::SystemManager> m_systemManager;

    /**
     * @brief TODO
     */
    Instance() {
        m_entityManager = std::make_unique<ECS::EntityManager>();
        m_componentManager = std::make_unique<ECS::ComponentManager>();
        m_systemManager = std::make_unique<ECS::SystemManager>();
    }

    /**
     * @brief TODO
     */
    template <typename T>
    void registerComponent() {
        m_componentManager->registerComponent<T>();
    }

    /**
     * @brief TODO
     */
    template <typename T>
    ComponentType getComponentType() {
        return m_componentManager->getComponentType<T>();
    }

    /**
     * @brief TODO
     */
    template <typename T>
    std::shared_ptr<T> registerSystem() {
        auto system = m_systemManager->registerSystem<T>();
        setSystemSignature<T>(system->signature(*this));
        return system;
    }

    /**
     * @brief TODO
     */
    template <typename T>
    void setSystemSignature(ComponentSignature signature) {
        m_systemManager->setSignature<T>(signature);
    }
};

inline auto CURRENT_INSTANCE = std::make_shared<Instance>();

}  // namespace labeeri::Engine::ECS
