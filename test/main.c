#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cstr.h"
#define CUTILS_DEBUG_TRACE
#include "debug.h"
#include "log.h"
#include "test.h"

test_results_t
test_cstr (void)
{
    test_group_t group;
    size_t len;

    group = test_group_new ();

    char s[] = "    Hello, World!\n    ";
    len = strtrimr (s);
    test_add (&group, test_assert (len == 17), "strtrimr return value");
    test_add (&group, test_assert (strlen (s) == 17), "strtrimr length");
    char *sn = strtriml (s);
    test_add (&group, test_assert (sn == s + 4), "strtriml pointer");
    test_add (&group, test_assert (strlen (sn) == 13), "strtriml length");
    char s2[] = "    Hello, World!\n    ";
    sn = strtrim (s2);
    test_add (&group, test_assert (sn == s2 + 4), "strtrim pointer");
    test_add (&group, test_assert (strlen (s2) == 17), "strtrim original pointer length");
    test_add (&group, test_assert (strlen (sn) == 13), "strtrim new pointer length");

    char *s3 = "Hello, World!\n";
    test_add (&group, test_assert (strcount (s3, 'l') == 3), "strcount multiple occurances");
    test_add (&group, test_assert (strcount (s3, '\n') == 1), "strcount one occurance");
    test_add (&group, test_assert (strcount (s3, 'X') == 0), "strcount no occurance");

    char s4[] = "Hello, World!\n";
    char s5[] = "Hello, World!\n";
    strdowncase (s4);
    strupcase (s5);
    test_add (&group, test_assert (!strcmp (s4, "hello, world!\n")), "strdowncase");
    test_add (&group, test_assert (!strcmp (s5, "HELLO, WORLD!\n")), "strupcase");
    
    char *s6 = "    x    ";
    char *s7 = " \r\n\t\v\f";
    test_add (&group, test_assert (!strisblank (s6)), "strisblank false");
    test_add (&group, test_assert (strisblank (s7)), "strisblank true");

    return test_group_get_results (&group);
}

int
main (void)
{
    test_suite_t suite;

    suite = test_suite_new ();
    test_suite_add (&suite, test_cstr);
    test_suite_run (&suite);
    test_suite_free (&suite);

    return EXIT_SUCCESS;
}
