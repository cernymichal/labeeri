#pragma once

#include "Scene/ECS/Common.h"

namespace labeeri::ECS {

class SystemManager;
class Instance;

/**
 * @brief The ECS system interface.
 */
class ISystem {
public:
    virtual ~ISystem() = default;

    /**
     * @param ecs The ECS instance the system belongs into.
     * @return The component signature of the system.
     */
    virtual ComponentSignature signature(const ECS::Instance& ecs) const = 0;

    /**
     * @param ecs The ECS instance the system belongs into.
     * @return The component signature of the system.
     */
    ComponentSignature signature(const Ref<ECS::Instance>& ecs) const {
        return signature(*ecs);
    };

    /**
     * @return The entities in the system.
     */
    const std::set<EntityId>& entities() const {
        return m_entities;
    }

private:
    std::set<EntityId> m_entities;

    friend class SystemManager;
};

}  // namespace labeeri::ECS