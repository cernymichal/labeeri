#pragma once

#include "Engine/Resources/Material.h"
#include "Engine/Resources/Model.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
ShaderProgramRef loadShaderProgram(const char* vertexPath, const char* fragmentPath);

/**
 * @brief TODO
 */
MeshRef loadMesh(const char* filePath);

/**
 * @brief TODO
 */
TextureRef loadTexture(const char* filePath);

}  // namespace labeeri::Engine
