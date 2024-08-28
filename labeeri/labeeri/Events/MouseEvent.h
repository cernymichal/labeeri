#pragma once

#include "Events/IEvent.h"
#include "Events/Input.h"

namespace labeeri {

/**
 * @brief Mouse moved event.
 */
class MouseMoveEvent : public IEvent {
public:
    const dvec2 m_position;
    const dvec2 m_delta;

    MouseMoveEvent(const dvec2& postition, const dvec2& delta)
        : m_position(postition), m_delta(delta) {
    }

    EVENT_CLASS_TYPE(MouseMove)

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Input) | static_cast<i32>(EventCategory::Mouse))
};

/**
 * @brief Scroll wheel event.
 */
class MouseScrollEvent : public IEvent {
public:
    const f64 m_delta;

    explicit MouseScrollEvent(f64 delta) : m_delta(delta) {
    }

    EVENT_CLASS_TYPE(MouseScroll)

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Input) | static_cast<i32>(EventCategory::Mouse))
};

/**
 * @brief General mouse button event.
 */
class MouseButtonEvent : public IEvent {
public:
    const MouseButton m_button;
    const i32 m_mods;
    const dvec2 m_position;

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Input) | static_cast<i32>(EventCategory::Mouse))

protected:
    MouseButtonEvent(MouseButton button, i32 mods, dvec2 positon)
        : m_button(button), m_mods(mods), m_position(positon) {
    }
};

/**
 * @brief Mouse button pressed event.
 */
class MouseButtonPressEvent : public MouseButtonEvent {
public:
    MouseButtonPressEvent(MouseButton button, i32 mods, dvec2 position)
        : MouseButtonEvent(button, mods, position) {
    }

    EVENT_CLASS_TYPE(MouseButtonPress)
};

/**
 * @brief Mouse button released event.
 */
class MouseButtonReleaseEvent : public MouseButtonEvent {
public:
    MouseButtonReleaseEvent(MouseButton button, i32 mods, dvec2 position)
        : MouseButtonEvent(button, mods, position) {
    }

    EVENT_CLASS_TYPE(MouseButtonRelease)
};

}  // namespace labeeri
