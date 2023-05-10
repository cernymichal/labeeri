#pragma once

#include "Engine/Resources/Material.h"
#include "Engine/Resources/Model.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
Ref<ShaderProgram> loadShaderProgram(const char* vertexPath, const char* fragmentPath);

/**
 * @brief TODO
 */
Ref<Mesh> loadMesh(const char* filePath);

/**
 * @brief TODO
 */
Ref<Texture> loadTexture(const char* filePath);

}  // namespace labeeri::Engine
