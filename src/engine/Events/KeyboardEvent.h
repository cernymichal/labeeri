#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Events/Input.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class KeyboardEvent : public Event {
public:
    inline Keyboard key() const {
        return m_key;
    }

    inline int scanCode() const {
        return m_scanCode;
    }

    inline int mods() const {
        return m_mods;
    }

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Keyboard))

protected:
    Keyboard m_key;
    int m_scanCode;
    int m_mods;

    KeyboardEvent(Keyboard key, int scanCode, int mods)
        : m_key(key), m_scanCode(scanCode), m_mods(mods) {
    }
};

/**
 * @brief TODO
 */
class KeyboardPressEvent : public KeyboardEvent {
public:
    KeyboardPressEvent(Keyboard key, int scanCode, int mods)
        : KeyboardEvent(key, scanCode, mods) {
    }

    EVENT_CLASS_TYPE(KeyboardPress)
};

/**
 * @brief TODO
 */
class KeyboardReleaseEvent : public KeyboardEvent {
public:
    KeyboardReleaseEvent(Keyboard key, int scanCode, int mods)
        : KeyboardEvent(key, scanCode, mods) {
    }

    EVENT_CLASS_TYPE(KeyboardRelease)
};

/**
 * @brief TODO
 */
class KeyboardRepeatEvent : public KeyboardEvent {
public:
    KeyboardRepeatEvent(Keyboard key, int scanCode, int mods)
        : KeyboardEvent(key, scanCode, mods) {
    }

    EVENT_CLASS_TYPE(KeyboardRepeat)
};

}  // namespace labeeri::Engine
