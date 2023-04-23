#pragma once

#include "../keys.h"

namespace labeeri::engine {

class Entity;

class Input {
public:
    std::function<void(Entity&, glm::dvec2, glm::dvec2)> m_onMouseMove;
    std::function<void(Entity&, MouseButton, KeyAction, int)> m_onMouseButton;
    std::function<void(Entity&, double)> m_onMouseScroll;
    std::function<void(Entity&, Keyboard, int, KeyAction, int)> m_onKeyboard;
};

}  // namespace labeeri::engine
