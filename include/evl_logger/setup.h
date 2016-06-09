#ifndef EVL_LOGGER_SETUP_H_
#define EVL_LOGGER_SETUP_H_


// ÷ª π”√æ≤Ã¨ø‚
#if defined(_DLL)
#define _DLL_DEFINED
#undef _DLL
#endif

#define RTQ_LIBRARY_NAME "evl_logger"
#include "third_party/utility/auto_link.h"

// ª÷∏¥
#if defined(_DLL_DEFINED)
#undef _DLL_DEFINED
#define _DLL
#endif

#endif // EVL_LOGGER_SETUP_H_
