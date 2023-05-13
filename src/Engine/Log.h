#pragma once

#include <sstream>

#define STR_MACRO_INNER(x) #x
#define STR_MACRO(x) STR_MACRO_INNER(x)

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

#define LAB_LOG_TO_CONSOLE

#ifdef LAB_LOG_TO_CONSOLE

#define LAB_LOG(x) std::cout << x << std::endl

#else

/**
 * @brief log message
 *
 * @param[in] x printable value
 */
#define LAB_LOG(x) labeeri::Engine::LOG_STREAM << x << std::endl

#endif

/**
 * @brief log message as a large header
 *
 * @param[in] x printable value
 */
#define LAB_LOGH1(x) LAB_LOG("\n===============================================================================\n" \
                             << "                           " << x)

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
#define LAB_LOGH3(x) LAB_LOG("- " << x)

/**
 * @brief TODO
 */
#define LAB_LOG_RENDERAPI_ERROR() LAB_DEBUG_ONLY(LAB_RENDERER->logError(__FILE__ ":" STR_MACRO(__LINE__)))

namespace labeeri::Engine {

inline std::ostringstream LOG_STREAM;

}  // namespace labeeri::Engine
