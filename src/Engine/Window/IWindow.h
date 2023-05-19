#pragma once

namespace labeeri::Engine {

class Application;

enum class CursorMode : uint8_t {
    Normal,
    Hidden,
    Disabled
};

class IWindow {
public:
    /**
     * @brief TODO
     */
    virtual ~IWindow() = default;

    /**
     * @brief TODO
     */
    virtual double currentTime() const = 0;

    /**
     * @brief TODO
     */
    virtual glm::uvec2 m_frameBufferSize() const = 0;

    /**
     * @brief TODO
     */
    virtual bool VSync() const = 0;

    /**
     * @brief TODO
     */
    virtual void setVSync(bool enabled) = 0;

    /**
     * @brief TODO
     */
    virtual bool fullscreen() const = 0;    

    /**
     * @brief TODO
     */
    virtual void setFullscreen(bool enabled) = 0;

    /**
     * @brief TODO
     */
    virtual bool minimized() const = 0;   

    /**
     * @brief TODO
     */
    virtual bool shouldClose() const = 0;

    /**
     * @brief TODO
     */
    virtual void swapBuffers() = 0;

    /**
     * @brief TODO
     */
    virtual void pollEvents() = 0;

    /**
     * @brief TODO
     */
    virtual void setCursorMode(CursorMode mode) = 0;

    /**
     * @brief TODO
     */
    virtual void setClipboardContent(const char* content) const = 0;

    /**
     * @brief TODO
     */
    virtual void* procAddressGetter() const = 0;

    /**
     * @brief TODO
     */
    virtual void makeCurrent() = 0;

    /**
     * @brief TODO
     */
    static IWindow* Instance() {
        return s_window.get();
    }

private:
    static inline std::unique_ptr<IWindow> s_window;

    friend Application;
};

}  // namespace labeeri::Engine
