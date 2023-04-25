#ifndef CUTILS_LOG_H_
#define CUTILS_LOG_H_

#include <stddef.h>
#include <stdlib.h>

#define log_error(...) log_print (LOG_LEVEL_ERROR, __VA_ARGS__) /* print a log message with level error */
#define log_warn(...) log_print (LOG_LEVEL_WARN, __VA_ARGS__) /* print a log message with level warning */
#define log_info(...) log_print (LOG_LEVEL_INFO, __VA_ARGS__) /* print a log message with level info */
#define log_ok(...) log_print (LOG_LEVEL_OK, __VA_ARGS__) /* print a log message with level ok */
#define log_debug(...) log_print (LOG_LEVEL_DEBUG, __VA_ARGS__) /* print a log message with level debug */
#define log_error_fl(...) log_print_fl (LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__) /* print a log message with the current file and line and log level error */
#define log_warn_fl(...) log_print_fl (LOG_LEVEL_WARN, __FILE__, __LINE__, __VA_ARGS__) /* print a log message with the current file and line and log level warning */
#define log_info_fl(...) log_print_fl (LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__) /* print a log message with the current file and line and log level info */
#define log_ok_fl(...) log_print_fl (LOG_LEVEL_OK, __FILE__, __LINE__, __VA_ARGS__) /* print a log message with the current file and line and log level ok */
#define log_debug_fl(...) log_print_fl (LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__) /* print a log message with the current file and line and log level debug */
#define log_fatal(...) do { log_print (LOG_LEVEL_ERROR, __VA_ARGS__); exit (EXIT_FAILURE); } while (0) /* print a log message with level error and exit */
#define log_fatal_fl(...) do { log_print_fl (LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__) exit (EXIT_FAILURE); } while (0) /* print a log message with the current file and line and log level error and exit */

typedef enum {
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_OK,
    LOG_LEVEL_DEBUG,
} log_level_t;

__attribute__ ((format (printf, 2, 3))) void log_print (log_level_t type, const char *fmt, ...); /* print a log message with given log level and format */
__attribute__ ((format (printf, 4, 5))) void log_print_fl (log_level_t type, const char *file, size_t line, const char *fmt, ...); /* print a log message with given log level and format, and add the filename and line that it was called in */

#endif // CUTILS_LOG_H_
