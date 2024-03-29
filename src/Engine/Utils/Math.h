#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_CUDA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <ostream>

constexpr double PI = glm::pi<double>();
constexpr double TWO_PI = glm::two_pi<double>();
constexpr double HALF_PI = glm::half_pi<double>();

using glm::dvec2;
using glm::dvec3;
using glm::dvec4;
using glm::ivec2;
using glm::ivec3;
using glm::ivec4;
using glm::mat2;
using glm::mat3;
using glm::mat4;
using glm::quat;
using glm::uvec2;
using glm::uvec3;
using glm::uvec4;
using glm::vec2;
using glm::vec3;
using glm::vec4;

namespace glm {

template <typename T, glm::qualifier Q>
constexpr inline T cross(const glm::vec<2, T, Q>& a, const glm::vec<2, T, Q>& b) {
    return a.x * b.y - a.y * b.x;
}

}  // namespace glm

/*
 * @param v The incoming vector
 * @param normal The normal vector
 */
constexpr inline vec3 reflect(const vec3& v, const vec3& normal) {
    return v - 2.0f * glm::dot(v, normal) * normal;
}

/*
 * @param v The incoming vector, normalized
 * @param normal The normal vector, normalized
 * @param refractionRatio The ratio of the incoming to outgoing refractive indices
 */
inline vec3 refract(const vec3& v, const vec3& normal, float refractionRatio) {
    // Snell's law
    auto cosTheta = std::min(glm::dot(-v, normal), 1.0f);
    auto outgoingPerpendicular = refractionRatio * (v + cosTheta * normal);
    auto outgoingParallel = -std::sqrt(std::abs(1.0f - glm::length2(outgoingPerpendicular))) * normal;
    return outgoingPerpendicular + outgoingParallel;
};

/*
 * @param aOrigin The origin of the first line
 * @param aDirection The direction of the first line
 * @param bOrigin The origin of the second line
 * @param bDirection The direction of the second line
 * @return The parameters t and u from the line origins along the line directions to the intersection point
 *
 * @note If the lines are parallel, the result is undefined
 */
constexpr inline vec2 lineIntersection(const vec2& aOrigin, const vec2& aDirection, const vec2& bOrigin, const vec2& bDirection) {
    // X = aOrigin + aDirection * t
    // X = bOrigin + bDirection * u

    float t = glm::cross(bOrigin - aOrigin, bDirection / glm::cross(aDirection, bDirection));
    float u = glm::cross(aOrigin - bOrigin, aDirection / glm::cross(bDirection, aDirection));
    return vec2(t, u);
}

/*
 * @param rayOrigin The origin of the ray
 * @param rayDirection The direction of the ray
 * @param vertices The vertices of the triangle
 * @return The t from the ray origin along the rayDirection the intersection point, or NAN if there is no intersection
 *
 * @note back facing triangles are not intersected
 */
constexpr inline float rayTriangleIntersection(const vec3& rayOrigin, const vec3& rayDirection, const std::array<vec3, 3>& vertices) {
    // X = rayOrigin + rayDirection * t

    // M�ller�Trumbore intersection algorithm
    auto edge1 = vertices[1] - vertices[0];
    auto edge2 = vertices[2] - vertices[0];
    auto P = glm::cross(rayDirection, edge2);
    auto determinant = glm::dot(edge1, P);

    // if the determinant is negative, the triangle is back facing
    // if the determinant is close to 0, the ray misses the triangle
    if (determinant < 0.0001f)
        return NAN;

    auto determinantInv = 1.0f / determinant;
    auto T = rayOrigin - vertices[0];
    auto u = glm::dot(T, P) * determinantInv;
    if (u < 0 || u > 1)
        return NAN;

    auto Q = glm::cross(T, edge1);
    auto v = glm::dot(rayDirection, Q) * determinantInv;
    if (v < 0 || u + v > 1)
        return NAN;

    auto t = glm::dot(edge2, Q) * determinantInv;
    if (t < 0)
        return NAN;

    return t;
}

/*
 * @param cosine The cosine of the angle between the incident ray and the normal
 * @param refractionRatio The ratio of the incoming to outgoing refractive indices
 */
inline float reflectance(float cosine, float refractionRatio) {
    // schlick's reflectance approximation
    auto r0 = (1 - refractionRatio) / (1 + refractionRatio);
    r0 *= r0;
    return r0 + (1 - r0) * static_cast<float>(std::pow((1 - cosine), 5));
}

// Comparison operators for vectors

template <int L, typename T, glm::qualifier Q>
constexpr inline glm::vec<L, bool> operator==(const glm::vec<L, T, Q>& a, const glm::vec<L, T, Q>& b) {
    return glm::equal(a, b);
}

template <int L, typename T, glm::qualifier Q>
constexpr inline glm::vec<L, bool> operator!=(const glm::vec<L, T, Q>& a, const glm::vec<L, T, Q>& b) {
    return glm::notEqual(a, b);
}

template <int L, typename T, glm::qualifier Q>
constexpr inline glm::vec<L, bool> operator>(const glm::vec<L, T, Q>& a, const glm::vec<L, T, Q>& b) {
    return glm::greaterThan(a, b);
}

template <int L, typename T, glm::qualifier Q>
constexpr inline glm::vec<L, bool> operator>=(const glm::vec<L, T, Q>& a, const glm::vec<L, T, Q>& b) {
    return glm::greaterThanEqual(a, b);
}

template <int L, typename T, glm::qualifier Q>
constexpr inline glm::vec<L, bool> operator<(const glm::vec<L, T, Q>& a, const glm::vec<L, T, Q>& b) {
    return glm::lessThan(a, b);
}

template <int L, typename T, glm::qualifier Q>
constexpr inline glm::vec<L, bool> operator<=(const glm::vec<L, T, Q>& a, const glm::vec<L, T, Q>& b) {
    return glm::lessThanEqual(a, b);
}

// Stream operators for vectors

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

// A closed interval [min, max]
template <typename T>
struct Interval {
    T min, max;

    constexpr Interval() = default;

    constexpr Interval(T min, T max) : min(min), max(max) {}

    constexpr T length() const { return max - min; }

    constexpr bool contains(T value) const { return value >= min && value <= max; }

    constexpr bool surrounds(T value) const { return value > min && value < max; }

    constexpr T clamp(T value) const { return std::max(min, std::min(max, value)); }

    static const Interval<T> empty;
    static const Interval<T> universe;
};

template <typename T>
const inline Interval<T> Interval<T>::empty = {std::numeric_limits<T>::max(), std::numeric_limits<T>::lowest()};

template <typename T>
const inline Interval<T> Interval<T>::universe = {std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max()};
