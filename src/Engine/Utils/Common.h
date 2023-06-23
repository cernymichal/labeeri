#pragma once

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
