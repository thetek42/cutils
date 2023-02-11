#include "log.h"
#include <stdarg.h>
#include <stdio.h>

/* print the log level */
static void
_log_print_type (log_level_t type)
{
    switch (type)
    {
        case LOG_LEVEL_ERROR:
            printf ("[\e[31merror\e[0m] ");
            break;
        case LOG_LEVEL_WARNING:
            printf ("[\e[33mwarn\e[0m] ");
            break;
        case LOG_LEVEL_INFO:
            printf ("[\e[34minfo\e[0m] ");
            break;
        case LOG_LEVEL_OK:
            printf ("[\e[32mok\e[0m] ");
            break;
        case LOG_LEVEL_DEBUG:
            printf ("[\e[35mdebug\e[0m] ");
            break;
    }
}

/**
 * print a log message with given log level and format
 * 
 * @param   type: the log level (see log_level_t)
 * @param   fmt: the format to use for the output (same as printf)
 * @param   ...: format arguments
 *
 * @usage   the header "log.h" defines various additional macros: log_error,
 *          log_warn, log_info, log_ok and log_debug. the log level does not
 *          need to be passed explicitly to these.
 */
__attribute__ ((format (printf, 2, 3)))
void
log_print (log_level_t type, const char *fmt, ...)
{
    va_list ap;

    va_start (ap, fmt);
    _log_print_type (type);
    vprintf (fmt, ap);
    va_end (ap);
}

/**
 * print a log message with given log level and format, and add the filename
 * and line that it was called in
 * 
 * @param   type: the log level (see log_level_t)
 * @param   file: the file that the log function was called in
 * @param   line: the line in which the function was called
 * @param   fmt: the format to use for the output (same as printf)
 * @param   ...: format arguments
 *
 * @usage   the header "log.h" defines various additional macros: log_error_fl,
 *          log_warn_fl, log_info_fl, log_ok_fl and log_debug_fl. the log level,
 *          file name and line do not need to be passed explicitly to these.
 */
__attribute__ ((format (printf, 4, 5)))
void
log_print_fl (log_level_t type, const char *file, size_t line, const char *fmt, ...)
{
    va_list ap;

    va_start (ap, fmt);
    _log_print_type (type);
    printf ("(\e[36m%s:%zu\e[0m) ", file, line);
    vprintf (fmt, ap);
    va_end (ap);
}
