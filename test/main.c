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
    test_suite_t suite;
    size_t len;

    suite = test_suite_new ();

    char s[] = "    Hello, World!\n    ";
    len = strtrimr (s);
    test_add (&suite, test_assert_op (len, ==, 17), "strtrimr return value");
    test_add (&suite, test_assert_op (strlen (s), ==, 17), "strtrimr length");
    char *sn = strtriml (s);
    test_add (&suite, test_assert_op (sn, ==, s + 4), "strtriml pointer");
    test_add (&suite, test_assert_op (strlen (sn), ==, 13), "strtriml length");
    char s2[] = "    Hello, World!\n    ";
    sn = strtrim (s2);
    test_add (&suite, test_assert_op (sn, ==, s2 + 4), "strtrim pointer");
    test_add (&suite, test_assert_op (strlen (s2), ==, 17), "strtrim original pointer length");
    test_add (&suite, test_assert_op (strlen (sn), ==, 13), "strtrim new pointer length");

    char *s3 = "Hello, World!\n";
    test_add (&suite, test_assert_op (strcount (s3, 'l'), ==, 3), "strcount multiple occurances");
    test_add (&suite, test_assert_op (strcount (s3, '\n'), ==, 1), "strcount one occurance");
    test_add (&suite, test_assert_op (strcount (s3, 'X'), ==, 0), "strcount no occurance");
    
    return test_suite_get_results (&suite);
}

int
main (void)
{
    test_group_t group;

    group = test_group_new ();
    test_group_add (&group, test_cstr);
    test_group_run (&group);
    test_group_free (&group);

    return EXIT_SUCCESS;
}
