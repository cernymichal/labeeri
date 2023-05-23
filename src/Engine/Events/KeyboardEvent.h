#pragma once

#include "Engine/Events/IEvent.h"
#include "Engine/Events/Input.h"

namespace labeeri::Engine {

/**
 * @brief General keyboard event.
 */
class KeyboardEvent : public IEvent {
public:
    const KeyboardKey m_key;
    const int m_scanCode;
    const int m_mods;

    EVENT_CLASS_CATEGORY(static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::Keyboard))

protected:
    KeyboardEvent(KeyboardKey key, int scanCode, int mods)
        : m_key(key), m_scanCode(scanCode), m_mods(mods) {
    }
};

/**
 * @brief Keyboard key pressed event.
 */
class KeyboardPressEvent : public KeyboardEvent {
public:
    KeyboardPressEvent(KeyboardKey key, int scanCode, int mods)
        : KeyboardEvent(key, scanCode, mods) {
    }

    EVENT_CLASS_TYPE(KeyboardPress)
};

/**
 * @brief Keyboard key released event.
 */
class KeyboardReleaseEvent : public KeyboardEvent {
public:
    KeyboardReleaseEvent(KeyboardKey key, int scanCode, int mods)
        : KeyboardEvent(key, scanCode, mods) {
    }

    EVENT_CLASS_TYPE(KeyboardRelease)
};

/**
 * @brief Keyboard key repeat event.
 */
class KeyboardRepeatEvent : public KeyboardEvent {
public:
    KeyboardRepeatEvent(KeyboardKey key, int scanCode, int mods)
        : KeyboardEvent(key, scanCode, mods) {
    }

    EVENT_CLASS_TYPE(KeyboardRepeat)
};

}  // namespace labeeri::Engine
