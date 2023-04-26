#pragma once

#include "Engine/Resources/Material.h"
#include "Engine/Resources/Model.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
struct Shaders {
    /**
     * @brief TODO
     */
    static const std::shared_ptr<ShaderProgram>& basic();
};

/**
 * @brief TODO
 */
struct Materials {
    /**
     * @brief TODO
     */
    static const std::shared_ptr<Material>& basic();
};

/**
 * @brief TODO
 */
struct Meshes {
    /**
     * @brief TODO
     */
    static const std::shared_ptr<Mesh>& cube();

    /**
     * @brief TODO
     */
    static const std::shared_ptr<Mesh>& sphere();
};

/**
 * @brief TODO
 */
struct Models {
    /**
     * @brief TODO
     */
    static const std::shared_ptr<Model>& basicCube();

    /**
     * @brief TODO
     */
    static const std::shared_ptr<Model>& basicSphere();
};

}  // namespace labeeri::Engine
