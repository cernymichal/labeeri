#pragma once

#include "Engine/Resources/Material.h"
#include "Engine/Resources/Model.h"

namespace labeeri::Engine {

namespace Shaders {
/**
 * @brief TODO
 */
const ShaderProgramRef& fallback();

/**
 * @brief TODO
 */
const ShaderProgramRef& flat();

/**
 * @brief TODO
 */
const ShaderProgramRef& phong();

};  // namespace Shaders

namespace Meshes {

/**
 * @brief TODO
 */
const MeshRef& cube();

/**
 * @brief TODO
 */
const MeshRef& sphere();

/**
 * @brief TODO
 */
const MeshRef& plane();

/**
 * @brief TODO
 */
const MeshRef& cone();
};  // namespace Meshes

/**
 * @brief TODO
 */
namespace Textures {
/**
 * @brief TODO
 */
const TextureRef& test();

};  // namespace Textures

namespace Materials {

/**
 * @brief TODO
 */
const std::shared_ptr<FlatMaterial>& flatWhite();

/**
 * @brief TODO
 */
const std::shared_ptr<ShadedMaterial>& grey();

/**
 * @brief TODO
 */
const std::shared_ptr<FlatMaterial>& UVTest();

};  // namespace Materials

namespace Models {

/**
 * @brief TODO
 */
const ModelRef& whiteCube();

/**
 * @brief TODO
 */
const ModelRef& whiteSphere();

/**
 * @brief TODO
 */
const ModelRef& whiteCone();

/**
 * @brief TODO
 */
const ModelRef& basicCube();

/**
 * @brief TODO
 */
const ModelRef& basicSphere();

/**
 * @brief TODO
 */
const ModelRef& basicPlane();

/**
 * @brief TODO
 */
const ModelRef& basicCone();

};  // namespace Models

}  // namespace labeeri::Engine
