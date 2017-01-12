#ifndef FOOD_AND_DRINK_H
#define FOOD_AND_DRINK_H
// C++ (and C for that matter) are pretty dumb, and will try to compile header files in every source file it's #included in
// We fix this by use of an "include guard": the first time we include this file, the macro FOOD_AND_DRINK_H is not defined, so we define it and carry on with compiling
// The next time we include the file, FOOD_AND_DRINK_H has been defined, so we skip to the #endif at the bottom of the file
// By convention, the defined name is the same as the filename, in CAPITALS, and with an underscore instead of a "." for the file extension (or any spaces in the filename)
// Also by convention, the include guard should be the first thing in the file, even before comments (this is because compilers know to look for include guards at the top of the file!)

// We need the string header
#include <string>

// Function prototype for GetRandomFoodItem
// We're declaring a function that returns a string (in the std namespace), that takes no arguments.
// By convention, if this file is food_and_drink.h, we'd expect the function definition to be in food_and_drink.cpp
std::string GetRandomFoodItem();

// Function prototype for GetRandomDrinkItem
// Again, we're declaring a function that returns a string (still in the standard namespace), that also accepts no arguments.
std::string GetRandomDrinkItem();

// End of the include guard
#endif