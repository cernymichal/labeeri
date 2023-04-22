#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

// STL
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

// labeeri
#include "engine/log.h"

using LAB_GL_UINT = unsigned int;  // so that we dont have to include glew everywhere
using LAB_GL_INT = int;
using LAB_GL_HANDLE = LAB_GL_UINT;
