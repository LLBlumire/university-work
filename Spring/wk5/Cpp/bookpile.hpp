/* bookpile.hpp
 * Describes the BookPile class, which is used to model stacks of books.
 */
#ifndef BOOK_PILE_H_INCL
#define BOOK_PILE_H_INCL

#include "book.hpp"
#include <utility>
#include <vector>
#include <ostream>

/* BookPile
 * Models a stack of books.
 */
class BookPile {
    public:
        /* BookPile()
         * Constructor
         */
        BookPile(void);

        /* AddBook(book)
         * Adds `book` to the stack of books
         */
        virtual bool AddBook(Book book);

        /* RemoveBook()
         * Removes the top book from the stack of books.
         *
         * Returns true if a book is removed,
         * Returns false if there are no books to remove.
         */
        bool RemoveBook(void);

        /* GetNextBook()
         * Get's the top book from the stack of books.
         *
         * Returns (true, book) if a book can be taken,
         * Returns (false, UNDEFINED) if a book cannot be taken.
         */
        std::pair<bool, Book> GetNextBook(void);

        /* ListAllBooks(ostream = cout)
         * Outputs all books on the stack to cout, with the top most (removable) book output first.
         */
        void ListAllBooks(std::ostream& os = std::cout);

        /* GetNumBooks()
         * Outputs the number of books on the stack
         */
        std::vector<Book>::size_type GetNumBooks();

    protected:

        /* books
         * Internal data structure used to represent the stack of books.
         */
        std::vector<Book> books;
};

#endif
