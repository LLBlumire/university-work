/* category.cpp
 * See category.hpp for documentation
 */
#include "category.hpp"
#include "catch.hpp"
#include <string>

std::string displayCategory(Category category) { 
    switch (category) {
        case Biography:
            return "Biography";
        case History:
            return "History";
        case Reference:
            return "Reference";
        case Fiction:
            return "Fiction";
        default:
            return "Unknown Type";
    }
}

TEST_CASE( "Category Printing", "[category]" ) {
    REQUIRE( displayCategory(Biography) == "Biography" );
    REQUIRE( displayCategory(History) == "History" );
    REQUIRE( displayCategory(Reference) == "Reference" );
    REQUIRE( displayCategory(Fiction) == "Fiction" );
    REQUIRE( displayCategory((Category)4) == "Unknown Type" );
}
