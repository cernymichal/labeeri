#pragma once

#define GLM_ENABLE_EXPERIMENTAL

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
 * @brief Fast inverse square root, use SSE versions instead
 *
 * @return Inverse square root of value
 */
inline constexpr float fastInvSqrt(const float value) {
    float x2 = value * 0.5f;
    float y = value;
    int32_t i = std::bit_cast<std::uint32_t>(y);  // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);                    // what the fuck?
    y = *(float*)&i;
    y = y * (1.5f - (x2 * y * y));  // 1st iteration
    y = y * (1.5f - (x2 * y * y));  // 2nd iteration, this can be removed

    return y;
}

/*
 * @brief SSE inverse square root
 *
 * @return Inverse square root of value
 */
inline float sseInvSqrt(const float value) {
    __m128 temp = _mm_set_ss(value);
    temp = _mm_rsqrt_ss(temp);
    return _mm_cvtss_f32(temp);

    // one step of NR could be added
}

/*
 * @brief SSE inverse square root
 *
 * @return Inverse square root of value
 */
inline double sseInvSqrt(const double value) {
    __m128d temp = _mm_set_sd(value);
    temp = _mm_div_sd(_mm_set_sd(1.0), _mm_sqrt_sd(temp, temp));
    return _mm_cvtsd_f64(temp);
}

/*
 * @brief Inverse of the SSE inverse square root
 *
 * @return Square root of value
 */
inline float sseSqrt(const float value) {
    return sseInvSqrt(value) * value;
}

/*
 * @brief SSE square root
 *
 * @return Square root of value
 */
inline double sseSqrt(const double value) {
    __m128d temp = _mm_set_sd(value);
    temp = _mm_sqrt_sd(temp, temp);
    return _mm_cvtsd_f64(temp);
}
