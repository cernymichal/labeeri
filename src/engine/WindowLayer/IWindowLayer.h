#pragma once

#include "Engine/Events/IEventReceiver.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class IWindowLayer : public IEventReceiver {
public:
    virtual ~IWindowLayer() = default;
};

}  // namespace labeeri::Engine
