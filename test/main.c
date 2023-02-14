#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cstr.h"
#define CUTILS_DEBUG_TRACE
#include "debug.h"
#include "log.h"
#include "common.h"
#include "str.h"
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

test_results_t
test_str (void)
{
    test_group_t group;
    str_t str;
    int res;
    char *s;

    group = test_group_new ();

    res = str_new (&str);
    test_add (&group, test_assert (str.str != NULL && str.cap > 0), "str_new");
    str_free (&str);

    res = str_new_cap (&str, 1000);
    test_add (&group, test_assert (str.cap == next_pow_of_two (1000)), "str_new_cap");
    str_free (&str);

    s = "Hello, World!\n";
    res = str_new_from (&str, s);
    test_add (&group, test_assert (!strcmp (str.str, s)), "str_new_from .str");
    test_add (&group, test_assert (str.len == strlen (s)), "str_new_from .len");
    test_add (&group, test_assert (str.cap >= str.len), "str_new_from .cap");
    test_add (&group, test_assert (res >= 0), "str_new_from success return value");
    str_free (&str);

    res = str_new_from (&str, NULL);
    test_add (&group, test_assert (res < 0), "str_new_from failure return value");
    if (res >= 0)
        str_free (&str);

    s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    str_new_from (&str, s);
    res = str_append (&str, s);
    test_add (&group, test_assert (!strncmp (str.str, s, strlen (s)) && !strncmp (str.str + strlen (s), s, strlen (s))), "str_append .str");
    test_add (&group, test_assert (str.len = 2 * strlen (s)), "str_append .len");
    test_add (&group, test_assert (str.cap = next_pow_of_two (2 * strlen (s))), "str_append .cap");
    test_add (&group, test_assert (res >= 0), "str_append success return value");
    res = str_append (&str, NULL);
    test_add (&group, test_assert (res < 0), "str_append failure return value");
    str_free (&str);

    return test_group_get_results (&group);
}

int
main (void)
{
    test_suite_t suite;

    suite = test_suite_new ();
    test_suite_add (&suite, test_cstr);
    test_suite_add (&suite, test_str);
    test_suite_run (&suite);
    test_suite_free (&suite);

    return EXIT_SUCCESS;
}
