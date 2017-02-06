/* bookbot.hpp
 * Describes the BookBot class, which is used to model a book carrying robot
 */
#ifndef BOOK_BOT_H_INCL
#define BOOK_BOT_H_INCL

#include "bookpile.hpp"
#include "book.hpp"
#include <ostream>
#include <utility>


/* BookBot
 * Models a book carrying robot.
 */
class BookBot {
    public:
        /* BookBot()
         * Constructor
         */
        BookBot();

        /* PickUpBook(bookPile)
         * Picks up and hold a book from a pile;
         * Returns true if a book is taken,
         * Returns false if there is no book to take or,
         * Returns false if a book is already held.
         */
        bool PickUpBook(BookPile& pile);

        /* PlaceDownBook(bookPile)
         * Places a held book onto a pile;
         * Returns true if a book is placed,
         * Returns false if there is no held book to place
         * Returns false if book cannot be placed,
         */
        bool PlaceDownBook(BookPile& pile);

        /* ListContents(ostream = cout)
         * Outputs the held book to cout.
         */
        void ListContents(std::ostream& os = std::cout);

    protected:
        /* heldBook
         * Internal data model representing an optionally held book where:
         * (true, book) = `book` is held
         * (false, _) = nothing is held
         */
        std::pair<bool, Book> heldBook;
};

#endif
