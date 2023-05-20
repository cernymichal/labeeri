#include "SceneLayer.h"

#include "Engine/Application.h"

namespace labeeri::Engine {

void SceneLayer::setScene(const Ref<Scene>& scene) {
    m_scene = scene;
    LAB_ECS = m_scene ? scene->ecs() : nullptr;

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
