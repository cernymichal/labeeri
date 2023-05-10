#pragma once

#include "Engine/Resources/Material.h"
#include "Engine/Resources/Model.h"

namespace labeeri::Engine {

namespace Shaders {
/**
 * @brief TODO
 */
const Ref<ShaderProgram>& fallback();

/**
 * @brief TODO
 */
const Ref<ShaderProgram>& flat();

/**
 * @brief TODO
 */
const Ref<ShaderProgram>& phong();

};  // namespace Shaders

namespace Meshes {

/**
 * @brief TODO
 */
const Ref<Mesh>& cube();

/**
 * @brief TODO
 */
const Ref<Mesh>& sphere();

/**
 * @brief TODO
 */
const Ref<Mesh>& plane();

/**
 * @brief TODO
 */
const Ref<Mesh>& cone();
};  // namespace Meshes

/**
 * @brief TODO
 */
namespace Textures {
/**
 * @brief TODO
 */
const Ref<Texture>& test();

};  // namespace Textures

namespace Materials {

/**
 * @brief TODO
 */
const Ref<FlatMaterial>& flatWhite();

/**
 * @brief TODO
 */
const Ref<ShadedMaterial>& grey();

/**
 * @brief TODO
 */
const Ref<FlatMaterial>& UVTest();

};  // namespace Materials

namespace Models {

/**
 * @brief TODO
 */
const Ref<Model>& whiteCube();

/**
 * @brief TODO
 */
const Ref<Model>& whiteSphere();

/**
 * @brief TODO
 */
const Ref<Model>& whiteCone();

/**
 * @brief TODO
 */
const Ref<Model>& basicCube();

/**
 * @brief TODO
 */
const Ref<Model>& basicSphere();

/**
 * @brief TODO
 */
const Ref<Model>& basicPlane();

/**
 * @brief TODO
 */
const Ref<Model>& basicCone();

};  // namespace Models

}  // namespace labeeri::Engine
