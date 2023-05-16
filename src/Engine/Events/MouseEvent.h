#pragma once

#include "Engine/Events/IEvent.h"
#include "Engine/Events/Input.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class MouseMoveEvent : public IEvent {
public:
    MouseMoveEvent(const glm::dvec2& postition, const glm::dvec2& delta)
        : m_position(postition), m_delta(delta) {
    }

    const glm::dvec2& position() const {
        return m_position;
    }

    const glm::dvec2& delta() const {
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
class MouseScrollEvent : public IEvent {
public:
    explicit MouseScrollEvent(double delta) : m_delta(delta) {
    }

    double delta() const {
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
class MouseButtonEvent : public IEvent {
public:
    MouseButton button() const {
        return m_button;
    }

    int mods() const {
        return m_mods;
    }

    const glm::dvec2& position() const {
        return m_position;
    }

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Mouse))

protected:
    MouseButton m_button;
    int m_mods;
    glm::dvec2 m_position;

    MouseButtonEvent(MouseButton button, int mods, glm::dvec2 positon)
        : m_button(button), m_mods(mods), m_position(positon) {
    }
};

/**
 * @brief TODO
 */
class MouseButtonPressEvent : public MouseButtonEvent {
public:
    MouseButtonPressEvent(MouseButton button, int mods, glm::dvec2 position)
        : MouseButtonEvent(button, mods, position) {
    }

    EVENT_CLASS_TYPE(MouseButtonPress)
};

/**
 * @brief TODO
 */
class MouseButtonReleaseEvent : public MouseButtonEvent {
public:
    MouseButtonReleaseEvent(MouseButton button, int mods, glm::dvec2 position)
        : MouseButtonEvent(button, mods, position) {
    }

    EVENT_CLASS_TYPE(MouseButtonRelease)
};

}  // namespace labeeri::Engine
