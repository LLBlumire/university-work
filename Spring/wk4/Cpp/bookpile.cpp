/* bookpile.cpp
 * See bookpile.hpp for documentation.
 */
#include "book.hpp"
#include "bookpile.hpp"
#include "catch.hpp"
#include "category.hpp"
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

BookPile::BookPile() {
    this->books = std::vector<Book>();
}

void BookPile::AddBook(Book book) {
    this->books.push_back(book);
}

bool BookPile::RemoveBook() {
    if (this->GetNumBooks() > 0) {
        this->books.pop_back();
        return false;
    } else {
        return true;
    }
}

std::pair<bool, Book> BookPile::GetNextBook() {
    if (this->GetNumBooks() > 0) {
        return std::pair<bool, Book>(true, this->books.back());
    } else {
        return std::pair<bool, Book>(false, Book("", "", (Category)-1));
    }
}

void BookPile::ListAllBooks(std::ostream& os) {
    os << "Book Stack" << std::endl;
    for (std::vector<Book>::reverse_iterator it = this->books.rbegin(); it != this->books.rend(); ++it) {
        (*it).PrintBookLn(os);
    }
    os << "End Book Stack" << std::endl;
}

std::vector<Book>::size_type BookPile::GetNumBooks() {
    return this->books.size();
}

TEST_CASE( "Bookpile Initialization", "[bookpile]" ) {
    BookPile p;
    REQUIRE( p.GetNumBooks() == 0 );
}

TEST_CASE( "Empty Bookpile List", "[bookpile]" ) {
    BookPile p;
    std::string expected =
        "Book Stack\n"
        "End Book Stack\n";
    std::stringstream actual;
    p.ListAllBooks(actual);
    REQUIRE( actual.str() == expected );
}

TEST_CASE( "List Bookpile Shows Contents", "[bookpile]" ) {
    BookPile p;
    Book b ("Foo", "Bar", Reference);
    p.AddBook(b);
    std::stringstream bookList;
    p.ListAllBooks(bookList);
    REQUIRE( bookList.str().find("Foo") != std::string::npos );
}

TEST_CASE( "Multiple Add", "[bookpile]" ) {
    BookPile p;
    Book b ("Foo", "Bar", Reference);
    p.AddBook(b);
    Book c ("Baz", "Bar", Reference);
    p.AddBook(c);
    std::stringstream bookList;
    p.ListAllBooks(bookList);
    REQUIRE( bookList.str().find("Foo") != std::string::npos );
    REQUIRE( bookList.str().find("Baz") != std::string::npos );
}

TEST_CASE( "Removing Delists", "[bookpile]" ) {
    BookPile p;
    Book b ("Foo", "Bar", Reference);
    p.AddBook(b);
    Book c ("Baz", "Bar", Reference);
    p.AddBook(c);
    p.RemoveBook();
    std::stringstream bookList;
    p.ListAllBooks(bookList);
    REQUIRE( bookList.str().find("Foo") != std::string::npos );
    REQUIRE( bookList.str().find("Baz") == std::string::npos );
}

TEST_CASE( "Multiple Piles", "[bookpile]" ) {
    BookPile p;
    Book b ("Foo", "Bar", Reference);
    p.AddBook(b);
    Book c ("Baz", "Bar", Reference);
    p.AddBook(c);
    BookPile test;
    std::stringstream bookList;
    p.ListAllBooks(bookList);
    REQUIRE( bookList.str().find("Foo") != std::string::npos );
    REQUIRE( bookList.str().find("Baz") != std::string::npos );
    REQUIRE( test.GetNumBooks() == 0 );
}

TEST_CASE( "Getting the Top Book", "[bookpile]" ) {
    BookPile p;
    Book b ("Foo", "Bar", Reference);
    p.AddBook(b);
    Book c ("Baz", "Bar", Reference);
    p.AddBook(c);

    std::pair<bool, Book> expected (true, Book("Baz", "Bar", Reference));
    REQUIRE( p.GetNextBook() == expected );
}

TEST_CASE( "Listing does not mutate", "[bookpile]" ) {
    BookPile p;
    Book b ("Foo", "Bar", Reference);
    p.AddBook(b);
    Book c ("Baz", "Bar", Reference);
    p.AddBook(c);

    std::stringstream one;
    std::stringstream two;

    p.ListAllBooks(one);
    p.ListAllBooks(two);
    REQUIRE( one.str() == two.str() );
}

TEST_CASE( "Get Next Book does not mutate", "[bookpile]" ) {
    BookPile p;
    Book b ("Foo", "Bar", Reference);
    p.AddBook(b);
    Book c ("Baz", "Bar", Reference);
    p.AddBook(c);

    std::stringstream one;
    std::stringstream two;

    p.ListAllBooks(one);
    std::pair<bool, Book> nextBook = p.GetNextBook();
    p.ListAllBooks(two);
    REQUIRE( one.str() == two.str() );
}
