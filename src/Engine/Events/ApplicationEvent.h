#pragma once

#include "Engine/Events/IEvent.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class WindowResizeEvent : public IEvent {
public:
    const uvec2 m_windowSize;

    explicit WindowResizeEvent(const uvec2& windowSize) : m_windowSize(windowSize) {
    }

    EVENT_CLASS_TYPE(WindowResize)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Application))
};

/**
 * @brief TODO
 */
class WindowMinimizeEvent : public IEvent {
public:
    const bool m_iconified;

    explicit WindowMinimizeEvent(bool iconified) : m_iconified(iconified) {
    }

    EVENT_CLASS_TYPE(WindowResize)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Application))
};

/**
 * @brief TODO
 */
class ApplicationRenderEvent : public IEvent {
public:
    EVENT_CLASS_TYPE(ApplicationRender)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Application))
};

/**
 * @brief TODO
 */
class UpdateEvent : public IEvent {
public:
    const double m_deltaTime;

    explicit UpdateEvent(double deltaTime) : m_deltaTime(deltaTime) {
    }

    EVENT_CLASS_TYPE(ApplicationUpdate)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Application) | static_cast<int>(EventCategory::Scene))
};

/**
 * @brief TODO
 */
class FixedUpdateEvent : public IEvent {
public:
    EVENT_CLASS_TYPE(ApplicationFixedUpdate)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Application) | static_cast<int>(EventCategory::Scene))
};

class Scene;

/**
 * @brief TODO
 */
class SceneChangeEvent : public IEvent {
public:
    const Ref<Scene> m_scene;

    explicit SceneChangeEvent(const Ref<Scene>& scene) : m_scene(scene) {
    }

    EVENT_CLASS_TYPE(SceneChange)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Application))
};

}  // namespace labeeri::Engine
