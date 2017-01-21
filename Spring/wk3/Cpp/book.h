//Include Guard
#ifndef __BOOK_H_INCLUDED__
#define __BOOK_H_INCLUDED__

#include <string>

struct Book {
    std::string title;
    std::string author;
};

void PrintBook(Book b);
void PrintBookLn(Book b);

#endif

