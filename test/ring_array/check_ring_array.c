#include <cc_ring_array.h>

#include <check.h>

#include <stdlib.h>
#include <stdio.h>

#define SUITE_NAME "ring_array"
#define DEBUG_LOG  SUITE_NAME ".log"

/*
 * utilities
 */
static void
test_setup(void)
{
}

static void
test_teardown(void)
{
}

static void
test_reset(void)
{
    test_setup();
    test_teardown();
}

START_TEST(test_create_push_pop_destroy)
{
#define ELEM_SIZE sizeof(uint8_t)
#define CAP 10
#define ELEM_VALUE 1
    struct ring_array *arr;
    uint8_t elem[1], test_elem[1];

    test_reset();
    *elem = ELEM_VALUE;
    *test_elem = ELEM_VALUE + 1; /* make sure it is not equal to ELEM_VALUE */

    arr = ring_array_create(ELEM_SIZE, CAP);
    ck_assert_int_eq(ring_array_push(elem, arr), CC_OK);
    ck_assert_int_eq(ring_array_pop(test_elem, arr), CC_OK);

    ck_assert_int_eq(*test_elem, ELEM_VALUE);

    ring_array_destroy(arr);
#undef ELEM_SIZE
#undef CAP
}
END_TEST

START_TEST(test_pop_empty)
{
#define ELEM_SIZE sizeof(uint8_t)
#define CAP 10
    struct ring_array *arr;

    test_reset();

    arr = ring_array_create(ELEM_SIZE, CAP);
    ck_assert_int_eq(ring_array_pop(NULL, arr), CC_ERROR);

    ring_array_destroy(arr);
#undef ELEM_SIZE
#undef CAP
}
END_TEST

/*
 * test suite
 */
static Suite *
ring_array_suite(void)
{
    Suite *s = suite_create(SUITE_NAME);

    TCase *tc_ring_array = tcase_create("cc_ring_array test");
    suite_add_tcase(s, tc_ring_array);

    tcase_add_test(tc_ring_array, test_create_push_pop_destroy);
    tcase_add_test(tc_ring_array, test_pop_empty);

    return s;
}
/**************
 * test cases *
 **************/

int
main(void)
{
    int nfail;

    /* setup */
    test_setup();

    Suite *suite = ring_array_suite();
    SRunner *srunner = srunner_create(suite);
    srunner_set_log(srunner, DEBUG_LOG);
    srunner_run_all(srunner, CK_ENV); /* set CK_VEBOSITY in ENV to customize */
    nfail = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    /* teardown */
    test_teardown();

    return (nfail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
