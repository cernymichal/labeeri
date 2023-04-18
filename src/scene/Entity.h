#pragma once

#include <functional>

#include "../shaders/Model.h"
#include "Transform.h"

/**
 * @brief TODO
 */
class Entity {
public:
    std::shared_ptr<Model> m_model;

    std::function<void(Entity&)> m_onFixedUpdate;
    std::function<void(Entity&, double)> m_onUpdate;

    /**
     * @brief TODO
     */
    Entity();

    /**
     * @brief TODO
     */
    ~Entity();

    /**
     * @brief TODO
     */
    const std::shared_ptr<Transform>& transform() const;

private:
    std::shared_ptr<Transform> m_transform = std::make_shared<Transform>();

    void fixedUpdate();

    void update(double deltaTime);

    friend class Scene;
};
