#include "books.h"

char *validate_input(char *title)
{
    char *number_str = NULL;
    size_t size = 0;
    getline(&number_str, &size, stdin);

    if (number_str == NULL)
        return IO_ERR;
}

int input_book_common();

int input_book_type();

int input_book_data();

int input_technical_book();

int input_fiction_book();

int input_children_book();
