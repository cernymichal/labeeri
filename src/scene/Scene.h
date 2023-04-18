#pragma once

#include "Entity.h"

inline const double FIXED_UPDATE_INTERVAL = 1.0 / 100.0; // 100 Hz

class Scene {
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

    /**
     * @brief TODO
     */
    void update(double currentTime, double deltaTime);

private:
    std::list<std::shared_ptr<Entity>> m_entities;

    double m_time = 0.0f;
    double m_fixedUpdateTimeAccumulator = 0.0f;
};
