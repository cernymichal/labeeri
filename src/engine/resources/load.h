#pragma once

#include "Material.h"
#include "Model.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
ShaderProgram loadShaderProgram(const char* vertexPath, const char* fragmentPath);

/**
 * @brief TODO
 */
Mesh loadMesh(const char* filePath);

}  // namespace labeeri::engine
