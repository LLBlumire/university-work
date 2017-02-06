/* book.cpp
 * See book.hpp for documentation.
 */
#include "book.hpp"
#include "category.hpp"
#include "catch.hpp"
#include <string>
#include <ostream>

Book::Book(std::string title, std::string author, Category category) {
    this->title = title;
    this->author = author;
    this->category = category;
}

Book::Book() {
    this->title = "";
    this->author = "";
    this->category = (Category)-1;
}


std::string Book::Format(void) {
    return "\"" + this->title + "\" by " + this->author + " (" + displayCategory(this->category) + ")";
}
void Book::PrintBook(std::ostream& os) { 
    os << this->Format();
}
void Book::PrintBookLn(std::ostream& os) {
    os << this->Format() << std::endl;
}

bool Book::operator==(const Book& other) const {
    return this->title == other.title &&
        this->author == other.author &&
        this->category == other.category;
}

bool Book::operator!=(const Book& other) const {
    return !(*this == other);
}

TEST_CASE( "Book Initializatoin", "[book]" ) {
    Book b ("Foo", "Bar", Reference);
    REQUIRE( b.title == "Foo" );
    REQUIRE( b.author == "Bar" );
    REQUIRE( b.category == Reference);
}
TEST_CASE( "Book Equality", "[book]" ) {
    Book a ("Foo", "Bar", Reference);
    Book b ("Foo", "Bar", Reference);
    Book c ("Foo", "Baz", Reference);
    Book d ("Foobar", "Baz", History);

    REQUIRE( a == b );
    REQUIRE( a != c );
    REQUIRE( a != d );
}
TEST_CASE( "Book Format", "[book]" ) {
    Book b ("Foo", "Bar", Reference);
    REQUIRE( "\"Foo\" by Bar (Reference)" == b.Format() );
}
