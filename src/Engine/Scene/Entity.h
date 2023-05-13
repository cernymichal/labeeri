#pragma once

#include "Engine/Resources/Model.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Scene/Light.h"
#include "Engine/Scene/Look.h"
#include "Engine/Scene/Movement.h"
#include "Engine/Scene/Transform.h"

namespace labeeri::Engine {

using EntityPack = std::vector<Ref<Entity>>;

/**
 * @brief TODO
 */
class Entity {
public:
    bool m_enabled = true;
    Ref<Model> m_model;
    Ref<Look> m_look;
    Ref<Movement> m_movement;
    Ref<Camera> m_camera;
    Ref<Light> m_light;

    std::function<void(Entity&)> m_onFixedUpdate;
    std::function<void(Entity&, double)> m_onUpdate;

    /**
     * @brief TODO
     */
    ~Entity() {
        //m_transform->destroy();
    }

    /**
     * @brief TODO
     */
    const Ref<Transform>& transform() const {
        return m_transform;
    }

    static Ref<Entity> Create() {
        auto entity = std::shared_ptr<Entity>(new Entity());
        entity->m_transform->m_entity = entity;
        return entity;
    }

private:
    Ref<Transform> m_transform = makeRef<Transform>();

    Entity() = default;

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
