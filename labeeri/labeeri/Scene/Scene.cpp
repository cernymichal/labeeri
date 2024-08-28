#include "Scene.h"

#include "Scene/Components/Components.h"
#include "Scene/ECS/Entity.h"

namespace labeeri {

Scene::Scene() {
    LAB_LOGH2("Scene::Scene()");

    registerDefaultComponents(m_ecs);

    m_systems.physics = m_ecs->registerSystem<PhysicsSystem>();
    m_systems.camera = m_ecs->registerSystem<CameraSystem>();
    m_systems.light = m_ecs->registerSystem<LightSystem>();
    m_systems.render = m_ecs->registerSystem<RenderSystem>();
}

void Scene::onEvent(IEvent& e) {
    if (!(e.isInCategory(EventCategory::Input) || e.isInCategory(EventCategory::Scene)))
        return;

    e.dispatch<UpdateEvent>(LAB_BIND_EVENT_FUNC(onUpdate));
    e.dispatch<FixedUpdateEvent>(LAB_BIND_EVENT_FUNC(onFixedUpdate));

    if (e.eventType() == EventType::EntityClick) {
        auto& clickEvent = dynamic_cast<EntityClickEvent&>(e);
        for (const auto& script : m_scripts) {
            if (script->m_entity == clickEvent.m_entity)
                script->onEvent(e);
        }
    }
    else {
        for (const auto& script : m_scripts)
            script->onEvent(e);
    }
}

bool Scene::onUpdate(const UpdateEvent& e) {
    m_time += e.m_deltaTime;
    m_systems.physics->update(e.m_deltaTime);

    return false;
}

bool Scene::onFixedUpdate(const FixedUpdateEvent& e) {
    return false;
}

void Scene::destroyEntity(EntityId id) {
    m_scripts.remove_if([id](const auto& script) { return script->m_entity.m_id == id; });
}

}  // namespace labeeri
