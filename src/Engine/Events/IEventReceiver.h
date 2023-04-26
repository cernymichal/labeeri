#pragma once

#include "Engine/Events/Event.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class IEventReceiver {
public:
    /**
     * @brief TODO
     */
    virtual void onEvent(Event& e) = 0;
};

}  // namespace labeeri::Engine