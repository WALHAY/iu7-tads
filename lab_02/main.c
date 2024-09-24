#include "books.h"
#include "table.h"

int main(void)
{
    Book book;
    input_book(&book);
    print_table_entry(&book);
    return SUCCESS;
}
