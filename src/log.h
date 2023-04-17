#pragma once

#include <sstream>

#ifdef LAB_DEBUG

#define LAB_DEBUG_ONLY(x) x

#else

/**
 * @brief execute only in debug mode
 *
 * @param[in] x expression to execute
 */
#define LAB_DEBUG_ONLY(x)

#endif

inline std::ostringstream LAB_LOGSTREAM;

/**
 * @brief log message
 *
 * @param[in] x printable value
 */
#define LAB_LOG(x) LAB_LOGSTREAM << x << std::endl

/**
 * @brief log message as a large header
 *
 * @param[in] x printable value
 */
#define LAB_LOGH1(x) LAB_LOGSTREAM << "\n\n" \
                                   << "==================== " << x << " ====================" << std::endl

/**
 * @brief log message as a header
 *
 * @param[in] x printable value
 */
#define LAB_LOGH2(x) LAB_LOGSTREAM << "\n" \
                                   << "=> " << x << std::endl
