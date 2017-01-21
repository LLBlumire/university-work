/* main.cpp
 * Tests a system designed to model stacks of books
 *
 * @author Lucille Blumire <lucy@llblumire.co.uk>
 * @version 1.0 2017-01-21
 */
#include <iostream>
#include <string>

#include "book.h"
#include "bookpile.h"

using namespace std;

int main() {
    // 1. Creating a BookPile should produce no output
    cout << "Test Case 1: Creating a BookPile" << endl;
    BookPile p1;

    cout << endl << endl;

    // 2. A new BookPile should not have any items in it
    // 3. Listing the contents of BookPile with no items should produce a blank listing
    cout << "Test Case 2/3: Bookpile Is Empty" << endl;
    p1.ListAllBooks();

    cout << endl << endl;

    // 4. Adding a book should result in the book's title being shown when ListAllBooks is called
    cout << "Test Case 4: Adding a Book" << endl;
    Book b1;
    b1.title = "Things to Make and Do in the Fourth Dimension";
    b1.author = "Matt Parker";
    p1.AddBook(b1);
    p1.ListAllBooks();

    cout << endl << endl;

    // 5. Adding more Books should not affect those already on the BookPile
    cout << "Test Case 5: Adding Additional Bookss" << endl;
    Book b2;
    b2.title = "The Language Construction Kitt";
    b2.author = "Rosenfelder";
    p1.AddBook(b2);
    p1.ListAllBooks();

    cout << endl << endl;

    // 6. Removing a Book should result in that item not being shown when ListAllBooks is called
    cout << "Test Case 6: Removing a Book" << endl;
    p1.RemoveBook();
    p1.ListAllBooks();

    cout << endl << endl;

    // 7. Creating a second BookPile should not affect the first
    cout << "Test Case 7: Creating a Second BookPile" << endl;
    BookPile p2;
    cout << "First Pile Content:" << endl;
    p1.ListAllBooks();
    cout << "Second Pile Content:" << endl;
    p2.ListAllBooks();

    cout << endl << endl;

    // 8. GetNextBook should return a copy of the Book object at the top of the pile
    cout << "Test Case 8: Getting the Next Book" << endl;
    Book nextBook1 = p1.GetNextBook();
    PrintBookLn(nextBook1);

    cout << endl << endl;

    // 9. Listing the contents of a BookPile should not affect the contents of a BookPile
    cout << "Test Case 9: Listing Pile Without Affecting Contents" << endl;
    cout << "First Listing:" << endl;
    p1.ListAllBooks();
    cout << "Second Listing:" << endl;
    p1.ListAllBooks();

    cout << endl << endl;

    // 10. GetNextBook should not affect the contents of the BookPile;
    cout << "Test Case 10: GetNextBook Without Affecting BookPile" << endl;
    cout << "Initial Listing:" << endl;
    p1.ListAllBooks();
    cout << "GetNextBook:" << endl;
    Book nextBook2 = p1.GetNextBook();
    PrintBookLn(nextBook2);
    cout << "Final Listing:" << endl;
    p1.ListAllBooks();

    cout << endl << endl;

    // Aditional Cases found in testing:

    // 11. Removing a Book from an empty BookPile shouldn't cause a crash;
    cout << "Test Case 11: Removing From Empty List" << endl;
    cout << "Listing:" << endl;
    p2.ListAllBooks();
    cout << "Removing:" << endl;
    p2.RemoveBook();
    cout << "Listing:" << endl;
    p2.ListAllBooks();

    cout << endl << endl;

    // 12. Calling GetNextBook on an empty BookPile shouldn't cause a crash;
    cout << "Test Case 12: GetNextBook on Empty Pile" << endl;
    Book nextBook3 = p2.GetNextBook();
    PrintBookLn(nextBook3);

    return 0;
}
