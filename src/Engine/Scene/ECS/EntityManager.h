#pragma once

#include "Engine/Scene/ECS/Common.h"

namespace labeeri::Engine::ECS {

class Entity;

/**
 * @brief Manages the creation and destruction of entities.
 */
class EntityManager {
public:
    /**
     * @brief Creates a new entity.
     *
     * @return The created entity.
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
     * @brief Destroys an entity.
     *
     * @param entity The entity to destroy.
     */
    void destroyEntity(EntityId entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        m_signatures[entity].reset();
        m_recycledIds.push(entity);
        m_entityCount--;
    }

    /**
     * @brief Gets the component signature of an entity.
     *
     * @param entity The entity.
     * @return The signature of the entity's components.
     */
    const ComponentSignature& getSignature(EntityId entity) const {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        return m_signatures[entity];
    }

    /**
     * @brief Sets the component signature of an entity.
     *
     * @param entity The entity.
     * @param signature The signature of the entity's components.
     */
    void setSignature(EntityId entity, ComponentSignature signature) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        m_signatures[entity] = signature;
    }

    /**
     * @return The number of entities in existence.
     */
    u32 entityCount() const {
        return m_entityCount;
    }

private:
    u32 m_entityCount = 0;
    EntityId m_nextEntityId = NULL_ENTITY + 1;
    std::stack<EntityId, std::vector<EntityId>> m_recycledIds;
    std::array<ComponentSignature, MAX_ENTITIES> m_signatures;
};

}  // namespace labeeri::Engine::ECS