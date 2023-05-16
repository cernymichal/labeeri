#include "Scene.h"

namespace labeeri::Engine {

Scene::Scene() {
    LAB_LOGH2("Scene::Scene()");
}

void Scene::addEntity(const Ref<Entity>& entity) {
    m_entities.push_back(entity);
}

void Scene::addEntity(const EntityPack& entities) {
    for (const auto& entity : entities)
        m_entities.push_back(entity);
}

void Scene::removeEntity(const Ref<Entity>& entity) {
    auto entityPosition = std::find(m_entities.begin(), m_entities.end(), entity);
    if (entityPosition != m_entities.end())
		m_entities.erase(entityPosition);
}

void Scene::onEvent(IEvent& e) {
    e.dispatch<ApplicationUpdateEvent>(LAB_BIND_EVENT_FUNC(Scene::onUpdate));
    e.dispatch<ApplicationFixedUpdateEvent>(LAB_BIND_EVENT_FUNC(Scene::onFixedUpdate));

    if (e.isInCategory(EventCategory::Input) && !e.m_handled)
        onInput(e);
}

bool Scene::onUpdate(const ApplicationUpdateEvent& e) {
    double deltaTime = e.deltaTime();
    m_time += deltaTime;

    for (const auto& entity : m_entities)
        entity->update(deltaTime);

    return false;
}

bool Scene::onFixedUpdate(const ApplicationFixedUpdateEvent& e) {
    for (const auto& entity : m_entities)
        entity->fixedUpdate();

    return false;
}

bool Scene::onInput(IEvent& e) {
    for (auto& entity : entities()) {
        if (!entity->m_enabled)
            continue;

        if (entity->m_movement)
            entity->m_movement->onEvent(e);

        if (entity->m_look)
            entity->m_look->onEvent(e);
    }

    return true;
}

}  // namespace labeeri::Engine
