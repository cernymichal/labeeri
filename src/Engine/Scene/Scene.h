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
    double time() const;

    /**
     * @brief TODO
     */
    void addEntity(const std::shared_ptr<Entity>& entity);

    /**
     * @brief TODO
     */
    void removeEntity(const std::shared_ptr<Entity>& entity);

    /**
     * @brief TODO
     */
    const std::list<std::shared_ptr<Entity>>& entities() const;

    virtual void onEvent(IEvent& e) override;

private:
    std::list<std::shared_ptr<Entity>> m_entities;

    double m_time = 0.0f;

    bool onUpdate(const ApplicationUpdateEvent& e);

    bool onFixedUpdate(const ApplicationFixedUpdateEvent& e);

    bool onInput(IEvent& e);
};

}  // namespace labeeri::Engine
