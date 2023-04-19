#pragma once

#include <GL/glew.h>

#include "shaders/Material.h"
#include "shaders/Model.h"

namespace load {

ShaderProgram shaderProgram(const char* vertexPath, const char* fragmentPath);

Mesh mesh(const char* filePath);

}  // namespace load
