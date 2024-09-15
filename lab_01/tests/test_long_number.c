#include "test_long_number.h"
#include "assert.h"

bool equal_long_number(long_number_t *number, char *mantissa, int exponent)
{
    normalize(number);
    return strcmp(number->mantissa, mantissa) == 0 && number->exponent == exponent;
}

void test_read_number()
{
    long_number_t number;
    bool rc = !read_long_number("123", &number) && equal_long_number(&number, "123", 3);
    print_long_number(&number, 0);
    assert(rc);
    rc = !read_long_number("123.123", &number) && equal_long_number(&number, "123123", 3);
    print_long_number(&number, 0);
    assert(rc);
    // assert(!read_long_number("123.123e123", &number) && equal_long_number(&number, "123", 126));
    // print_long_number(&number, 0);
    // assert(!read_long_number(".123", &number) && equal_long_number(&number, "123", 0));
    // print_long_number(&number, 0);
    // assert(!read_long_number("0.1", &number) && equal_long_number(&number, "1", 0));
    // print_long_number(&number, 0);
    // assert(!read_long_number("0000123.1230000", &number) && equal_long_number(&number, "123123", 3));
    // print_long_number(&number, 0);
    // assert(!read_long_number("123000.000123", &number) && equal_long_number(&number, "123000000123", 6));
    // print_long_number(&number, 0);
}
