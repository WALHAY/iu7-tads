#include "../inc/entry_generator.h"

char *authors[] = {"Glukhovkiy", "Asimov", "King", "Dostoevskiy", "Pushkin", "Savelyev", "Perelman", "Arbuzov"};
char *titles1[] = {"Cool", "Awesome", "Bad", "Dummy", "Moderate"};
char *titles2[] = {"Animals", " Nature",  " Friends", " Vibes", " Cars", " Automoblies",
                   " People", " Student", " Apples",  " Cats",  " Dogs"};
char *titles3[] = {" of Kamchatka", " in Nigeria", " in Africa", " of USA", " in USA", " of China", " in University"};
char *industry[] = {"Physics", "Math", "Programming", "Law", "Chemical"};
char *publisher[] = {"ACT", "Alpine", "Bombora", "Eksmo"};

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
        strcpy(book.authorSurname, authors[rand() % 8]);
        strcpy(book.bookTitle, titles1[rand() % 5]);
        strcat(book.bookTitle, titles2[rand() % 11]);
        strcat(book.bookTitle, titles3[rand() % 7]);
        strcpy(book.publisher, publisher[rand() % 4]);
        book.pageCount = generate_in_range(100, 500);
        book.genre = generate_in_range(0, 2);
        switch (book.genre)
        {
        case TECHNICAL:
            strcpy(book.data.technical.industry, industry[rand() % 5]);
            book.data.technical.domestic = generate_in_range(0, 1);
            book.data.technical.publishYear = generate_in_range(1950, 2017);
            break;
        case FICTION:
            book.data.fiction.type = generate_in_range(0, 3);
            break;
        case CHILDREN:
            book.data.children.minimalAge = generate_in_range(3, 16);
            book.data.children.type = generate_in_range(3, 4);
            break;
        }
        add_entry(table, &book);
    }
}
