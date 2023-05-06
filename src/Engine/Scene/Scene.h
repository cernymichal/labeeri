#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Scene/Entity.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Scene : IEventReceiver {
public:
    /**
     * @brief TODO
     */
    Scene();

    /**
     * @brief TODO
     */
    double time() const {
        return m_time;
    }

    /**
     * @brief TODO
     */
    void addEntity(const EntityRef& entity);

    /**
     * @brief TODO
     */
    void addEntity(const EntityPack& entities);

    /**
     * @brief TODO
     */
    void removeEntity(const EntityRef& entity);

    /**
     * @brief TODO
     */
    const std::list<EntityRef>& entities() const {
        return m_entities;
    }

    virtual void onEvent(IEvent& e) override;

private:
    std::list<EntityRef> m_entities;

    double m_time = 0.0f;

    bool onUpdate(const ApplicationUpdateEvent& e);

    bool onFixedUpdate(const ApplicationFixedUpdateEvent& e);

    bool onInput(IEvent& e);
};

}  // namespace labeeri::Engine
