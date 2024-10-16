#pragma once

#include <chrono>
#include <random>
#include <thread>

#include "Utils/Math.h"
#include "Utils/Scalars.h"

/*
 * @brief Fast pseudo random number generator by Sebastiano Vigna
 */
struct SplitMix64 {
    u64 state;

    /*
     * @brief Constructs a new instance.
     * @param seed Initial state.
     */
    explicit constexpr SplitMix64(u64 seed) : state(seed) {}

    /*
     * @brief Constructs a new instance seeded by the current time.
     */
    explicit SplitMix64() : SplitMix64(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) {}

    /*
     * @brief Generates a random uint64 and updates the state.
     */
    constexpr inline u64 operator()() {
        // https://prng.di.unimi.it/splitmix64.c

        state += 0x9e3779b97f4a7c15Ui64;

        u64 z = state;
        z ^= z >> 30;
        z *= 0xbf58476d1ce4e5b9Ui64;
        z ^= z >> 27;
        z *= 0x94d049bb133111ebUi64;
        z ^= z >> 31;

        return z;
    }

    static inline constexpr u64 min() {
        return 0;
    }

    static inline constexpr u64 max() {
        return u64(-1);
    }
};

/*
 * @brief Very fast solid pseudo random number generator by David Blackman and Sebastiano Vigna
 *
 * https://prng.di.unimi.it/
 */
struct Xoshiro256SS {
    u64 state[4];

    /*
     * @brief Constructs a new instance.
     * @param seed 64b seed from which the initial state is generated using splitmix64.
     */
    explicit constexpr Xoshiro256SS(u64 seed) {
        SplitMix64 generator(seed);

        state[0] = generator();
        state[1] = generator();
        state[2] = generator();
        state[3] = generator();
    }

    /*
     * @brief Constructs a new instance seeded by the current time and thread ID.
     */
    explicit Xoshiro256SS() : Xoshiro256SS(std::chrono::system_clock::now().time_since_epoch().count() + std::hash<std::thread::id>()(std::this_thread::get_id())) {}

    /*
     * @brief Generates a random uint64 and updates the state.
     */
    constexpr inline u64 operator()() {
        // https://prng.di.unimi.it/xoshiro256starstar.c

        u64 result = bitRotateLeft(state[1] * 5, 7) * 9;

        u64 t = state[1] << 17;
        state[2] ^= state[0];
        state[3] ^= state[1];
        state[1] ^= state[2];
        state[0] ^= state[3];
        state[2] ^= t;
        state[3] = bitRotateLeft(state[3], 45);

        return result;
    }

    static inline constexpr u64 min() {
        return 0;
    }

    static inline constexpr u64 max() {
        return u64(-1);
    }

private:
    /*
     * @return value rotated by k places left.
     */
    static inline constexpr u64 bitRotateLeft(u64 value, i32 k) {
        return (value << k) | (value >> (64 - k));
    }
};

inline thread_local Xoshiro256SS RANDOM_GENERATOR;

/*
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return A random T in the range [min, max).
 *
 * @note Uses RANDOM_GENERATOR internally.
 */
template <typename T>
inline T random(T min, T max) {
    if constexpr (std::is_floating_point_v<T>)
        return min + (max - min) * static_cast<T>(RANDOM_GENERATOR()) / static_cast<T>(RANDOM_GENERATOR.max());
    else
        return min + RANDOM_GENERATOR() % (max - min);
}

/*
 * @return A random value of T or a floating-point number in the range [0, 1).
 *
 * @note Uses RANDOM_GENERATOR internally.
 */
template <typename T>
inline T random() {
    if constexpr (std::is_floating_point_v<T>)
        return random<T>(0, 1);
    else if constexpr (std::is_same_v<T, bool>)
        return RANDOM_GENERATOR() & 1;
    else {
        auto value = RANDOM_GENERATOR();
        return *reinterpret_cast<T*>(&value);
    }
}

/*
 * @return A random value from a normal distribution N(0, 1).
 *
 * @note Uses RANDOM_GENERATOR internally.
 */
template <typename T>
inline T randomNormal() {
    // https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
    // faster than ratio of uniforms :( but ziggurat might be faster

    thread_local std::pair<T, bool> cache(0, false);  // {cached value, valid}
    if (cache.second) {
        cache.second = false;
        return cache.first;
    }

    f64 u1, u2;
    do {
        u1 = random<T>();
    } while (u1 == 0);
    u2 = random<T>();

    auto mag = 1 * sqrt(-2.0 * log(u1));
    auto z0 = mag * cos(TWO_PI * u2);
    auto z1 = mag * sin(TWO_PI * u2);

    cache = {z1, true};
    return z0;
}

// Random vectors

/*
 * @return A random vector with values in the range in the range [min, max).
 *
 * @note Uses RANDOM_GENERATOR internally.
 */
template <int L, typename T = f32>
inline glm::vec<L, T> randomVec(const glm::vec<L, T>& min, const glm::vec<L, T>& max) {
    glm::vec<L, T> result;
    for (i32 i = 0; i < L; i++)
        result[i] = random<T>(min[i], max[i]);

    return result;
}

/*
 * @return A random vector with values in the range in the range [0, 1).
 *
 * @note Uses RANDOM_GENERATOR internally.
 */
template <int L, typename T = f32>
inline glm::vec<L, T> randomVec() {
    return randomVec<L, T>(glm::vec<L, T>(0), glm::vec<L, T>(1));
}

/*
 * @return A random unit vec.
 *
 * @note Uses RANDOM_GENERATOR internally.
 */
template <int L, typename T = f32>
inline glm::vec<L, T> randomUnitVec() {
    while (true) {
        glm::vec<L, T> v = randomVec<L>(glm::vec<L, T>(-1), glm::vec<L, T>(1));
        if (glm::length2(v) <= 1.0)
            return glm::normalize(v);
    }
}

/*
 * @return A random vec3 on a unit sphere.
 *
 * @note Uses RANDOM_GENERATOR internally.
 */
template <>
inline glm::vec<3, f32> randomUnitVec() {
    // https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations
    vec2 u = randomVec<2>();

    f32 z = 1 - 2 * u[0];
    f32 r = std::sqrt(std::max(0.0f, 1.0f - z * z));
    f32 phi = 2 * (f32)PI * u[1];
    return vec3(r * std::cos(phi), r * std::sin(phi), z);
}

/*
 * @return A random unit vec3 on a unit hemisphere given by a normal.
 *
 * @note Uses RANDOM_GENERATOR internally.
 */
inline vec3 randomVec3OnHemisphere(const vec3& normal) {
    // https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations
    vec2 u = randomVec<2>();

    f32 z = u[0];
    f32 r = std::sqrt(std::max(0.0f, 1.0f - z * z));
    f32 phi = 2 * (f32)PI * u[1];
    return vec3(r * std::cos(phi), r * std::sin(phi), z);
}

/*
 * @return A random vec2 in a unit disk around 0.
 *
 * @note Uses RANDOM_GENERATOR internally.
 */
inline vec2 randomVec2InUnitDisk() {
    // https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations
    vec2 u = randomVec<2>();

    f32 r = std::sqrt(u[0]);
    f32 theta = 2 * (f32)PI * u[1];
    return vec2(r * std::cos(theta), r * std::sin(theta));
}

/*
 * @return A random vec2 in a unit square stratified, liearly after each other.
 *
 * @note Uses RANDOM_GENERATOR internally.
 */
inline vec2 randomVec2Stratified(u32 strataCountPerAxis, u32 strataIndex) {
    vec2 offset = vec2(strataIndex % strataCountPerAxis, (strataIndex / strataCountPerAxis) % strataCountPerAxis);
    return (randomVec<2>() + offset) / (f32)strataCountPerAxis;
}
