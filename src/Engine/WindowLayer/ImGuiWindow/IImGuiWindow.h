#pragma once

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class IImGuiWindow {
public:
    virtual ~IImGuiWindow() = default;

    /**
     * @brief TODO
     */
    virtual void draw() = 0;
};

}  // namespace labeeri::Engine
