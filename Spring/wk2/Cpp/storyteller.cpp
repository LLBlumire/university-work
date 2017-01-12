#include <iostream>
#include <string>
#include "food_and_drink.h"

using namespace std;

int main() {
    // Get the characters name
    cout << "What is the characters name?" << endl;
    string name;
    cin >> name;

    // Find out if they are eating or drinking
    cout << "Are they \"Eating\" or \"Drinking\"?" << endl;
    string eatingOrDrinking;
    cin >> eatingOrDrinking;
    bool isEating = (eatingOrDrinking == "Eating" || eatingOrDrinking == "eating");

    // Find out how much they consumed
    cout << "How much did they ";
    if (isEating) {
        cout << "eat?";
    } else {
        cout << "drink?";
    }
    cout << endl;
    int itemCount;
    cin >> itemCount;

    // Generate what they consumed
    string substance;
    if (isEating) {
        substance = GetRandomFoodItem();
    } else {
        substance = GetRandomDrinkItem();
    }

    // Output to user
    cout << name;
    if (isEating) {
        cout << " eats ";
    } else {
        cout << " drinks ";
    }
    cout << itemCount << " " << substance << endl;
}
