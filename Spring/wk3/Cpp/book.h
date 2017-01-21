/* book.h
 * Describes the Book struct, which is used to model books.
 */
#ifndef __BOOK_H_INCLUDED__
#define __BOOK_H_INCLUDED__

#include <string>

/* Book
 * Models a Book.
 */
struct Book {
    /* The title of a book */
    std::string title;
    /* The author of a book */
    std::string author;
};

/* PrintBook(b)
 * Outputs the book `b` nicely formatted to cout.
 */
void PrintBook(Book b);

/* PrintBookLn(b)
 * The same as `PrintBook` but with a trailing newline.
 */
void PrintBookLn(Book b);

#endif

