#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

#define TEST_GROUP_ENTRIES_ALLOC 16

test_group_t
test_group_new (void)
{
    test_group_t group;

    group = (test_group_t) {0};
    if ((group.entries = malloc ((sizeof *(group.entries)) * TEST_GROUP_ENTRIES_ALLOC)) == NULL)
    {
        log_error ("failed to allocate memory\n");
        exit (EXIT_FAILURE);
    }
    group.entries[0] = NULL;
    group.entries_cap = TEST_GROUP_ENTRIES_ALLOC;

    return group;
}

void
test_group_free (test_group_t *group)
{
    free (group->entries);
}

void
test_group_add (test_group_t *group, test_entry_func_t func)
{
    if (group->entries_len == group->entries_cap - 1)
    {
        group->entries_cap += TEST_GROUP_ENTRIES_ALLOC;
        if ((group->entries = realloc (group->entries, (sizeof *(group->entries)) * group->entries_cap)) == NULL)
        {
            log_error ("failed to allocate memory\n");
            exit (EXIT_FAILURE);
        }
    }
    group->entries[group->entries_len] = func;
    group->entries_len += 1;
    group->entries[group->entries_len] = NULL;
}

test_results_t
test_group_run (test_group_t *group)
{
    test_results_t total_result, result;
    size_t i;

    total_result = (test_results_t) {0};

    for (i = 0; i < group->entries_len; i++)
    {
        result = group->entries[i]();
        total_result.success += result.success;
        total_result.failure += result.failure;
    }

    if (total_result.failure == 0)
        log_ok ("all tests successful (%zu tests in %zu sections)\n", total_result.success, group->entries_len);
    else
        log_error ("tests unsuccessful (%zu tests in %zu sections, out of which %zu successful and %zu failures)\n", total_result.success + total_result.failure, group->entries_len, total_result.success, total_result.failure);

    return total_result;
}

test_suite_t
test_suite_new (void)
{
    return (test_suite_t) {0};
}

void
test_suite_add (test_suite_t *suite, bool success, const char *assertion, const char *name, const char *file, size_t line)
{
    if (success)
        suite->results.success += 1;
    else
    {
        suite->results.failure += 1;
        log_print_fl (LOG_LEVEL_ERROR, file, line, "test '%s' (assertion '%s') failed\n", name, assertion);
    }
}

test_results_t
test_suite_get_results (test_suite_t *suite)
{
    return suite->results;
}
