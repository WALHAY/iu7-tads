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

void input_book(Book *book);

void input_book_common(Book *book);

void input_book_type(Book *book);

void input_book_data(Book *book);

void input_technical_book(TechnicalBook *book);

void input_fiction_book(FictionBook *book);

void input_children_book(ChildrenBook *book);

char *get_book_genre(Book *book);

char *get_fiction_book_type(FictionBook *book);

void print_book(Book *book);
