#pragma once

#include <sstream>

inline std::ostringstream LAB_LOG_STREAM;

#ifdef LAB_DEBUG

/**
 * @brief Log value
 *
 * @param x Printable value
 */
#define LAB_LOG(x)               \
    std::cout << x << std::endl; \
    LAB_LOG_STREAM << x << std::endl

#else

/**
 * @brief Log value
 *
 * @param x Printable value
 */
#define LAB_LOG(x) LAB_LOG_STREAM << x << std::endl

#endif

/**
 * @brief Log value as a large header
 *
 * @param x Printable value
 */
#define LAB_LOGH1(x) LAB_LOG("\n===============================================================================\n" \
                             << "                           " << x)

/**
 * @brief Log value as a header
 *
 * @param x Printable value
 */
#define LAB_LOGH2(x) LAB_LOG("\n" \
                             << "=> " << x)

/**
 * @brief Log value as a small header
 *
 * @param x Printable value
 */
#define LAB_LOGH3(x) LAB_LOG("- " << x)
