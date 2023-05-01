#pragma once

#include "Engine/Events/IEventReceiver.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class IWindowLayer : public IEventReceiver {
public:
    virtual ~IWindowLayer() = default;

    /**
     * @brief TODO
     */
    bool enabled() const {
        return m_enabled;
    }

protected:
    bool m_enabled = true;
};

}  // namespace labeeri::Engine
