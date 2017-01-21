#ifndef __BOOK_PILE_H_INCLUDED__
#define __BOOK_PILE_H_INCLUDED__

#include <vector>
#include "book.h"

class BookPile {
    public:
        void AddBook(Book);
        void RemoveBook();
        Book GetNextBook();
        void ListAllBooks();
        int GetNumBooks();
    protected:
        std::vector<Book> books;
};

#endif
