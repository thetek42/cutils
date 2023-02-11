#ifndef CUTILS_LOG_H_
#define CUTILS_LOG_H_

#include <stddef.h>

#define log_error(...) log_print (LOG_LEVEL_ERROR, __VA_ARGS__)
#define log_warn(...) log_print (LOG_LEVEL_WARN, __VA_ARGS__)
#define log_info(...) log_print (LOG_LEVEL_INFO, __VA_ARGS__)
#define log_ok(...) log_print (LOG_LEVEL_OK, __VA_ARGS__)
#define log_debug(...) log_print (LOG_LEVEL_DEBUG, __VA_ARGS__)
#define log_error_fl(...) log_print_fl (LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn_fl(...) log_print_fl (LOG_LEVEL_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_info_fl(...) log_print_fl (LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_ok_fl(...) log_print_fl (LOG_LEVEL_OK, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug_fl(...) log_print_fl (LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)

typedef enum {
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_OK,
    LOG_LEVEL_DEBUG,
} log_level_t;

__attribute__ ((format (printf, 2, 3))) void log_print (log_level_t type, const char *fmt, ...);
__attribute__ ((format (printf, 4, 5))) void log_print_fl (log_level_t type, const char *file, size_t line, const char *fmt, ...);

#endif // CUTILS_LOG_H_
