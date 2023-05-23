#pragma once

#include "Engine/Events/IEventReceiver.h"

namespace labeeri::Engine {

/**
 * @brief Window layer interface.
 */
class IWindowLayer : public IEventReceiver {
public:
    /**
     * @return Whether the window layer is enabled. (is drawn)
     */
    bool enabled() const {
        return m_enabled;
    }

protected:
    bool m_enabled = true;
};

}  // namespace labeeri::Engine
