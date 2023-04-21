#pragma once

#include "../engine.h"

namespace labeeri {

/**
 * @brief TODO
 */
struct LoadedScene {
    std::shared_ptr<engine::Scene> scene;
    std::shared_ptr<engine::Camera> camera;
};

/**
 * @brief TODO
 */
LoadedScene defaultScene();

}  // namespace labeeri
