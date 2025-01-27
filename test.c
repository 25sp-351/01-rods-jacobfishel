// test.c
#include <stdlib.h>
#include "munit.h"
#include "functions.h"

// Test calculate_rod_price with valid input
static MunitResult
test_calculate_rod_price(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    float rod_length = 5.0;
    int size_of_array = 3;

    // Allocate and set input array
    float** length_and_value = malloc(size_of_array * sizeof(float*));
    for (int i = 0; i < size_of_array; i++) {
        length_and_value[i] = malloc(2 * sizeof(float));
    }

    length_and_value[0][0] = 1.0;
    length_and_value[0][1] = 10.0;
    length_and_value[1][0] = 2.0;
    length_and_value[1][1] = 20.0;
    length_and_value[2][0] = 3.0;
    length_and_value[2][1] = 30.0;

    float result = calculate_rod_price(rod_length, length_and_value, size_of_array, 0);
    munit_assert_double(result, ==, 50.0);  // Use munit_assert_double instead

    for (int i = 0; i < size_of_array; i++) {
        free(length_and_value[i]);
    }
    free(length_and_value);

    return MUNIT_OK;
}

// Test calculate_rod_price with empty input
static MunitResult
test_calculate_rod_price_empty(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;

    float rod_length = 5.0;
    int size_of_array = 0;
    float** length_and_value = NULL;

    float result = calculate_rod_price(rod_length, length_and_value, size_of_array, 0);
    munit_assert_double(result, ==, 0.0);  // Use munit_assert_double instead

    return MUNIT_OK;
}

// Test suite
static MunitTest tests[] = {
    { "/test_calculate_rod_price", test_calculate_rod_price, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_calculate_rod_price_empty", test_calculate_rod_price_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

// Test suite configuration
static const MunitSuite suite = {
    "/test_suite",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

// Main entry point for test runner
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
