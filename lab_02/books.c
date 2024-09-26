#include "books.h"
#include "tui.h"

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

size_t import_entry_from_file(FILE *file, Book *book)
{
    if (fread(book, sizeof(Book), 1, file))
        return READ_ERROR;

    return SUCCESS;
}

size_t export_entry_to_file(FILE *file, Book *book)
{
    if (fwrite(book, sizeof(Book), 1, file))
        return WRITE_ERROR;

    return SUCCESS;
}
