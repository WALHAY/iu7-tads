#include "books.h"
#include "table.h"

int main(void)
{
    Table table;
    Book book;
    input_book(&book);
    add_entry(&table, &book);
    print_table_by_entries(&table);

    return SUCCESS;
}
