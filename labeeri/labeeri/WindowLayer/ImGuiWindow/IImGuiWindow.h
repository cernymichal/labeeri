#pragma once

namespace labeeri {

/**
 * @brief ImGui window interface.
 */
class IImGuiWindow {
public:
    virtual ~IImGuiWindow() = default;

    /**
     * @return The name of the window.
     */
    virtual const std::string& name() const = 0;

    /**
     * @brief Draws the window.
     *
     * @return True if the window is open, false if it should be closed.
     */
    virtual bool draw() = 0;

    /**
     * @brief Compares two windows by their name.
     */
    bool operator==(const IImGuiWindow& other) const {
        return name() == other.name();
    }
};

}  // namespace labeeri
