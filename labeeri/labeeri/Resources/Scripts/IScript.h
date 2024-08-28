#pragma once

#include "Events/ApplicationEvent.h"
#include "Events/IEventReceiver.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/SceneEvent.h"
#include "Scene/ECS/Entity.h"

namespace labeeri {

class Scene;

/**
 * @brief Entity script interface.
 */
class IScript : IEventReceiver {
public:
    /**
     * @param entity The entity that this script is attached to.
     */
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

    /**
     * @brief Called every frame.
     *
     * @param e The update event.
     */
    virtual void onUpdate(const UpdateEvent& e) {
    }

    /**
     * @brief Called at a fixed rate. (every FIXED_UPDATE_INTERVAL seconds)
     *
     * @param e The fixed update event.
     */
    virtual void onFixedUpdate(const FixedUpdateEvent& e) {
    }

    /**
     * @brief Called when the entity is clicked.
     *
     * @param e The entity click event.
     */
    virtual void onEntityClick(const EntityClickEvent& e) {
    }

    /**
     * @brief Called when the mouse is moved.
     *
     * @param e The mouse move event.
     */
    virtual void onMouseMove(const MouseMoveEvent& e) {
    }

    /**
     * @brief Called when a key is pressed.
     *
     * @param e The keyboard press event.
     */
    virtual void onKeyboardPress(const KeyboardPressEvent& e) {
    }

    /**
     * @brief Called when a key is released.
     *
     * @param e The keyboard release event.
     */
    virtual void onKeyboardRelease(const KeyboardReleaseEvent& e) {
    }

    /**
     * @brief Called when a mouse button is pressed.
     *
     * @param e The mouse button press event.
     */
    virtual void onMouseButtonPress(const MouseButtonPressEvent& e) {
    }

    /**
     * @brief Called when a mouse button is released.
     *
     * @param e The mouse button release event.
     */
    virtual void onMouseButtonRelease(const MouseButtonReleaseEvent& e) {
    }

    friend Scene;
};

}  // namespace labeeri
