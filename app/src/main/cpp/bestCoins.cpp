//
// Created by john on 7/3/18.
//

#include <iostream>
#include "util.h"
#include "bestCoins.h"
#include <string>
#include <limits>

// This code is Based on an example from Starting Out With C++ 4th by Tony Gaddis (pg 1194)
using namespace std;

// Constants
const int MAX_COINS_CHANGE = 100;
const int MAX_COIN_VALUES = 6;
const int NO_SOLUTION = numeric_limits<int>::max();

// coinValues - global array of coin values to choose from
int coinValues[MAX_COIN_VALUES] = {100, 50, 25, 10, 5, 1};

// bestCoins - global array of best coins to make change with
int bestCoins[MAX_COINS_CHANGE];

// Global variables
int numBestCoins = NO_SOLUTION,     // Number of coins in bestCoins
        numSolutions = 0,           // Number of ways to make change
        numCoins;                   // Number of allowable coins

int main() {
    int coinsUsed[MAX_COINS_CHANGE],    // List of coins used
        numCoinsUsed = 0,               // The number of coins used
        amount;                         // The amount to make change for

    // Use for string building
    string valueString;

    /*
     * Set the inputs here
     */
    amount = 67;
    numCoins = 88;

    // Display the possible coin values.
    COUT("Here are the valid coin values, in cents: ");
    for (int i = 0; i < MAX_COIN_VALUES; ++i) {
        valueString += to_string(coinValues[i]) + ' ';
    }
    COUT(valueString.data());

    // Get the input from the user
    COUT("Enter the amount of cents (as an integer) to make change for: ");
    COUT(to_string(amount).data());
    COUT("What is the maximum number of coins to give as change? ");
    COUT(to_string(numCoins).data());

    // Call the recursive function
    makeChange(numCoins, amount, coinsUsed, numCoinsUsed);

    // Display the results
    valueString.clear();
    valueString += "Number of possible combinations: " + to_string(numSolutions);
    COUT(valueString.data());

    valueString.clear();
    valueString += "Best combination of coins: \n";

    if (numBestCoins == NO_SOLUTION) {
        valueString += "\nNo solution\n";
    } else {
        for (int i = 0; i < numBestCoins; i++) {
            valueString += to_string(bestCoins[i]) + ' ';
        }
    }
    COUT((valueString += "\n").data());
    return 0;
}

//**************************************************************************************************
// coinsLeft - The number of coins left to choose from.                                            *
// amount - The amount to make change for.                                                         *
// coinsUsed - An array that contains the coin values used so far.                                 *
// numCoinsUsed - The number of values in the coinsUsed array.                                     *
//                                                                                                 *
// This recursive function finds all the possible ways to make change for the value in amount.     *
// The best combination of coins is stored in the array bestCoins.                                 *
//**************************************************************************************************

void makeChange(int coinsLeft, int amount, int coinsUsed[], int numCoinsUsed) {
    int coinPos, // To calculate array position of the coin being used
        count;   // Loop counter

    if (coinsLeft == 0) // No more coins left
        return;

    else if (amount < 0) // Amount to make change is negative
        return;

    else if (amount == 0) { // Solution is found
        // Store as bestCoins if best
        if (numCoinsUsed < numBestCoins) {
            for (count = 0; count < numCoinsUsed; count++) {
                bestCoins[count] = coinsUsed[count];
            }
            numBestCoins = numCoinsUsed;
        }
        numSolutions++;
        return;
    }

    // Find the other combinations using the coin
    coinPos = numCoins - coinsLeft;

    // Bug fix on the original code in print
    if (coinPos == MAX_COIN_VALUES)
        return;

    coinsUsed[numCoinsUsed] = coinValues[coinPos];
    numCoinsUsed++;
    makeChange(coinsLeft, amount - coinValues[coinPos], coinsUsed, numCoinsUsed);

    // Find the other combinations not using the coin
    numCoinsUsed--;
    makeChange(coinsLeft - 1, amount, coinsUsed, numCoinsUsed);
}



