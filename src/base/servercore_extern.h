#ifndef __HEARTBEAT_EXTERN_H__
#define __HEARTBEAT_EXTERN_H__

/* Export functions from the DLL */
#ifndef MY_SERVERCORE_EXTERN
# if defined(WIN32) || defined(_WIN32)
/* Windows - set up dll import/export decorators. */
#  if defined(MY_SERVERCORE_BUILDING_SHARED)
/* Building shared library. */
#   define MY_SERVERCORE_EXTERN __declspec(dllexport)
#  elif defined(MY_SERVERCORE_USING_SHARED)
/* Using shared library. */
#   define MY_SERVERCORE_EXTERN __declspec(dllimport)
#  else
/* Building static library. */
#    define MY_SERVERCORE_EXTERN /* nothing */
#  endif
# elif __GNUC__ >= 4
#  define MY_SERVERCORE_EXTERN __attribute__((visibility("default")))
# else
#  define MY_SERVERCORE_EXTERN /* nothing */
# endif
#endif

#endif /* __HEARTBEAT_EXTERN_H__ */