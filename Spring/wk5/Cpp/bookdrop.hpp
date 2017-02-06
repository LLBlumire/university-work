/* bookdrop.hpp
 * Describes the BookDrop class, which provides a specialized bookpile for the checking in and out
 * of books.
 */
#ifndef BOOK_DROP_H_INCL
#define BOOK_DROP_H_INCL

#include "bookpile.hpp"
#include <iostream>

/* BookDrop
 * Specialized BookPile for checking in and out books.
 */
class BookDrop : public BookPile {
    public:
        /* CheckIn(istream = cin)
         * Gets a new book from Cin. Asking for input on cout.
         */
        void CheckIn(std::istream& is = std::cin, std::ostream& os = std::cout);

        /* CheckOut()
         * Empties the bookpile of all books
         */
        void CheckOut(void);
};

#endif
