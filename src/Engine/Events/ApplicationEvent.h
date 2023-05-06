#pragma once

#include "Engine/Events/IEvent.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class WindowResizeEvent : public IEvent {
public:
    explicit WindowResizeEvent(const glm::uvec2& windowSize) : m_windowSize(windowSize) {
    }

    const glm::uvec2& windowSize() const {
        return m_windowSize;
    }

    EVENT_CLASS_TYPE(WindowResize)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Application))

private:
    glm::uvec2 m_windowSize;
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
class ApplicationUpdateEvent : public IEvent {
public:
    explicit ApplicationUpdateEvent(double deltaTime) : m_deltaTime(deltaTime) {
    }

    double deltaTime() const {
        return m_deltaTime;
    }

    EVENT_CLASS_TYPE(ApplicationUpdate)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Application))

private:
    double m_deltaTime;
};

/**
 * @brief TODO
 */
class ApplicationFixedUpdateEvent : public IEvent {
public:
    EVENT_CLASS_TYPE(ApplicationFixedUpdate)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Application))
};

}  // namespace labeeri::Engine
