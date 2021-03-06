#pragma once

#include "odbk_def.h"

#define ODBK_GET_FUN(x) x
#if ODBK_BITS == 32
#  define ODBK_GET_FUN_THUNK(x) x##__thunk
#else
#  define ODBK_GET_FUN_THUNK ODBK_GET_FUN
#endif

#define ODBK_GET_FUN_COMPACT(x) x##__compact

#define ODBK_GET_PROC_ADDR(h, x) x = reinterpret_cast<decltype(x)>(::GetProcAddress(h, #x))

enum
{
  ODBKM_INFO  = 0,
  ODBKM_WARN  = 1,
  ODBKM_ERROR = 2,
};

enum class code_state
{
  NORMAL      = 0, // The code is normal.
  UNAVAILABLE = 1, // The code for the script was not available.
  BINARY      = 2, // The code was loaded as a binary/compiled file
};

#define ODBK_LOGINFO(format, ...)                                                                  \
  do                                                                                               \
  {                                                                                                \
    auto content = odbk_sfmt((format "\r\n"), ##__VA_ARGS__);                                      \
    singleton<odbk_core>::instance()->print((int)ODBKM_INFO, content);                             \
  } while (false)

#define ODBK_LOGWARN(format, ...)                                                                  \
  do                                                                                               \
  {                                                                                                \
    auto content = odbk_sfmt((format "\r\n"), ##__VA_ARGS__);                                      \
    singleton<odbk_core>::instance()->print((int)ODBKM_WARN, content);                             \
  } while (false)

#define ODBK_LOGERR(format, ...)                                                                   \
  do                                                                                               \
  {                                                                                                \
    auto content = odbk_sfmt((format "\r\n"), ##__VA_ARGS__);                                      \
    singleton<odbk_core>::instance()->print((int)ODBKM_ERROR, content);                            \
  } while (false)

class odbk_core;
