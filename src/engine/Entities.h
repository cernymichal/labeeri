#pragma once

#include "Engine/Scene/Camera.h"
#include "Engine/Scene/Entity.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Entities {
public:
    /**
     * @brief TODO
     */
    static std::shared_ptr<Entity> Flycam(float speed = 4.0, double sensitivity = 0.002);
};

}  // namespace labeeri::Engine
