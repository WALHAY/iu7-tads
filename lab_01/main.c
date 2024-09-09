#include "defines.h"
#include "long_number.h"

#ifdef TEST
void test_normalize()
{
    long_number_t ln = {false, "0000123", 10, 2};
    print_long_number(&ln);
    normalize(&ln);
    printf("After normalization: ");
    print_long_number(&ln);
}

void test_is_less_mantissa()
{
    long_number_t ln = {false, "112", 321, 0};
    long_number_t ln2 = {false, "11", 321, 0};
    printf("Is less? %s\n", is_less_mantissa(&ln, &ln2) ? "Less" : "Bigger");
    printf("---------------\n");
}

void test_subtract_mantissa()
{
    long_number_t ln = {false, "2130", 321, 0};
    print_long_number(&ln);
    printf("-\n");
    long_number_t ln2 = {false, "10", 321, 0};
    print_long_number(&ln2);
    subtract_mantissa(&ln, &ln2);
    printf("Result: ");
    print_long_number(&ln);
    printf("---------------\n");
    long_number_t ln3 = {false, "2130", 321, 0};
    print_long_number(&ln);
    printf("-\n");
    long_number_t ln4 = {false, "20", 321, 0};
    print_long_number(&ln3);
    subtract_mantissa(&ln3, &ln4);
    printf("Result: ");
    print_long_number(&ln3);
    printf("---------------\n");
}
#endif

int main(void)
{
#ifdef TEST
    test_normalize();
    test_is_less_mantissa();
    test_subtract_mantissa();
#endif
    // // equal to 123.43e321
    // long_number_t ln = {false, "12343", 321, 3};
    // normalize(&ln);
    // print_long_number(&ln);

    // // equal to 0.12343e10
    // long_number_t ln2 = {false, "00012343", 10, 3};
    // normalize(&ln2);
    // print_long_number(&ln2);
    char *number_str = "123.321e101";
    long_number_t number;
    if (!read_long_number(number_str, &number))
        print_long_number(&number);

    char *number2_str = ".123e5";
    long_number_t number2;
    if (!read_long_number(number2_str, &number2))
        print_long_number(&number2);

    normalize(&number);
    normalize(&number2);

    char mantissa[MAX_MANTISSA_SIZE] = "123321";
    subtract_divider(mantissa, "123", 3);
    printf("New mantissa %s\n", mantissa);

    long_number_t *result;
    printf("Result after division: ");
    print_long_number(&number);
    return 0;
}
