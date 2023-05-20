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
    virtual ComponentSignature signature(const Instance& ecs) const = 0;

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