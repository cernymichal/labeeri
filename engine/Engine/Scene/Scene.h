#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/IEventReceiver.h"
#include "Engine/Renderer/RendererParameters.h"
#include "Engine/Resources/Scripts/IScript.h"
#include "Engine/Scene/ECS/Instance.h"
#include "Engine/Scene/Systems/Systems.h"

namespace labeeri::Engine {

class ViewportLayer;
class Entity;

/**
 * @brief Hold all data for a scene. (ECS, systems, scripts, ...)
 */
class Scene : IEventReceiver {
public:
    RenderSceneParameters m_renderParameters;

    /**
     * @brief Create a new scene.
     *
     * Instantiates ECS.
     */
    Scene();

    /**
     * @return The ECS instance.
     */
    const std::shared_ptr<ECS::Instance>& ecs() const {
        return m_ecs;
    }

    /**
     * @return The current scene time.
     */
    f64 time() const {
        return m_time;
    }

    /**
     * &return The cameras in the scene.
     */
    const std::set<EntityId>& cameras() const {
        return m_systems.camera->entities();
    }

    /**
     * @brief Add a new script to the scene.
     *
     * @tparam T The type of the script.
     * @tparam Args The types of the arguments to pass to the constructor.
     * @param args The arguments to pass to the constructor.
     * @return The created script.
     */
    template <typename T, typename... Args>
    T* addScript(Args&&... args) {
        IScript* script = m_scripts.emplace_back(makeScoped<T>(std::forward<Args>(args)...)).get();
        return static_cast<T*>(script);
    }

    virtual void onEvent(IEvent& e) override;

private:
    std::shared_ptr<ECS::Instance> m_ecs = std::make_shared<ECS::Instance>();
    struct {
        std::shared_ptr<PhysicsSystem> physics;
        std::shared_ptr<CameraSystem> camera;
        std::shared_ptr<LightSystem> light;
        std::shared_ptr<RenderSystem> render;
    } m_systems;
    std::list<Scoped<IScript>> m_scripts;
    f64 m_time = 0.0;

    bool onUpdate(const UpdateEvent& e);

    bool onFixedUpdate(const FixedUpdateEvent& e);

    void destroyEntity(EntityId id);

    friend class ViewportLayer;
    friend class Entity;
};

}  // namespace labeeri::Engine
