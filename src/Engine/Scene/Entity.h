#pragma once

#include "Engine/Resources/Model.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Scene/Look.h"
#include "Engine/Scene/Movement.h"
#include "Engine/Scene/Transform.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Entity {
public:
    bool m_enabled = true;
    ModelRef m_model;
    std::shared_ptr<Look> m_look;
    std::shared_ptr<Movement> m_movement;
    std::shared_ptr<Camera> m_camera;

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

}  // namespace labeeri::Engine
