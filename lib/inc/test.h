#ifndef CUTILS_TEST_H_
#define CUTILS_TEST_H_

#include "common.h"

#define test_add(group, success_and_assertion, name) test_group_add (group, success_and_assertion, name, __FILE__, __LINE__) /* add a test to a test group. source file and line will be inserted automatically. to be used with the `test_assert()` macro. */
#define test_assert(a) ((bool) (a)), (#a) /* provides the `success` and `assertion` parameters for `test_add()` / `test_group_add()` */

/* results of a test group or suite */
typedef struct {
    usize success; /* number of successful tests */
    usize failure; /* number of failed tests */
} test_results_t;

/* function signature for test group functions */
typedef test_results_t (*test_entry_func_t) (void);

/* test suite. a suite contains multiple test groups. */
typedef struct {
    test_entry_func_t *entries; /* test groups as executable function pointers */
    usize entries_len; /* number of functions */
    usize entries_cap; /* allocated space for functions */
} test_suite_t;

/* test group. contains multiple tests. */
typedef struct {
    test_results_t results;
} test_group_t;

test_suite_t test_suite_new (void); /* create a new test suite */
void test_suite_free (test_suite_t suite[static 1]); /* free dynamically allocated memory occupied by a test suite */
void test_suite_add (test_suite_t suite[static 1], test_entry_func_t func); /* add a test group function to a test suite */
test_results_t test_suite_run (test_suite_t suite[static 1]); /* run the entries within a test suite and print an informational message */
test_group_t test_group_new (void); /* create a new test group */
void test_group_add (test_group_t group[static 1], bool success, const char *assertion, const char *name, const char *file, usize line); /* add a test to a test group, print an error message if the test failed */
test_results_t test_group_get_results (test_group_t group[static 1]); /* get results of a test group. used for returning the status from a test group */

#endif // CUTILS_TEST_H_
