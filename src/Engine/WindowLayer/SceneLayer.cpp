#include "SceneLayer.h"

#include "Engine/Application.h"
#include "Engine/Events/SceneEvent.h"

namespace labeeri::Engine {

void SceneLayer::setScene(const Ref<Scene>& scene) {
    m_scene = scene;
    LAB_ECS = scene->ecs();
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
