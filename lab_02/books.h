#pragma once

#include <cstdio>
#include <stdbool.h>
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
    char *authorSurname;
    char *bookTitle;
    char *publisher;
    size_t pageCount;
    EBookType type;
    UBookData data;
} Book;

char *validate_input(char *title);

int input_book_common();

int input_book_type();

int input_book_data();

int input_technical_book();

int input_fiction_book();

int input_children_book();
