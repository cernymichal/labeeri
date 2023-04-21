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

#ifdef LAB_LOG_TO_CONSOLE

#define LAB_LOG(x) std::cout << x << std::endl

#define LAB_LOGSTREAM_STR ""

#else

inline std::ostringstream LAB_LOGSTREAM;

/**
 * @brief log message
 *
 * @param[in] x printable value
 */
#define LAB_LOG(x) LAB_LOGSTREAM << x << std::endl

/**
 * @brief TODO
 */
#define LAB_LOGSTREAM_STR LAB_LOGSTREAM.str()

#endif

/**
 * @brief log message as a large header
 *
 * @param[in] x printable value
 */
#define LAB_LOGH1(x) LAB_LOG("\n\n" \
                             << "==================== " << x << " ====================")

/**
 * @brief log message as a header
 *
 * @param[in] x printable value
 */
#define LAB_LOGH2(x) LAB_LOG("\n" \
                             << "=> " << x)

/**
 * @brief TODO
 */
#define LAB_LOG_OGL_ERROR() LAB_DEBUG_ONLY(logOGLError(__FILE__, __LINE__))

/**
 * @brief TODO
 */
void logOGLError(const char* file, int line);
