#pragma once

/*
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return A random double in the range [min, max).
 */
static double randomDouble(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

/*
 * @return A random double in the range [0, 1).
 */
static double randomDouble() {
    return randomDouble(0.0, 1.0);
}
