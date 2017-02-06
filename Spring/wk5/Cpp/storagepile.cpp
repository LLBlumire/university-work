/* storagepile.cpp
 * See storagepile.hpp for documentation
 */

#include "storagepile.hpp"
#include "bookpile.hpp"
#include "book.hpp"
#include "catch.hpp"
#include <utility>

StoragePile::StoragePile(Category category) {
    this->category = category;
}

bool StoragePile::AddBook(Book b) {
    if (b.category == this->category) {
        return BookPile::AddBook(b);
    } else {
        return false;
    }
}

TEST_CASE ( "Add Book of same category", "[storagepile]" ) {
    StoragePile storagePile ( Reference );
    Book b ( "Foo", "Bar", Reference );
    REQUIRE( storagePile.AddBook(b) == true );
    std::pair<bool, Book> expected (true, b);
    REQUIRE( storagePile.GetNextBook() == expected );
}

TEST_CASE ( "Add Book of different category", "[storagepile]" ) {
    StoragePile storagePile ( History );
    Book b ( "Foo", "Bar", Reference );
    REQUIRE( storagePile.AddBook(b) == false );
    REQUIRE( storagePile.GetNextBook().first == false );
}
