#pragma once

#include "Engine/Events/IEvent.h"

namespace labeeri::Engine {

/**
 * @brief An event describing a window resize.
 */
class WindowResizeEvent : public IEvent {
public:
    const uvec2 m_windowSize;

    explicit WindowResizeEvent(const uvec2& windowSize) : m_windowSize(windowSize) {
    }

    EVENT_CLASS_TYPE(WindowResize)

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Application))
};

/**
 * @brief An event sent out when the window is minimized (iconified).
 */
class WindowMinimizeEvent : public IEvent {
public:
    const bool m_iconified;

    explicit WindowMinimizeEvent(bool iconified) : m_iconified(iconified) {
    }

    EVENT_CLASS_TYPE(WindowResize)

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Application))
};

/**
 * @brief An event signaling that a new frame should be rendered.
 */
class ApplicationRenderEvent : public IEvent {
public:
    EVENT_CLASS_TYPE(ApplicationRender)

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Application))
};

/**
 * @brief Update event distributed once per frame.
 */
class UpdateEvent : public IEvent {
public:
    const f64 m_deltaTime;

    explicit UpdateEvent(f64 deltaTime) : m_deltaTime(deltaTime) {
    }

    EVENT_CLASS_TYPE(ApplicationUpdate)

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Application) | static_cast<i32>(EventCategory::Scene))
};

/**
 * @brief Fixed update event is distributed a a fix rate of 50Hz. (1 / FIXED_UPDATE_INTERVAL)
 */
class FixedUpdateEvent : public IEvent {
public:
    EVENT_CLASS_TYPE(ApplicationFixedUpdate)

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Application) | static_cast<i32>(EventCategory::Scene))
};

class Scene;

/**
 * @brief An event signaling that the current scene has been switched.
 */
class SceneChangeEvent : public IEvent {
public:
    const Ref<Scene> m_scene;

    explicit SceneChangeEvent(const Ref<Scene>& scene) : m_scene(scene) {
    }

    EVENT_CLASS_TYPE(SceneChange)

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Application))
};

}  // namespace labeeri::Engine
