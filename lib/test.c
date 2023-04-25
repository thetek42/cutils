#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "log.h"

#define TEST_GROUP_ENTRIES_ALLOC 16

/**
 * create a new test suite.
 *
 * @return  test suite struct instance, with space allocated for adding test
 *          group functions.
 */
test_suite_t
test_suite_new (void)
{
    test_suite_t suite;

    suite = (test_suite_t) {0};
    suite.entries = smalloc ((sizeof *(suite.entries)) * TEST_GROUP_ENTRIES_ALLOC);
    suite.entries[0] = NULL;
    suite.entries_cap = TEST_GROUP_ENTRIES_ALLOC;

    return suite;
}

/**
 * free dynamically allocated memory occupied by a test suite
 *
 * @param   suite: a pointer to the suite to free up
 */
void
test_suite_free (test_suite_t suite[static 1])
{
    free (suite->entries);
}

/**
 * add a test group function to a test suite.
 *
 * @param   suite: the suite to add the test group function to
 * @param   func: the test group function
 */
void
test_suite_add (test_suite_t suite[static 1], test_entry_func_t func)
{
    if (suite->entries_len == suite->entries_cap - 1)
    {
        suite->entries_cap += TEST_GROUP_ENTRIES_ALLOC;
        suite->entries = realloc (suite->entries, (sizeof *(suite->entries)) * suite->entries_cap);
    }
    suite->entries[suite->entries_len] = func;
    suite->entries_len += 1;
    suite->entries[suite->entries_len] = NULL;
}

/**
 * run the entries within a test suite and print a message informing the user
 * about the number of passed or failed tests.
 *
 * @param   suite: the suite to run
 *
 * @return  test results (number of successful and failed tests)
 */
test_results_t
test_suite_run (test_suite_t suite[static 1])
{
    test_results_t total_result, result;
    size_t i;

    total_result = (test_results_t) {0};

    for (i = 0; i < suite->entries_len; i++)
    {
        result = suite->entries[i]();
        total_result.success += result.success;
        total_result.failure += result.failure;
    }

    if (total_result.failure == 0)
        log_ok ("all tests successful (%zu tests in %zu groups)\n", total_result.success, suite->entries_len);
    else
        log_error ("tests unsuccessful (%zu tests in %zu groups, out of which %zu successful and %zu failures)\n", total_result.success + total_result.failure, suite->entries_len, total_result.success, total_result.failure);

    return total_result;
}

/**
 * create a new test group.
 *
 * @return  a test group struct instance
 */
test_group_t
test_group_new (void)
{
    return (test_group_t) {0};
}

/**
 * add a test to a test group, update its status and print an error message if
 * the test failed.
 *
 * @param   group: the test group to add the test to
 * @param   success: wheter the assertion was successful
 * @param   assertion: a string containing the assertion expression
 * @param   file: the file in which the test was added
 * @param   line: the source code line where the test was added
 *
 * @usage   the header file `test.h` defines various macros for using this
 *          function. file name and line will be inserted automatically, and
 *          assertion macros may be used to fill in the `success` and
 *          `assertion` parameters.
 */
void
test_group_add (test_group_t group[static 1], bool success, const char *assertion, const char *name, const char *file, size_t line)
{
    if (success)
        group->results.success += 1;
    else
    {
        group->results.failure += 1;
        log_print_fl (LOG_LEVEL_ERROR, file, line, "test '%s' (assertion '%s') failed\n", name, assertion);
    }
}

/**
 * get results of a test group. used for returning the status from a test group
 * function.
 *
 * @param   group: the group to query
 */
test_results_t
test_group_get_results (test_group_t group[static 1])
{
    return group->results;
}
