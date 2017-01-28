/* category.h
 * Describes the Category enum, which is used to model differente categories of books.
 */
#ifndef CATEGORY_H_INCL
#define CATEGORY_H_INCL

#include <string>

enum Category {
    Biography,
    History,
    Reference,
    Fiction
};

std::string display(Category&);

#endif
