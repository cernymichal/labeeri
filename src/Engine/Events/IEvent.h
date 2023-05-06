#pragma once

namespace labeeri::Engine {

#define LAB_BIND_EVENT_FUNC(f) std::bind(&f, this, std::placeholders::_1)

#define EVENT_CLASS_TYPE(type)                                                 \
    static EventType staticEventType() { return EventType::type; }             \
    virtual EventType eventType() const override { return staticEventType(); } \
    virtual const char* name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int categoryFlags() const override { return category; }

/**
 * @brief TODO
 */
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
    MouseScroll
};

/**
 * @brief TODO
 */
enum class EventCategory : int {
    None = 0,
    Application = LAB_BIT(0),
    Input = LAB_BIT(1),
    Keyboard = LAB_BIT(2),
    Mouse = LAB_BIT(3)
};

/**
 * @brief TODO
 */
class IEvent {
public:
    bool m_handled = false;

    virtual ~IEvent() = default;

    /**
     * @brief TODO
     */
    virtual EventType eventType() const = 0;

    /**
     * @brief TODO
     */
    virtual const char* name() const = 0;

    /**
     * @brief TODO
     */
    virtual int categoryFlags() const = 0;

    /**
     * @brief TODO
     */
    bool isInCategory(EventCategory category) const {
        return categoryFlags() & static_cast<int>(category);
    }

    /**
     * @brief TODO
     */
    template <typename T, typename F>
    bool dispatch(const F& handler) {
        if (eventType() != T::staticEventType())
            return false;

        m_handled |= handler(static_cast<T&>(*this));
        return true;
    }
};

inline std::ostream& operator<<(std::ostream& stream, const IEvent& event) {
    return stream << event.name();
}

}  // namespace labeeri::Engine
