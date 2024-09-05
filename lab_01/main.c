#include "long_number.h"

int main(void)
{
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

    char *number2_str = ".321e5";
    long_number_t number2;
    if (!read_long_number(number2_str, &number2))
        print_long_number(&number2);
    return 0;
}
