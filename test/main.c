#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cstr.h"
#define CUTILS_DEBUG_TRACE
#include "debug.h"
#include "log.h"

int
main (void)
{
    char *ptr;
    size_t len;

    ptr = malloc ((sizeof *ptr) * 1);
    ptr = realloc (ptr, (sizeof *ptr) * 4096);
    ptr = realloc (ptr, (sizeof *ptr) * 524288);
    free (ptr);

    log_print (LOG_LEVEL_ERROR, "error! %s\n", "string fmt");
    log_print (LOG_LEVEL_WARNING, "warning! %c\n", 'c');
    log_print (LOG_LEVEL_INFO, "info! %d\n", 42);
    log_print (LOG_LEVEL_OK, "okay! %#x\n", 69);
    log_print (LOG_LEVEL_DEBUG, "debug! %04.04f\n", 13.37);
    log_print_fl (LOG_LEVEL_OK, __FILE__, __LINE__, "file and line\n");

    char s[] = "    Hello, World!\n    ";
    len = strtrimr (s);
    assert (len == 17);
    assert (strlen (s) == 17);
    char *sn = strtriml (s);
    assert (sn == s + 4);
    assert (strlen (sn) == 13);
    char s2[] = "    Hello, World!\n    ";
    sn = strtrim (s2);
    assert (strlen (s2) == 17);
    assert (sn == s2 + 4);
    assert (strlen (sn) == 13);

    return EXIT_SUCCESS;
}
