#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <ostream>

using vec2 = glm::vec2;
using dvec2 = glm::dvec2;
using ivec2 = glm::ivec2;
using uvec2 = glm::uvec2;
using vec3 = glm::vec3;
using dvec3 = glm::dvec3;
using ivec3 = glm::ivec3;
using uvec3 = glm::uvec3;
using vec4 = glm::vec4;
using dvec4 = glm::dvec4;
using ivec4 = glm::ivec4;
using uvec4 = glm::uvec4;
using mat2 = glm::mat2;
using mat3 = glm::mat3;
using mat4 = glm::mat4;
using quat = glm::quat;

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const glm::vec<2, T>& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const glm::vec<3, T>& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const glm::vec<4, T>& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}

/*
*  @brief The legendary fast inverse square root
 * @return Inverse square root of value
*/
float invSqrt(float value) {
    float x2 = value * 0.5f;
    float y = value;
    int32_t i = *(int32_t*)&y;  // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);  // what the fuck?
    y = *(float*)&i;
    y = y * (1.5f - (x2 * y * y));  // 1st iteration
    // y = y * (1.5f - (x2 * y * y));  // 2nd iteration, this can be removed

    return y;
}
