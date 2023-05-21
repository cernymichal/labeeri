#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/IEventReceiver.h"
#include "Engine/Renderer/RendererParameters.h"
#include "Engine/Resources/Scripts/IScript.h"
#include "Engine/Scene/ECS/Instance.h"
#include "Engine/Scene/Systems/Systems.h"

namespace labeeri::Engine {

class ViewportLayer;

/**
 * @brief TODO
 */
class Scene : IEventReceiver {
public:
    RenderSceneParameters m_renderParameters;

    /**
     * @brief TODO
     */
    Scene();

    /**
     * @brief TODO
     */
    const std::shared_ptr<ECS::Instance>& ecs() const {
        return m_ecs;
    }

    /**
     * @brief TODO
     */
    double time() const {
        return m_time;
    }

    /**
     * @brief TODO
     */
    const std::set<EntityId>& cameras() const {
        return m_systems.camera->entities();
    }

    /**
     * @brief TODO
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
    double m_time = 0.0;

    bool onUpdate(const UpdateEvent& e);

    bool onFixedUpdate(const FixedUpdateEvent& e);

    friend class ViewportLayer;
};

}  // namespace labeeri::Engine
