/* book.cpp
 * See book.h for method documentation
 */
#include "book.h"
#include <iostream>

using namespace std;

void PrintBook(Book b) {
    cout << "\"" << b.title << "\" by " << b.author;
}
void PrintBookLn(Book b) {
    PrintBook(b);
    cout << endl;
}
