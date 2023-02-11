#include "log.h"
#include <stdarg.h>
#include <stdio.h>

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
