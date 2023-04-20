#pragma once

#include <GL/glew.h>

#include "Material.h"
#include "Model.h"

/**
 * @brief TODO
 */
ShaderProgram loadShaderProgram(const char* vertexPath, const char* fragmentPath);

/**
 * @brief TODO
 */
Mesh loadMesh(const char* filePath);
