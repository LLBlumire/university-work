#include "bookpile.h"
#include "book.h"
#include <vector>
#include <iostream>

using namespace std;

void BookPile::AddBook(Book b) {
    books.push_back(b);
}

void BookPile::RemoveBook() {
    if (GetNumBooks() > 0) {
        books.pop_back();
    } else {
        cout << "Cannot remove book, book pile empty" << endl;
    }
}

Book BookPile::GetNextBook() {
    if (GetNumBooks() > 0) {
        return books.back();
    } else {
        cout << "Book pile empty, getting empty book" << endl;
        Book e;
        e.title = "";
        e.author = "";
        return e;
    }
}

void BookPile::ListAllBooks() {
    cout << "[";
    for (vector<Book>::reverse_iterator it = books.rbegin(); it != books.rend(); ++it) {
        Book b = *it;
        PrintBook(b);
        if (GetNumBooks() > 1) {
            if (++it != books.rend())
                cout << endl;
            --it;
        }
    }
    cout << "]" << endl;
}

int BookPile::GetNumBooks() {
    return books.size();
}
