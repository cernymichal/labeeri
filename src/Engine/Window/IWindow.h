#pragma once

namespace labeeri::Engine {

class Application;

/**
 * @brief Wheter  not the cursor should be visible and/or disabled.
 */
enum class CursorMode : u8 {
    Normal,
    Hidden,
    Disabled
};

/**
 * @brief Window API abstraction interface.
 */
class IWindow {
public:
    virtual ~IWindow() = default;

    /**
     * @return The current time in seconds.
     */
    virtual f64 currentTime() const = 0;

    /**
     * @return The size of the window in pixels.
     */
    virtual uvec2 frameSize() const = 0;

    /**
     * @return If vertical sync is enabled.
     */
    virtual bool VSync() const = 0;

    /**
     * @param enabled If vertical sync should be enabled.
     */
    virtual void setVSync(bool enabled) = 0;

    /**
     * @return If the window is fullscreen.
     */
    virtual bool fullscreen() const = 0;

    /**
     * @param enabled If the window should be fullscreen.
     */
    virtual void setFullscreen(bool enabled) = 0;

    /**
     * @return If the window is minimized.
     */
    virtual bool minimized() const = 0;

    /**
     * @return If the window was called to be closed.
     */
    virtual bool shouldClose() const = 0;

    /**
     * @brief Swaps the front and back buffers.
     */
    virtual void swapBuffers() = 0;

    /**
     * @brief Polls window events.
     */
    virtual void pollEvents() = 0;

    /**
     * @param mode The cursor mode.
     */
    virtual void setCursorMode(CursorMode mode) = 0;

    /**
     * @brif Sets the OS clipboard content.
     *
     * @param content The content to be set.
     */
    virtual void setClipboardContent(const char* content) const = 0;

    /**
     * @return OS provided getter of OpenGL function addresses.
     */
    virtual void* procAddressGetter() const = 0;

    /**
     * @brief Makes the window the current OpenGL context.
     */
    virtual void makeCurrent() = 0;

    /**
     * @return The current window abstraction.
     */
    static IWindow* Instance() {
        return s_window.get();
    }

private:
    static inline std::unique_ptr<IWindow> s_window;

    friend Application;
};

}  // namespace labeeri::Engine
