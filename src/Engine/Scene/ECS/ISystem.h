#pragma once

#include "Engine/Scene/ECS/Common.h"

namespace labeeri::Engine::ECS {

class SystemManager;
class Instance;

/**
 * @brief TODO
 */
class ISystem {
public:
    virtual ~ISystem() = default;

    /**
     * @brief TODO
     */
    virtual ComponentSignature signature(const ECS::Instance& ecs) const = 0;

    /**
     * @brief TODO
     */
    ComponentSignature signature(const Ref<ECS::Instance>& ecs) const {
        return signature(*ecs);
    };

    /**
     * @brief TODO
     */
    const std::set<EntityId>& entities() const {
        return m_entities;
    }

private:
    std::set<EntityId> m_entities;

    friend class SystemManager;
};

}  // namespace labeeri::Engine::ECS