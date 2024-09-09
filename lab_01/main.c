#include "defines.h"
#include "long_number.h"
#include "utils.h"

int main(void)
{
    int rc = SUCCESS;
    long_number_t first;
    printf("Enter first number: ");
    rc = read_number_wrapper(&first);

    if (rc)
        return rc;

    long_number_t second;
    printf("Enter second number: ");
    rc = read_number_wrapper(&second);

    if (rc)
        return rc;

    rc = divide(&first, &second);
    printf("Result:\n");
    print_long_number(&first);
    print_len_line(2, 40);
    return rc;
}
