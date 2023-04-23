#pragma once

#include "scene/Camera.h"
#include "scene/Entity.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
class Entities {
public:
    /**
     * @brief TODO
     */
    static std::shared_ptr<Entity> Flycam(float speed = 1.0);
};

}  // namespace labeeri::engine
