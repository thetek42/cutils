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
    usize len;

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
    char *s;

    group = test_group_new ();

    str = str_new ();
    test_add (&group, test_assert (str.str != nullptr && str.cap > 0), "str_new");
    str_free (&str);

    str = str_new_cap (1000);
    test_add (&group, test_assert (str.cap == next_pow_of_two (1000)), "str_new_cap");
    str_free (&str);

    s = "Hello, World!\n";
    str = str_new_from (s);
    test_add (&group, test_assert (!strcmp (str.str, s)), "str_new_from .str");
    test_add (&group, test_assert (str.len == strlen (s)), "str_new_from .len");
    test_add (&group, test_assert (str.cap >= str.len), "str_new_from .cap");
    str_free (&str);

    s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    str = str_new_from (s);
    str_append (&str, s);
    test_add (&group, test_assert (!strncmp (str.str, s, strlen (s)) && !strncmp (str.str + strlen (s), s, strlen (s))), "str_append .str");
    test_add (&group, test_assert (str.len = 2 * strlen (s)), "str_append .len");
    test_add (&group, test_assert (str.cap = next_pow_of_two (2 * strlen (s))), "str_append .cap");
    str_free (&str);

    str = str_new_from (s);
    test_add (&group, test_assert (str_eq (&str, s)), "str_eq true");
    test_add (&group, test_assert (!str_eq (&str, "foo")), "str_eq false");
    test_add (&group, test_assert (str_cmp (&str, "A") > 0), "str_eq greater");
    test_add (&group, test_assert (str_cmp (&str, s) == 0), "str_eq equal");
    test_add (&group, test_assert (str_cmp (&str, "Z") < 0), "str_eq less");

    test_add (&group, test_assert (str_starts_with (&str, "Lorem")), "str_starts_with true");
    test_add (&group, test_assert (!str_starts_with (&str, "foo")), "str_starts_with false");
    test_add (&group, test_assert (str_ends_with (&str, "elit.")), "str_ends_with true");
    test_add (&group, test_assert (!str_ends_with (&str, "bar")), "str_ends_with false");

    test_add (&group, test_assert (str_find (&str, "ipsum") == str.str + 6), "str_find success");
    test_add (&group, test_assert (str_find (&str, "foo") == nullptr), "str_find failure");
    test_add (&group, test_assert (str_pos (&str, "ipsum") == 6), "str_pos success");
    test_add (&group, test_assert (str_pos (&str, "foo") == -1), "str_pos failure");
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
