#include "defines.h"
#include "long_number.h"
#include "tests/test_long_number.h"
#include "utils.h"

int main(void)
{
#ifdef TEST
    test_read_number();
    return SUCCESS;
#endif
    int rc = SUCCESS;
    long_number_t first;
    long_number_t second;
    do
    {
        printf("Enter first number: ");
        rc = read_number_wrapper(&first);
        if (rc)
            print_err(rc);
    } while (rc);

    do
    {
        printf("Enter second number: ");
        rc = read_number_wrapper(&second);
        if (rc)
            print_err(rc);
    } while (rc);

    normalize(&first);
    normalize(&second);
    print_long_number(&first, false);
    print_long_number(&second, false);

    rc = divide(&first, &second);
    if (!rc)
    {
        printf("Division result:\n");
        print_long_number(&first, true);
    }
    else
        print_err(rc);
    return rc;
}
