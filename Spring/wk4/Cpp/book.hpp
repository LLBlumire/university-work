/* book.hpp
 * Describes the Book class, which is used to model books.
 */
#ifndef BOOK_H_INCL
#define BOOK_H_INCL

#include "category.hpp"
#include <string>
#include <ostream>
#include <iostream>

/* Book
 * Models a book.
 */
class Book {
    public:
        /* Title
         * The title of the book.
         */
        std::string title;

        /* Author
         * The author of the book.
         */
        std::string author;

        /* Category
         * The category of the book.
         */
        Category category;

        /* Book()
         * Constructor
         */
        Book(std::string title, std::string author, Category category);

        /* Format()
         * Formats the book nicely for output.
         */
        std::string Format(void);

        /* PrintBook(ostream = cout)
         * Outputs the book formatted to cout.
         */
        void PrintBook(std::ostream& os = std::cout);

        /* PrintBookLn(ostream = cout)
         * Same as `PrintBook` buut with a trailing newline.
         */
        void PrintBookLn(std::ostream& os = std::cout);

        /* ==
         * Overload == for equality comparison.
         */
        bool operator==(const Book& other) const;

        /* !=
         * Overload != for equality comparison.
         */
        bool operator!=(const Book& other) const;
};

#endif
