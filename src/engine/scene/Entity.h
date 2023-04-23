#pragma once

#include "../resources/Model.h"
#include "Camera.h"
#include "Input.h"
#include "Movement.h"
#include "Transform.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
class Entity {
public:
    bool m_enabled = true;
    std::shared_ptr<Model> m_model;
    std::shared_ptr<Input> m_input;
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

}  // namespace labeeri::engine
