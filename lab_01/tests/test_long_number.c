#include "test_long_number.h"
#include "assert.h"

bool equal_long_number(long_number_t number, char *mantissa, int exponent)
{
    normalize(&number);
    print_long_number(&number, false);
    return strcmp(number.mantissa, mantissa) == 0 && number.exponent == exponent;
}

void test_read_number()
{
    long_number_t number;
    printf("Empty test!\n");
    assert(read_long_number("", &number) == EMPTY_NUMBER_ERROR);
    printf("Simple test!\n");
    assert(read_long_number("123", &number) == SUCCESS);
    assert(equal_long_number(number, "123", 3));
    printf("Point test!\n");
    assert(read_long_number("123.123", &number) == SUCCESS);
    assert(equal_long_number(number, "123123", 3));
    printf("After point test!\n");
    assert(read_long_number(".123", &number) == SUCCESS);
    assert(equal_long_number(number, "123", 0));
    printf("Leading zeroes removal test!\n");
    assert(read_long_number("000123.123", &number) == SUCCESS);
    assert(equal_long_number(number, "123123", 3));
    printf("Leading zeroes removal test!\n");
    assert(read_long_number("000123123", &number) == SUCCESS);
    assert(equal_long_number(number, "123123", 6));
    printf("Leading zeroes and trailing before point removal test!\n");
    assert(read_long_number("000123123000", &number) == SUCCESS);
    assert(equal_long_number(number, "123123", 9));
    printf("Leading zeroes and trailing after point removal test!\n");
    assert(read_long_number("000123.123000", &number) == SUCCESS);
    assert(equal_long_number(number, "123123", 3));
    printf("Positive sign test!\n");
    assert(read_long_number("+000123.123000", &number) == SUCCESS);
    assert(equal_long_number(number, "123123", 3));
    printf("Negative sign test!\n");
    assert(read_long_number("-000123.123000", &number) == SUCCESS);
    assert(equal_long_number(number, "123123", 3));
    printf("Trailing zeroes removal !Overflow test!\n");
    assert(read_long_number(
               "-000123.12300000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
               &number) == SUCCESS);
    assert(equal_long_number(number, "123123", 3));
    printf("Positive sign symbol inside mantissa test!\n");
    assert(read_long_number("-000+123.123000", &number) == WRONG_SYMBOL_ERROR);
    printf("Wrong symbol inside mantissa test!\n");
    assert(read_long_number("-000c123.123000", &number) == WRONG_SYMBOL_ERROR);

    printf("Mantissa overflow handle test!\n");
    assert(
        read_long_number("-12300000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                         &number) == MANTISSA_OVERFLOW);
    // Exponent checks
    printf("Exponent test!\n");
    assert(read_long_number("-000123.123000e10", &number) == SUCCESS);
    assert(equal_long_number(number, "123123", 13));
    printf("Exponent test!\n");
    assert(read_long_number("-.123000e10", &number) == SUCCESS);
    assert(equal_long_number(number, "123", 10));
    printf("Exponent positive overflow test!\n");
    assert(read_long_number("-.123000e999999", &number) == EXPONENT_OVERFLOW);
    printf("Exponent negative overflow test!\n");
    assert(read_long_number("-.123000e-100000", &number) == EXPONENT_OVERFLOW);
}
