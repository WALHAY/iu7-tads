#include "defines.h"
#include "long_number.h"

int main(void)
{
    char *number_str = "-534534.136445e101";
    long_number_t number;
    if (!read_long_number(number_str, &number))
        print_long_number(&number);

    char *number2_str = "-1632.1234e-5";
    long_number_t number2;
    if (!read_long_number(number2_str, &number2))
        print_long_number(&number2);

    normalize(&number);
    normalize(&number2);

    printf("Is less %d\n", is_less_divider(number.mantissa, number2.mantissa, 0));

    divide(&number, &number2);
    printf("Result after division: ");
    print_long_number(&number);
    return 0;
}
