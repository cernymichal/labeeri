#include "SceneLayer.h"

#include "Engine/Application.h"

namespace labeeri::Engine {

void SceneLayer::onEvent(IEvent& e) {
    if (!m_scene)
        return;

    if (e.isInCategory(EventCategory::Input) && LAB_APP.focus() != ApplicationFocus::Viewport)
        return;

    m_scene->onEvent(e);
}

}  // namespace labeeri::Engine
