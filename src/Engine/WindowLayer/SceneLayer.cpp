#include "SceneLayer.h"

#include "Engine/Application.h"

namespace labeeri::Engine {

void SceneLayer::setScene(const Ref<Scene>& scene) {
    m_scene = scene;

    if (m_scene) {
        LAB_ECS = scene->ecs();
        auto& cameras = m_scene->cameras();
        LAB_CURRENT_CAMERA = cameras.empty() ? NULL_ENTITY : *cameras.begin();
    }
    else {
        LAB_ECS = nullptr;
        LAB_CURRENT_CAMERA = NULL_ENTITY;
    }

    auto event = SceneChangeEvent(scene);
    LAB_APP.emitEvent(event);
}

void SceneLayer::onEvent(IEvent& e) {
    if (!m_scene)
        return;

    if (e.isInCategory(EventCategory::Input) && LAB_APP.focus() != ApplicationFocus::Viewport)
        return;

    m_scene->onEvent(e);
}

}  // namespace labeeri::Engine
