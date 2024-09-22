#pragma once

#include "defines.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    TECHINCAL,
    FICTION,
    CHILDREN
} EBookType;

typedef enum
{
    FAIRY_TALE,
    CHILD_POETRY
} EChildrenBookType;

typedef enum
{
    NOVEL,
    PLAY,
    POETRY
} EFictionBookType;

typedef struct
{
    char *industry;
    bool domestic;
    size_t publishYear;
} TechnicalBook;

typedef struct
{
    EFictionBookType type;
} FictionBook;

typedef struct
{
    size_t minimalAge;
    EChildrenBookType type;
} ChildrenBook;

typedef union
{
    TechnicalBook technical;
    FictionBook fiction;
    ChildrenBook children;
} UBookData;

typedef struct
{
    char authorSurname[MAX_SURNAME_LEN];
    char bookTitle[MAX_TITLE_LEN];
    char publisher[MAX_PUBLISHER_LEN];
    size_t pageCount;
    EBookType type;
    UBookData data;
} Book;

int validate_input(char *field, char *title, size_t max_size);

int input_book(Book *book);

int input_book_common(Book *book);

int input_book_type(Book *book);

int input_book_data(Book *book);

int input_technical_book(TechnicalBook *book);

int input_fiction_book(FictionBook *book);

int input_children_book(ChildrenBook *book);

void print_book(Book *book);

void print_book_common(Book *book);

void print_technical_book(TechnicalBook *book);

void print_fiction_book(FictionBook *book);

void print_children_book(ChildrenBook *book);
