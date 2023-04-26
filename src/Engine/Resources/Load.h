#pragma once

#include "Engine/Resources/Material.h"
#include "Engine/Resources/Model.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
ShaderProgram loadShaderProgram(const char* vertexPath, const char* fragmentPath);

/**
 * @brief TODO
 */
Mesh loadMesh(const char* filePath);

}  // namespace labeeri::Engine
