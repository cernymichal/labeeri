#pragma once

#include "Engine/Events/IEvent.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class IEventReceiver {
public:
    /**
     * @brief TODO
     */
    virtual void onEvent(IEvent& e) = 0;
};

}  // namespace labeeri::Engine