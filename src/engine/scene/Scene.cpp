#include "Scene.h"

namespace labeeri::engine {

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

void Scene::update(double deltaTime) {
    m_fixedUpdateTimeAccumulator += deltaTime;

    if (m_fixedUpdateTimeAccumulator >= FIXED_UPDATE_INTERVAL) {
        double fixedUpdateDeltaTime = deltaTime / floor(m_fixedUpdateTimeAccumulator / FIXED_UPDATE_INTERVAL);
        while (m_fixedUpdateTimeAccumulator >= FIXED_UPDATE_INTERVAL) {
            m_time += fixedUpdateDeltaTime;

            for (const auto& entity : m_entities)
                entity->fixedUpdate();

            m_fixedUpdateTimeAccumulator -= FIXED_UPDATE_INTERVAL;
        }
    }
    else
        m_time += deltaTime;

    for (const auto& entity : m_entities)
        entity->update(deltaTime);
}

}  // namespace labeeri::engine
