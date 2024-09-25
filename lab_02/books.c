#include "books.h"

int validate_input(char *field, char *title, size_t max_size)
{
    char temp[max_size + 1];
    do
    {
        printf("Enter %s: ", title);
        fgets(temp, max_size, stdin);
    } while (strlen(temp) >= max_size);
    char *newline = strchr(temp, '\n');
    if (newline)
        *newline = '\0';
    strcpy(field, temp);
    return SUCCESS;
}

int input_enum(size_t *option, size_t max_options, char **options)
{
    printf("\nPossible variants:\n");
    for (size_t i = 0; i < max_options; ++i)
        printf("\t%zu. %s\n", i, options[i]);

    printf("Option: ");
    while (!scanf("%zu", option) || *option >= max_options)
        printf("\nWrong option! Enter option again: ");
    return SUCCESS;
}

int input_value(size_t *value, char *title, bool has_range, size_t max_value)
{
    printf("Enter %s: ", title);
    while (!scanf("%zu", value) || (has_range && *value > max_value))
        printf("Enter %s again: ", title);
    return SUCCESS;
}

int input_book(Book *book)
{
    input_book_common(book);
    input_book_data(book);
    return SUCCESS;
}

int input_book_common(Book *book)
{
    validate_input(book->authorSurname, "author surname", MAX_SURNAME_LEN);
    validate_input(book->bookTitle, "book title", MAX_TITLE_LEN);
    validate_input(book->publisher, "publisher", MAX_PUBLISHER_LEN);
    input_value(&book->pageCount, "page count", false, 0);
    return SUCCESS;
}

int input_book_data(Book *book)
{
    char *options[] = {"Technical", "Fiction", "Children"};
    int rc = input_enum((size_t *)&book->genre, 3, options);
    switch (book->genre)
    {
    case TECHNICAL:
        input_technical_book(&book->data.technical);
        break;
    case FICTION:
        input_fiction_book(&book->data.fiction);
        break;
    case CHILDREN:
        input_children_book(&book->data.children);
        break;
    }
    return rc;
}

int input_technical_book(TechnicalBook *book)
{
    validate_input(book->industry, "industry", MAX_INDUSTRY_LEN);
    char *options[] = {"Domestic", "Non domestic"};
    input_enum((size_t *)&book->domestic, 2, options);
    input_value(&book->publishYear, "publish year", true, 2024);
    return SUCCESS;
}

int input_fiction_book(FictionBook *book)
{
    char *options[] = {"Novel", "Play", "Poetry"};
    input_enum((size_t *)&book->type, 3, options);
    return SUCCESS;
}

int input_children_book(ChildrenBook *book)
{
    input_value((size_t *)&book->minimalAge, "minimal age", true, 100);
    char *options[] = {"Fairy Tale", "Children Poetry"};
    input_enum((size_t *)&book->type, 2, options);
    book->type += POETRY + 1;
    return SUCCESS;
}

char *get_book_genre(Book *book)
{
    switch (book->genre)
    {
    case TECHNICAL:
        return "Technical";
    case FICTION:
        return "Fiction";
    case CHILDREN:
        return "Children";
    }
}

char *get_fiction_book_type(FictionBook *book)
{
    switch (book->type)
    {
    case NOVEL:
        return "Novel";
    case PLAY:
        return "Play";
    case POETRY:
        return "Poetry";
    case FAIRY_TALE:
        return "Fairy tale";
    case CHILD_POETRY:
        return "Child poetry";
    }
}
