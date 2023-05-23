#pragma once

#include "Engine/Events/IEvent.h"

namespace labeeri::Engine {

/**
 * @brief Event receiver interface.
 */
class IEventReceiver {
public:
    virtual ~IEventReceiver() = default;

    /**
     * @brief Called when an event is received.
     *
     * @param e The event.
     */
    virtual void onEvent(IEvent& e) = 0;
};

}  // namespace labeeri::Engine