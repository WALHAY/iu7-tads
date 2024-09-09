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

    divide(&number, &number2);
    printf("Result after division: ");
    print_long_number(&number);

    char *number_str3 = "-1632.1234e101";
    long_number_t number3;
    if (!read_long_number(number_str3, &number3))
        print_long_number(&number3);

    char *number_str4 = "-3264.2468e-5";
    long_number_t number4;
    if (!read_long_number(number_str4, &number4))
        print_long_number(&number4);

    normalize(&number3);
    normalize(&number4);

    divide(&number3, &number4);
    printf("Result after division: ");
    print_long_number(&number3);
    return 0;
}
