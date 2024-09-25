#pragma once

#include "defines.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    TECHNICAL,
    FICTION,
    CHILDREN
} EBookGenre;

typedef enum
{
    NOVEL,
    PLAY,
    POETRY,
    FAIRY_TALE,
    CHILD_POETRY
} EBookType;

typedef struct
{
    char industry[MAX_INDUSTRY_LEN];
    bool domestic;
    size_t publishYear;
} TechnicalBook;

typedef struct
{
    EBookType type;
} FictionBook;

typedef struct
{
    EBookType type;
    size_t minimalAge;
} ChildrenBook;

typedef union
{
    TechnicalBook technical;
    FictionBook fiction;
    ChildrenBook children;
} UBookData;

typedef struct
{
    char authorSurname[MAX_SURNAME_LEN + 1];
    char bookTitle[MAX_TITLE_LEN + 1];
    char publisher[MAX_PUBLISHER_LEN + 1];
    size_t pageCount;
    EBookGenre genre;
    UBookData data;
} Book;

int validate_input(char *field, char *title, size_t max_size);

int input_enum(size_t *option, size_t max_options, char **options);

int input_value(size_t *value, char *title, bool has_range, size_t max_value);

int input_book(Book *book);

int input_book_common(Book *book);

int input_book_type(Book *book);

int input_book_data(Book *book);

int input_technical_book(TechnicalBook *book);

int input_fiction_book(FictionBook *book);

int input_children_book(ChildrenBook *book);

char *get_book_genre(Book *book);

char *get_fiction_book_type(FictionBook *book);
