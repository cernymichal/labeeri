#pragma once

#include "Engine/Events/IEvent.h"
#include "Engine/Events/Input.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class MouseMoveEvent : public IEvent {
public:
    const dvec2 m_position;
    const dvec2 m_delta;

    MouseMoveEvent(const dvec2& postition, const dvec2& delta)
        : m_position(postition), m_delta(delta) {
    }

    EVENT_CLASS_TYPE(MouseMove)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Mouse))
};

/**
 * @brief TODO
 */
class MouseScrollEvent : public IEvent {
public:
    const double m_delta;

    explicit MouseScrollEvent(double delta) : m_delta(delta) {
    }

    EVENT_CLASS_TYPE(MouseScroll)

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Mouse))
};

/**
 * @brief TODO
 */
class MouseButtonEvent : public IEvent {
public:
    const MouseButton m_button;
    const int m_mods;
    const dvec2 m_position;

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Mouse))

protected:
    MouseButtonEvent(MouseButton button, int mods, dvec2 positon)
        : m_button(button), m_mods(mods), m_position(positon) {
    }
};

/**
 * @brief TODO
 */
class MouseButtonPressEvent : public MouseButtonEvent {
public:
    MouseButtonPressEvent(MouseButton button, int mods, dvec2 position)
        : MouseButtonEvent(button, mods, position) {
    }

    EVENT_CLASS_TYPE(MouseButtonPress)
};

/**
 * @brief TODO
 */
class MouseButtonReleaseEvent : public MouseButtonEvent {
public:
    MouseButtonReleaseEvent(MouseButton button, int mods, dvec2 position)
        : MouseButtonEvent(button, mods, position) {
    }

    EVENT_CLASS_TYPE(MouseButtonRelease)
};

}  // namespace labeeri::Engine
