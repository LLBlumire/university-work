/* bookbot.cpp
 * See bookbot.hpp for documentation.
 */
#include "book.hpp"
#include "bookbot.hpp"
#include "category.hpp"
#include "bookpile.hpp"
#include "storagepile.hpp"
#include "catch.hpp"
#include <ostream>
#include <sstream>
#include <utility>

BookBot::BookBot() {
    this->heldBook = EMPTY_BOOK_OPT; 
}

bool BookBot::PickUpBook(BookPile& pile) {
    if (this->heldBook.first) {
        return false;
    }
    this->heldBook = pile.GetNextBook();
    pile.RemoveBook(); // Error already handled by GetNextBook
    return this->heldBook.first;
}

bool BookBot::PlaceDownBook(BookPile& pile) {
    if (!this->heldBook.first) {
        return false;
    }
    if (pile.AddBook(this->heldBook.second)) {
        this->heldBook = EMPTY_BOOK_OPT;
        return true;
    } else {
        return false;
    }
}


void BookBot::ListContents(std::ostream& os) {
    if (this->heldBook.first) {
        this->heldBook.second.PrintBookLn(os);
    } else {
        os << "No Book Held" << std::endl;
    }
}

TEST_CASE( "New BookBot Empty", "[bookbot]" ) {
    BookBot bb;
    std::stringstream ss;
    bb.ListContents(ss);
    REQUIRE( ss.str() == "No Book Held\n" );
}

TEST_CASE( "BookBot pickup and show", "[bookbot]" ) {
    BookBot bb;
    BookPile p;
    Book b ("Foo", "Bar", Reference);
    p.AddBook(b);
    bb.PickUpBook(p);
    std::stringstream ss;
    bb.ListContents(ss);
    REQUIRE( ss.str() == "\"Foo\" by Bar (Reference)\n" );
}

TEST_CASE( "BookBot removes from pile", "[bookbot]" ) {
    BookBot bb;
    BookPile p;
    Book b ("Foo", "Bar", Reference);
    p.AddBook(b);
    bb.PickUpBook(p);
    REQUIRE( p.GetNumBooks() == 0 );
}

TEST_CASE( "BookBot place to pile", "[bookbot]" ) {
    BookBot bb;
    BookPile p;
    Book b ("Foo", "Bar", Reference);
    p.AddBook(b);
    bb.PickUpBook(p);
    bb.PlaceDownBook(p);
    std::stringstream ss1;
    bb.ListContents(ss1);
    REQUIRE( ss1.str() == "No Book Held\n" );
    std::stringstream ss2;
    p.ListAllBooks(ss2);
    REQUIRE( ss2.str().find("\"Foo\" by Bar (Reference)") != std::string::npos );
}


TEST_CASE( "BookBot cannot hold multiple books", "[bookbot]" ) {
    BookBot bb;
    BookPile p;
    Book b1 ("Foo", "Bar", Reference);
    Book b2 ("Baz", "Bar", Reference);
    p.AddBook(b1);
    p.AddBook(b2);
    bb.PickUpBook(p);
    REQUIRE( bb.PickUpBook(p) == false );
    std::stringstream ss1;
    bb.ListContents(ss1);
    REQUIRE( ss1.str() == "\"Baz\" by Bar (Reference)\n" );
    std::stringstream ss2;
    p.ListAllBooks(ss2);
    REQUIRE( ss2.str().find("\"Foo\" by Bar (Reference)\n") != std::string::npos );
}

TEST_CASE( "BookBot cannot pickup from empty pile", "[bookbot]" ) {
    BookBot bb;
    BookPile p;
    REQUIRE( bb.PickUpBook(p) == false );
}

TEST_CASE( "Cannot add book of wrong category to storagepile", "[bookbot]" ) {
    BookBot bb;
    StoragePile sp ( History );
    BookPile bp;
    Book b ("Foo", "Bar", Reference);
    bp.AddBook(b);
    REQUIRE( bb.PickUpBook(bp) == true );
    REQUIRE( bb.PlaceDownBook(sp) == false );

}
