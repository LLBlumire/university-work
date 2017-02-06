/* bookdrop.cpp
 * See bookdrop.hpp for documentation
 */

#include "book.hpp"
#include "bookdrop.hpp"
#include "bookpile.hpp"
#include "catch.hpp"
#include "category.hpp"
#include <iostream>
#include <sstream>
#include <utility>

void BookDrop::CheckIn(std::istream& is, std::ostream& os) {
    Book newBook;
    os << "Enter a book title: ";
    is >> newBook.title;
    os << "Enter a book author: ";
    is >> newBook.author;
    os << "Enter a new category (0=Biography, 1=History, 2=Reference, 3=Fiction): ";
    int category;
    is >> category;
    newBook.category = (Category)category;

    this->AddBook(newBook);
}

void BookDrop::CheckOut(void) {
    this->books.clear();
}

TEST_CASE( "Check In Book", "[bookdrop]" ) {
    BookDrop drop;
    std::istringstream iss ("Foo\nBar\n1");
    std::ostringstream oss;
    drop.CheckIn(iss, oss);
    std::pair<bool, Book> found = drop.GetNextBook();
    std::pair<bool, Book> expected (true, Book("Foo", "Bar", (Category)1));
    
    REQUIRE( found == expected );
}

TEST_CASE( "Check Out Book", "[bookdrop]" ) {
    BookDrop drop;
    Book a ("Foo", "Bar", Reference);
    Book b ("Baz", "Bar", History);
    drop.AddBook(a);
    drop.AddBook(b);
    REQUIRE( drop.GetNumBooks() == 2 );
    drop.CheckOut();
    REQUIRE( drop.GetNumBooks() == 0 );
}
