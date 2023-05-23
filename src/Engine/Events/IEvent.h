#pragma once

namespace labeeri::Engine {

#define LAB_BIND_EVENT_FUNC(f) [this](auto& e) { return f(e); }

#define EVENT_CLASS_TYPE(type)                                                 \
    static EventType StaticEventType() { return EventType::type; }             \
    virtual EventType eventType() const override { return StaticEventType(); } \
    virtual const char* name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int categoryFlags() const override { return category; }

enum class EventType : uint8_t {
    None,
    WindowResize,
    ApplicationRender,
    ApplicationUpdate,
    ApplicationFixedUpdate,
    KeyboardPress,
    KeyboardRelease,
    KeyboardRepeat,
    MouseButtonPress,
    MouseButtonRelease,
    MouseMove,
    MouseScroll,
    SceneChange,
    EntityClick
};

enum class EventCategory : int {
    None = 0,
    Application = LAB_BIT(0),
    Input = LAB_BIT(1),
    Keyboard = LAB_BIT(2),
    Mouse = LAB_BIT(3),
    Scene = LAB_BIT(4),
};

/**
 * @brief Event object interface.
 */
class IEvent {
public:
    bool m_handled = false;

    virtual ~IEvent() = default;

    /**
     * @return The type of the event.
     */
    virtual EventType eventType() const = 0;

    /**
     * @return The name of the event.
     */
    virtual const char* name() const = 0;

    /**
     * @return The categories of the event.
     */
    virtual int categoryFlags() const = 0;

    /**
     * @return If the event is in the given category.
     */
    bool isInCategory(EventCategory category) const {
        return categoryFlags() & static_cast<int>(category);
    }

    /**
     * @brief Dispatches the handler if the event is of the given type.
     *
     * @tparam T The type of the event.
     * @tparam F The type of the handler.
     * @param handler The handler to dispatch.
     * @return If the event was handled.
     */
    template <typename T, typename F>
    bool dispatch(const F& handler) {
        if (eventType() != T::StaticEventType())
            return false;

        m_handled |= handler(static_cast<T&>(*this));
        return true;
    }
};

inline std::ostream& operator<<(std::ostream& stream, const IEvent& event) {
    return stream << event.name();
}

}  // namespace labeeri::Engine
