#pragma once

#include <chrono>
#include <random>

/*
 * @brief Fast pseudo random number generator by Sebastiano Vigna
 */
struct SplitMix64 {
    uint64_t state;

    /*
     * @brief Constructs a new instance.
     * @param seed Initial state.
     */
    explicit constexpr SplitMix64(uint64_t seed) : state(seed) {}

    /*
     * @brief Constructs a new instance seeded by the current time.
     */
    explicit SplitMix64() : SplitMix64(std::chrono::system_clock::now().time_since_epoch().count()) {}

    /*
     * @brief Generates a random uint64 and updates the state.
     */
    constexpr inline uint64_t operator()() {
        // https://prng.di.unimi.it/splitmix64.c

        state += 0x9e3779b97f4a7c15Ui64;

        uint64_t z = state;
        z ^= z >> 30;
        z *= 0xbf58476d1ce4e5b9Ui64;
        z ^= z >> 27;
        z *= 0x94d049bb133111ebUi64;
        z ^= z >> 31;

        return z;
    }

    static inline constexpr uint64_t min() {
        return 0;
    }

    static inline constexpr uint64_t max() {
        return uint64_t(-1);
    }
};

/*
 * @brief Very fast solid pseudo random number generator by David Blackman and Sebastiano Vigna
 *
 * https://prng.di.unimi.it/
 */
struct Xoshiro256SS {
    uint64_t state[4];

    /*
     * @brief Constructs a new instance.
     * @param seed 64b seed from which the initial state is generated using splitmix64.
     */
    explicit constexpr Xoshiro256SS(uint64_t seed) {
        SplitMix64 generator(seed);

        state[0] = generator();
        state[1] = generator();
        state[2] = generator();
        state[3] = generator();
    }

    /*
     * @brief Constructs a new instance seeded by the current time.
     */
    explicit Xoshiro256SS() : Xoshiro256SS(std::chrono::system_clock::now().time_since_epoch().count()) {}

    /*
     * @brief Generates a random uint64 and updates the state.
     */
    constexpr inline uint64_t operator()() {
        // https://prng.di.unimi.it/xoshiro256starstar.c

        uint64_t result = bitRotateLeft(state[1] * 5, 7) * 9;

        uint64_t t = state[1] << 17;
        state[2] ^= state[0];
        state[3] ^= state[1];
        state[1] ^= state[2];
        state[0] ^= state[3];
        state[2] ^= t;
        state[3] = bitRotateLeft(state[3], 45);

        return result;
    }

    static inline constexpr uint64_t min() {
        return 0;
    }

    static inline constexpr uint64_t max() {
        return uint64_t(-1);
    }

private:
    /*
     * @return value rotated by k places left.
     */
    static inline constexpr uint64_t bitRotateLeft(uint64_t value, int k) {
        return (value << k) | (value >> (64 - k));
    }
};

inline Xoshiro256SS LAB_RANDOM_GENERATOR;

/*
 * @return A random uint64.
 *
 * @note Uses LAB_RANDOM_GENERATOR internally.
 */
inline uint64_t randomUInt64() {
    return LAB_RANDOM_GENERATOR();
}

/*
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return A random int32 in the range [min, max).
 *
 * @note Uses LAB_RANDOM_GENERATOR internally.
 */
inline int32_t randomInt(int32_t min, int32_t max) {
    std::uniform_int_distribution<int32_t> distribution(min, max);
    return distribution(LAB_RANDOM_GENERATOR);
}

/*
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return A random double in the range [min, max).
 *
 * @note Uses LAB_RANDOM_GENERATOR internally.
 */
inline double randomDouble(double min, double max) {
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(LAB_RANDOM_GENERATOR);
}

/*
 * @return A random double in the range [0, 1).
 *
 * @note Uses LAB_RANDOM_GENERATOR internally.
 */
inline double randomDouble() {
    return randomDouble(0.0, 1.0);
}
