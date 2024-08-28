#pragma once

#include "Scene/Scene.h"
#include "WindowLayer/IWindowLayer.h"

namespace labeeri {

/**
 * @brief Window layer holding the current scene.
 */
class SceneLayer : public IWindowLayer {
public:
    /**
     * @return The current scene.
     */
    const Ref<Scene>& scene() const {
        return m_scene;
    }

    /**
     * @brief Switch scenes.
     *
     * @param scene The new scene.
     */
    void setScene(const Ref<Scene>& scene);

    virtual void onEvent(IEvent& e) override;

private:
    Ref<Scene> m_scene = nullptr;
};

}  // namespace labeeri
