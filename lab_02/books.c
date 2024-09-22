#include "books.h"

int validate_input(char *field, char *title, size_t max_size)
{
    int rc = SUCCESS;

    char *temp = NULL;
    size_t size = 0;
    getline(&temp, &size, stdin);
    do
    {
        if (temp == NULL)
            rc = IO_ERR;

        if (size > max_size)
            rc = 3;

    } while (rc);

    strcpy(field, temp);
    return rc;
}

int input_enum(int *option)
{
    char buf = 0;
    do
    {
        printf("\nEnter book type: ");
        buf = getchar();
    } while (!isdigit(buf) || buf > '2');

    return buf - '0';
}

int input_book(Book *book)
{
    int rc = input_book_common(book);
    if (!rc)
        rc = input_book_data(book);
    return rc;
}

int input_book_common(Book *book)
{
    // input author surname
    int rc = validate_input(book->authorSurname, "Enter author surname: ", MAX_SURNAME_LEN);
    // input book title
    if (!rc)
        rc = validate_input(book->bookTitle, "Enter book title: ", MAX_TITLE_LEN);
    // input publisher
    if (!rc)
        rc = validate_input(book->publisher, "Enter publisher: ", MAX_PUBLISHER_LEN);
    return rc;
}

int input_book_type(Book *book)
{
    char buf = 0;
    do
    {
        printf("\nEnter book type: ");
        buf = getchar();
    } while (!isdigit(buf) || buf > '2');

    return buf - '0';
}

int input_book_data(Book *book)
{
    EBookType type = 0;
    int rc = input_book_type(book);
    switch (book->type)
    {
    case TECHINCAL:
        input_technical_book(book);
        break;
    case FICTION:
        input_fiction_book(book);
        break;
    case CHILDREN:
        input_children_book(book);
        break;
    }
    return rc;
}

int input_technical_book(Book *book)
{
    return SUCCESS;
}

int input_fiction_book(Book *book)
{
    return SUCCESS;
}

int input_children_book(Book *book)
{
    return SUCCESS;
}

void print_book(Book *book)
{
    print_book_common(book);
    switch (book->type)
    {
    case TECHINCAL:
        print_technical_book(&book->data.technical);
        break;
    case FICTION:
        print_fiction_book(&book->data.fiction);
        break;
    case CHILDREN:
        print_children_book(&book->data.children);
        break;
    }
}

void print_book_common(Book *book)
{
    printf("\nAuthor: %s\nTitle: %s\n%s Pages: %zu\n", book->authorSurname, book->bookTitle, book->publisher,
           book->pageCount);
}

void print_technical_book(TechnicalBook *book)
{
    printf("\nIndustry: %s\nDomestic: %s\nPublish year: %zu\n", book->industry, book->domestic ? "Yes" : "No",
           book->publishYear);
}

void print_fiction_book(FictionBook *book)
{
    char *book_type = NULL;
    switch (book->type)
    {
    case NOVEL:
        book_type = "Novel";
        break;
    case PLAY:
        book_type = "Play";
        break;
    case POETRY:
        book_type = "Poetry";
        break;
    }
    printf("\nBook type: %s\n", book_type);
}

void print_children_book(ChildrenBook *book)
{
    char *book_type = NULL;
    switch (book->type)
    {
    case FAIRY_TALE:
        book_type = "Fairy tale";
        break;
    case CHILD_POETRY:
        book_type = "Children poetry";
        break;
    }
    printf("\nBook type: %s\n", book_type);
}
