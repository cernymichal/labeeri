#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Scene/Scene.h"
#include "Engine/WindowLayer/IWindowLayer.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class SceneLayer : public IWindowLayer {
public:
    std::shared_ptr<Scene> m_scene = nullptr;

    /**
     * @brief TODO
     */
    void onEvent(IEvent& e) override;
};

}  // namespace labeeri::Engine
