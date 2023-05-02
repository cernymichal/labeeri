#pragma once

#include "Engine/Resources/Model.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Scene/Light.h"
#include "Engine/Scene/Look.h"
#include "Engine/Scene/Movement.h"
#include "Engine/Scene/Transform.h"

namespace labeeri::Engine {

using EntityRef = std::shared_ptr<Entity>;
using EntityPack = std::vector<EntityRef>;

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
    std::shared_ptr<Light> m_light;

    std::function<void(Entity&)> m_onFixedUpdate;
    std::function<void(Entity&, double)> m_onUpdate;

    /**
     * @brief TODO
     */
    ~Entity() {
        m_transform->destroy();
    }

    /**
     * @brief TODO
     */
    inline const std::shared_ptr<Transform>& transform() const {
        return m_transform;
    }

    static EntityRef Create() {
        auto entity = std::make_shared<Entity>(Entity());
        entity->m_transform->m_entity = entity;
        return entity;
    }

private:
    std::shared_ptr<Transform> m_transform = std::make_shared<Transform>();

    Entity() {
    }

    void fixedUpdate() {
        if (!m_enabled)
            return;

        if (m_onFixedUpdate)
            m_onFixedUpdate(*this);
    }

    void update(double deltaTime) {
        if (!m_enabled)
            return;

        if (m_onUpdate)
            m_onUpdate(*this, deltaTime);

        if (m_movement)
            m_movement->update(deltaTime);
    }

    friend class Scene;
};

}  // namespace labeeri::Engine
