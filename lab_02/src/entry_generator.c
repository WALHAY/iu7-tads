#include "../inc/entry_generator.h"

#define arrlen(arr) sizeof(arr) / sizeof(*arr)

static char *authors[] = {"Glukhovskiy", "Asimov",   "King",    "Dostoevskiy", "Pushkin",
                          "Savelyev",    "Perelman", "Arbuzov", "Hamilton"};
static char *titles1[] = {"Cool", "Awesome", "Bad", "Wonderful", "Moderate"};
static char *titles2[] = {" Animals", " Nature",  " Friends", " Vibes", " Cars", " Automoblies",
                          " People",  " Student", " Apples",  " Cats",  " Dogs"};
static char *titles3[] = {" of Kamchatka", " in Nigeria", " in Africa",    " of USA",
                          " in USA",       " of China",   " in University"};
static char *industry[] = {"Physics", "Math", "Programming", "Law", "Chemical"};
static char *publisher[] = {"ACT", "Alpine", "Bombora", "Eksmo"};

static size_t generate_in_range(size_t min, size_t max)
{
    return min + (rand() % (max - min + 1));
}

void generate_entries(Table *table, size_t size)
{
    srand(time(NULL));
    Book book;
    for (size_t i = 0; i < size; ++i)
    {
        strcpy(book.authorSurname, authors[rand() % arrlen(authors)]);
        strcpy(book.bookTitle, titles1[rand() % arrlen(titles1)]);
        strcat(book.bookTitle, titles2[rand() % arrlen(titles2)]);
        strcat(book.bookTitle, titles3[rand() % arrlen(titles3)]);
        strcpy(book.publisher, publisher[rand() % arrlen(publisher)]);
        book.pageCount = generate_in_range(100, 500);
        book.genre = generate_in_range(0, 2);
        switch (book.genre)
        {
        case TECHNICAL:
            strcpy(book.data.technical.industry, industry[rand() % arrlen(industry)]);
            book.data.technical.domestic = generate_in_range(0, 1);
            book.data.technical.publishYear = generate_in_range(1950, 2017);
            break;
        case FICTION:
            book.data.fiction.type = generate_in_range(0, 2);
            break;
        case CHILDREN:
            book.data.children.minimalAge = generate_in_range(3, 17);
            book.data.children.type = generate_in_range(3, 4);
            break;
        }
        add_entry(table, &book);
    }
}
