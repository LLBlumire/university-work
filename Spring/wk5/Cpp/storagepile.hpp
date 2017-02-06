/* storagepile.hpp
 * Describes the StoragePile class, which provides a specialized bookpile for storing books of a
 * specific category.
 */
#ifndef STORAGE_PILE_H_INCL
#define STORAGE_PILE_H_INCL

#include "book.hpp"
#include "category.hpp"
#include "bookpile.hpp"

/* StoragePile
 * Specizlied BookPile for storing books of a sepcific category.
 */
class StoragePile : public BookPile {
    public:
        /* StoragePile(category)
         * Constructor
         */
        StoragePile(Category category);

        /* AddBook(book)
         * Specialized method for adding books. Will return false and not add if the book is of an
         * incorrect category.
         */
        bool AddBook(Book b);

        /* category
         * The category this StoragePile should accept.
         */
        Category category;
};

#endif
