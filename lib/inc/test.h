#ifndef CUTILS_TEST_H_
#define CUTILS_TEST_H_

#include <stdbool.h>
#include <stddef.h>

#define test_add(suite, success_and_assertion, name) test_suite_add (suite, success_and_assertion, name, __FILE__, __LINE__)
#define test_assert_op(a, op, b) ((a) op (b)), (#a " " #op " " #b)
#define test_assert(a) ((bool) a), (#a)

typedef struct
{
    size_t success;
    size_t failure;
} test_results_t;

typedef test_results_t (*test_entry_func_t) (void);

typedef struct
{
    test_entry_func_t *entries;
    size_t entries_len;
    size_t entries_cap;
} test_group_t;

typedef struct
{
    test_results_t results;
} test_suite_t;

test_group_t test_group_new (void);
void test_group_free (test_group_t *group);
void test_group_add (test_group_t *group, test_entry_func_t func);
test_results_t test_group_run (test_group_t *group);
test_suite_t test_suite_new (void);
void test_suite_add (test_suite_t *suite, bool success, const char *assertion, const char *name, const char *file, size_t line);
test_results_t test_suite_get_results (test_suite_t *suite);

#endif // CUTILS_TEST_H_
