/* -*- coding: utf-8 -*-
 * ----------------------------------------------------------------------
 * Copyright © 2013, RedJack, LLC.
 * All rights reserved.
 *
 * Please see the COPYING file in this distribution for license details.
 * ----------------------------------------------------------------------
 */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include <check.h>

#include "libcork/core/types.h"
#include "libcork/ds/bloom-filter.h"

#include "helpers.h"


/*-----------------------------------------------------------------------
 * Bloom filters
 */

START_TEST(test_bloom_filter)
{
    DESCRIBE_TEST;

    struct cork_bloom_filter  *bf = cork_bloom_filter_new(8589934592, 3);

    cork_bloom_filter_insert(bf, "hello world", 11);
    fail_unless(cork_bloom_filter_contains(bf, "hello world", 11),
                "Expected \"hello world\"");

    cork_bloom_filter_insert(bf, "fizzbuzz", 8);
    fail_unless(cork_bloom_filter_contains(bf, "fizzbuzz", 8),
                "Expected \"fizzbuzz\"");

    fail_if(cork_bloom_filter_contains(bf, "world hello", 11),
            "Did not expect \"world hello\"");

    cork_bloom_filter_free(bf);
}
END_TEST


/*-----------------------------------------------------------------------
 * Testing harness
 */

Suite *
test_suite()
{
    Suite  *s = suite_create("bloom-filters");

    TCase  *tc_ds = tcase_create("bloom-filter");
    tcase_add_test(tc_ds, test_bloom_filter);
    suite_add_tcase(s, tc_ds);

    return s;
}


int
main(int argc, const char **argv)
{
    int  number_failed;
    Suite  *suite = test_suite();
    SRunner  *runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (number_failed == 0)? EXIT_SUCCESS: EXIT_FAILURE;
}
