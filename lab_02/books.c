#include "books.h"
#include "tui.h"

void input_book(Book *book)
{
    input_book_common(book);
    input_book_data(book);
}

void input_book_common(Book *book)
{
    validate_input(book->authorSurname, "author surname", MAX_SURNAME_LEN);
    validate_input(book->bookTitle, "book title", MAX_TITLE_LEN);
    validate_input(book->publisher, "publisher", MAX_PUBLISHER_LEN);
    book->pageCount = input_value("page count", false, false, 0, 0);
}

void input_book_data(Book *book)
{
    char *options[] = {"Technical", "Fiction", "Children"};
    book->genre = input_enum(3, options);
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
}

void input_technical_book(TechnicalBook *book)
{
    validate_input(book->industry, "industry", MAX_INDUSTRY_LEN);
    char *options[] = {"Domestic", "Non domestic"};
    book->domestic = input_enum(2, options);
    book->publishYear = input_value("publish year", true, true, 0, 2024);
}

void input_fiction_book(FictionBook *book)
{
    char *options[] = {"Novel", "Play", "Poetry"};
    book->type = input_enum(3, options);
}

void input_children_book(ChildrenBook *book)
{
    book->minimalAge = input_value("minimal age", true, true, 0, 100);
    char *options[] = {"Fairy Tale", "Children Poetry"};
    book->type = input_enum(2, options) + POETRY + 1;
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
    return "Unknown";
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
    return "Unknown";
}
