#ifndef __BOOK_PILE_H_INCLUDED__
#define __BOOK_PILE_H_INCLUDED__

#include <vector>
#include "book.h"

/* BookPile
 * Models a pile of books, that are stacked on top of each other such that only the topmost book can
 * be removed, but any book can have it's title and authorship seen.
 */
class BookPile {
    public:

        /* AddBook(b)
         * Adds a book to the top of the pile.
         */
        void AddBook(Book);

        /* RemoveBook()
         * Removes the book from the top of the pile.
         */
        void RemoveBook();

        /* GetNextBook()
         * Returns a copy of the top book on the pile.
         */
        Book GetNextBook();

        /* ListAllBooks()
         * Outputs all books in the order they appear to cout.
         */
        void ListAllBooks();

        /* GetNumBooks()
         * Returns the number of books in the pile as an integer.
         */
        int GetNumBooks();

    protected:

        /* books
         * Internal data model used to store the books that are in the pile.
         */
        std::vector<Book> books;
};

#endif
