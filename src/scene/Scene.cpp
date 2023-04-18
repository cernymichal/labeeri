#include "Scene.h"

Scene::Scene() {
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

void Scene::update(double currentTime, double deltaTime) {
    m_time = currentTime;
    m_fixedUpdateTimeAccumulator += deltaTime;

    while (m_fixedUpdateTimeAccumulator >= FIXED_UPDATE_INTERVAL) {
        for (const auto& entity : m_entities)
            entity->fixedUpdate();
        m_fixedUpdateTimeAccumulator -= FIXED_UPDATE_INTERVAL;
    }

    for (const auto& entity : m_entities)
        entity->update(deltaTime);
}
