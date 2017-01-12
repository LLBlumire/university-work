// Let's include the C++ string header
#include <string>

// I can also include any of the C standard library files
// by dropping the ".h" off the end, and putting a "c" at the front.
// So, if I want stuff contained in <stdlib.h> and <time.h>...
#include <cstdlib>
#include <ctime>

// Finally, we'll include our header files
// Remember: standard header files use <>, ours use ""
#include "food_and_drink.h"

// We're using the standard namespace (containing string)
// Alternatively, we could have skipped this line, and instead written "std::string" everywhere we used "string" in the code (like we did in the header)
// Namespaces are useful when you've got code that comes from (or will be used in) a lot of different people's work
using namespace std;


// Selecting a random food item and a random drink item are both the same sort of thing,
// so I'd prefer to not have to write the same code twice.
// Because GetRandomItemFromList is NOT in the header file, only functions in this file can see it
// GetRandomItemFromList returns a string, and requires 2 arguments: an array of strings, and an integer to let us know how many strings we have
string GetRandomItemFromList(string list[], int num_items_in_list)
{
	// We want to pick an item from the list at random.
	
	// rand is a cheap function defined by the C standard library in stdlib
	// It's got some poor statistical characteristics, but our application is simple enough to not care
	
	// srand initialises the random number generator (without this, we get the same numbers every time)
	// We'll initialise it using the current time, as this is fairly difficult to predict.

	// Note: It is generally bad practice to call srand multiple times. This is because programs
	// execute very fast on a modern processor, and there is a good chance that the next call to time() will
	// be within the same second. srand will then return the same value, and when you call rand you'll
	// end up with the same value from the generator. 
	// Ordinarily, you would place this in the main function, call it once on program start and then never call it again.
	srand(time(NULL));
	
	// rand will pick a random number between 0 and INT_MAX. We'd like to pick a number between 0 and the end of our list
	// Our good friend modulus (%) helps us here
	// rand will pick some arbitrary big number, but since we only take the remainder, we know the end value will be in the range we want
	// (work it out with a pen and paper if you don't see how this works: divide a big number by the list count, and look at the remainder)
	int index = rand() % num_items_in_list;

	// Now we know which position in the array we want, we'll return it.
	return list[index];


}

string GetRandomFoodItem()
{
	// An array of foods.
	// Note that I only need a one-dimensional array,
	// and that I don't care how long a string is.
	// This is the magic that is the string class
	string foods[10] = 
	{
		"carrots",
		"apples",
		"oranges",
		"biscuits",
		"sweets",
		"sandwiches",
		"lemons", // do children eat lemons? Probably.
		"boiled eggs",
		"slices of cake",
		"bowls of ice-cream"
	};
	
	// Pick something from the list, and return it.
	return GetRandomItemFromList(foods, 10);
}

string GetRandomDrinkItem()
{
	// An array of drinks.
	// Again, the string class has made it a bit easier than in C
	string drinks[5] =
	{
		"cups of milk",
		"glasses of water",
		"mugs of hot chocolate",
		"cups of tea",
		"cans of fizzy pop"
	};

	// Pick something from the list, and return it.
	return GetRandomItemFromList(drinks, 5);
}


