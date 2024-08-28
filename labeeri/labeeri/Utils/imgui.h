#pragma once

#include "Utils/Math.h"

#define IMGUI_DEFINE_MATH_OPERATORS

#define IM_VEC2_CLASS_EXTRA                   \
    ImVec2(const vec2& v) : x(v.x), y(v.y) {} \
    operator vec2() const { return vec2(x, y); }

#define IM_VEC4_CLASS_EXTRA                                   \
    ImVec4(const vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {} \
    operator vec4() const { return vec4(x, y, z, w); }

#include "Utils/imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
