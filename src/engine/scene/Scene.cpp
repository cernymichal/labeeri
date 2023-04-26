#include "Scene.h"

namespace labeeri::Engine {

Scene::Scene() {
    LAB_LOGH2("Scene::Scene()");
}

double Scene::time() const {
    return m_time;
}

void Scene::addEntity(const std::shared_ptr<Entity>& entity) {
    m_entities.push_back(entity);
}

void Scene::removeEntity(const std::shared_ptr<Entity>& entity) {
    m_entities.remove(entity);
}

const std::list<std::shared_ptr<Entity>>& Scene::entities() const {
    return m_entities;
}

void Scene::onEvent(Event& e) {
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

bool Scene::onInput(Event& e) {
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
