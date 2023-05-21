#include "Scene.h"

#include "Engine/Scene/Components/Components.h"
#include "Engine/Scene/ECS/Instance.h"

namespace labeeri::Engine {

Scene::Scene() {
    LAB_LOGH2("Scene::Scene()");

    registerDefaultComponents(*m_ecs);

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
        for (const auto& script : m_scripts) {
            if (script->m_entity == dynamic_cast<EntityClickEvent&>(e).m_entity)
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

}  // namespace labeeri::Engine
