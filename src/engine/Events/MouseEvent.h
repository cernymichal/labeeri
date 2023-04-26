#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Events/Input.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class MouseMoveEvent : public Event {
public:
    MouseMoveEvent(const glm::dvec2& postition, const glm::dvec2& delta)
        : m_position(postition), m_delta(delta) {
    }

    inline const glm::dvec2& position() const {
        return m_position;
    }

    inline const glm::dvec2& delta() const {
        return m_delta;
    }

    EVENT_CLASS_TYPE(MouseMove)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Mouse))

protected:
    glm::dvec2 m_position;
    glm::dvec2 m_delta;
};

/**
 * @brief TODO
 */
class MouseScrollEvent : public Event {
public:
    MouseScrollEvent(double delta) : m_delta(delta) {
    }

    inline double delta() const {
        return m_delta;
    }

    EVENT_CLASS_TYPE(MouseScroll)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Mouse))

protected:
    double m_delta;
};

/**
 * @brief TODO
 */
class MouseButtonEvent : public Event {
public:
    inline MouseButton button() const {
        return m_button;
    }

    inline int mods() const {
        return m_mods;
    }

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Mouse))

protected:
    MouseButton m_button;
    int m_mods;

    MouseButtonEvent(MouseButton button, int mods)
        : m_button(button), m_mods(mods) {
    }
};

/**
 * @brief TODO
 */
class MouseButtonPressEvent : public MouseButtonEvent {
public:
    MouseButtonPressEvent(MouseButton button, int mods)
        : MouseButtonEvent(button, mods) {
    }

    EVENT_CLASS_TYPE(MouseButtonPress)
};

/**
 * @brief TODO
 */
class MouseButtonReleaseEvent : public MouseButtonEvent {
public:
    MouseButtonReleaseEvent(MouseButton button, int mods)
        : MouseButtonEvent(button, mods) {
    }

    EVENT_CLASS_TYPE(MouseButtonRelease)
};

}  // namespace labeeri::Engine
