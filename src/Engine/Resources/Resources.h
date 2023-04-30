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
    static const ShaderProgramRef& fallback();

    /**
     * @brief TODO
     */
    static const ShaderProgramRef& flat();
};

/**
 * @brief TODO
 */
struct Meshes {
    /**
     * @brief TODO
     */
    static const MeshRef& cube();

    /**
     * @brief TODO
     */
    static const MeshRef& sphere();
};

/**
 * @brief TODO
 */
struct Textures {
    /**
     * @brief TODO
     */
    static const TextureRef& test();
};

/**
 * @brief TODO
 */
struct Materials {
    /**
     * @brief TODO
     */
    static const std::shared_ptr<FlatMaterial>& flatGrey();

    /**
     * @brief TODO
     */
    static const std::shared_ptr<FlatMaterial>& UVTest();
};

/**
 * @brief TODO
 */
struct Models {
    /**
     * @brief TODO
     */
    static const ModelRef& basicCube();

    /**
     * @brief TODO
     */
    static const ModelRef& basicSphere();
};

}  // namespace labeeri::Engine
