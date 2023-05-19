#pragma once

#include "Engine/Scene/ECS/Common.h"

namespace labeeri::Engine::ECS {

class Entity;

/**
 * @brief TODO
 */
class EntityManager {
public:
    /**
     * @brief TODO
     */
    EntityId createEntity() {
        assert(m_entityCount < MAX_ENTITIES && "Too many entities in existence.");

        m_entityCount++;

        if (m_recycledIds.empty())
            return m_nextEntityId++;

        EntityId id = m_recycledIds.top();
        m_recycledIds.pop();
        return id;
    }

    /**
     * @brief TODO
     */
    void destroyEntity(EntityId entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        m_signatures[entity].reset();
        m_recycledIds.push(entity);
        m_entityCount--;
    }

    /**
     * @brief TODO
     */
    const ComponentSignature& getSignature(EntityId entity) const {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        return m_signatures[entity];
    }

    /**
     * @brief TODO
     */
    void setSignature(EntityId entity, ComponentSignature signature) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        m_signatures[entity] = signature;
    }

private:
    uint32_t m_entityCount = 0;
    EntityId m_nextEntityId = NULL_ENTITY + 1;
    std::stack<EntityId, std::vector<EntityId>> m_recycledIds;
    std::array<ComponentSignature, MAX_ENTITIES> m_signatures;
};

}  // namespace labeeri::Engine::ECS