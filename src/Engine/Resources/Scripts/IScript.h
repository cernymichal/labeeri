#pragma once

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/IEventReceiver.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/SceneEvent.h"
#include "Engine/Scene/ECS/Entity.h"

namespace labeeri::Engine {

class Scene;

/**
 * @brief TODO
 */
class IScript : IEventReceiver {
public:
    IScript(Entity entity) : m_entity(entity) {
    }

    virtual void onEvent(IEvent& e) override final {
        e.dispatch<UpdateEvent>([this](auto& e) {onUpdate(e); return false; });
        e.dispatch<FixedUpdateEvent>([this](auto& e) {onFixedUpdate(e); return false; });
        e.dispatch<EntityClickEvent>([this](auto& e) {onEntityClick(e); return false; });
        e.dispatch<MouseMoveEvent>([this](auto& e) {onMouseMove(e); return false; });
        e.dispatch<KeyboardPressEvent>([this](auto& e) {onKeyboardPress(e); return false; });
        e.dispatch<KeyboardReleaseEvent>([this](auto& e) {onKeyboardRelease(e); return false; });
        e.dispatch<MouseButtonPressEvent>([this](auto& e) {onMouseButtonPress(e); return false; });
        e.dispatch<MouseButtonReleaseEvent>([this](auto& e) {onMouseButtonRelease(e); return false; });
    }

protected:
    Entity m_entity;

    virtual void onUpdate(const UpdateEvent& e) {
    }

    virtual void onFixedUpdate(const FixedUpdateEvent& e) {
    }

    virtual void onEntityClick(const EntityClickEvent& e) {
    }

    virtual void onMouseMove(const MouseMoveEvent& e) {
    }

    virtual void onKeyboardPress(const KeyboardPressEvent& e) {
    }

    virtual void onKeyboardRelease(const KeyboardReleaseEvent& e) {
    }

    virtual void onMouseButtonPress(const MouseButtonPressEvent& e) {
    }

    virtual void onMouseButtonRelease(const MouseButtonReleaseEvent& e) {
    }

    friend Scene;
};

}  // namespace labeeri::Engine
