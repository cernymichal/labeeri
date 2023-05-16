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
    virtual const std::string& name() const = 0;

    /**
     * @brief TODO
     */
    virtual bool draw() = 0;

    /**
     * @brief TODO
     */
    bool operator==(const IImGuiWindow& other) const {
        return name() == other.name();
    }
};

}  // namespace labeeri::Engine
