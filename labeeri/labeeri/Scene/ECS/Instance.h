#pragma once

#include "Scene/ECS/ComponentManager.h"
#include "Scene/ECS/EntityManager.h"
#include "Scene/ECS/SystemManager.h"

namespace labeeri::ECS {

/**
 * @brief An ECS system instance.
 */
class Instance {
public:
    std::unique_ptr<ECS::EntityManager> m_entityManager;
    std::unique_ptr<ECS::ComponentManager> m_componentManager;
    std::unique_ptr<ECS::SystemManager> m_systemManager;

    /**
     * @brief Creates all the ECS managers.
     */
    Instance() {
        m_entityManager = std::make_unique<ECS::EntityManager>();
        m_componentManager = std::make_unique<ECS::ComponentManager>();
        m_systemManager = std::make_unique<ECS::SystemManager>();
    }

    /**
     * @brief Add a new component to the ECS.
     *
     * @tparam T The type of the component.
     */
    template <typename T>
    void registerComponent() {
        m_componentManager->registerComponent<T>();
    }

    /**
     *  @tparam T The type of the component.
     * @return The id of the component.
     */
    template <typename T>
    ComponentType getComponentType() {
        return m_componentManager->getComponentType<T>();
    }

    /**
     * @brief Adds a new system to the ECS.
     *
     * @tparam T The type of the system.
     * @return A pointer to the system.
     */
    template <typename T, typename... Args>
    std::shared_ptr<T> registerSystem(Args... args) {
        auto system = m_systemManager->registerSystem<T>(std::forward<Args>(args)...);
        setSystemSignature<T>(system->signature(*this));
        return system;
    }

    /**
     * @brief Sets the component signature of a system.
     *
     * @tparam T The type of the system.
     * @param signature The component signature.
     */
    template <typename T>
    void setSystemSignature(ComponentSignature signature) {
        m_systemManager->setSignature<T>(signature);
    }
};

inline auto CURRENT_INSTANCE = std::make_shared<Instance>();

}  // namespace labeeri::ECS
