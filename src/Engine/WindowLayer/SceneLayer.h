#pragma once

#include "Engine/Scene/Scene.h"
#include "Engine/WindowLayer/IWindowLayer.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class SceneLayer : public IWindowLayer {
public:
    const Ref<Scene>& scene() const {
        return m_scene;
    }

    void setScene(const Ref<Scene>& scene);

    /**
     * @brief TODO
     */
    virtual void onEvent(IEvent& e) override;

private:
    Ref<Scene> m_scene = nullptr;
};

}  // namespace labeeri::Engine
