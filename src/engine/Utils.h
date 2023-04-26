#pragma once

#include "Engine/Log.h"

#define LAB_BIT(x) (1 << x)

using LAB_GL_UINT = unsigned int;  // so that we dont have to include glew everywhere
using LAB_GL_INT = int;
using LAB_GL_HANDLE = LAB_GL_UINT;

#define LAB_APP labeeri::Engine::Application::get()
#define LAB_CURRENT_SCENE LAB_APP.scene()
#define LAB_CURRENT_CAMERA LAB_APP.camera()

namespace labeeri::Engine {

// GL 4.3 + GLSL 430
constexpr auto GL_VERSION_MAJOR = 4;
constexpr auto GL_VERSION_MINOR = 3;
constexpr auto GLSL_VERSION = "#version 430";

constexpr auto FIXED_UPDATE_INTERVAL = (1.0 / 50.0);  // 50 Hz

}  // namespace labeeri::Engine
