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
    const i32 m_scanCode;
    const i32 m_mods;

    EVENT_CLASS_CATEGORY(static_cast<i32>(EventCategory::Input) | static_cast<i32>(EventCategory::Keyboard))

protected:
    KeyboardEvent(KeyboardKey key, i32 scanCode, i32 mods)
        : m_key(key), m_scanCode(scanCode), m_mods(mods) {
    }
};

/**
 * @brief Keyboard key pressed event.
 */
class KeyboardPressEvent : public KeyboardEvent {
public:
    KeyboardPressEvent(KeyboardKey key, i32 scanCode, i32 mods)
        : KeyboardEvent(key, scanCode, mods) {
    }

    EVENT_CLASS_TYPE(KeyboardPress)
};

/**
 * @brief Keyboard key released event.
 */
class KeyboardReleaseEvent : public KeyboardEvent {
public:
    KeyboardReleaseEvent(KeyboardKey key, i32 scanCode, i32 mods)
        : KeyboardEvent(key, scanCode, mods) {
    }

    EVENT_CLASS_TYPE(KeyboardRelease)
};

/**
 * @brief Keyboard key repeat event.
 */
class KeyboardRepeatEvent : public KeyboardEvent {
public:
    KeyboardRepeatEvent(KeyboardKey key, i32 scanCode, i32 mods)
        : KeyboardEvent(key, scanCode, mods) {
    }

    EVENT_CLASS_TYPE(KeyboardRepeat)
};

}  // namespace labeeri::Engine
