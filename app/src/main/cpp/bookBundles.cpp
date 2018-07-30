//
// Created by john on 7/29/18.
// Problem from HackerRank
//

#include "bookBundles.h"
#include "util.h"

using namespace std;

int bookBundles_driver() {
    const int bundleCount = 7;
    int bundleSize[] = {44, 47, 66, 32, 22, 13, 68};
    int bundleCost[] = {11, 12, 26, 14, 6,  3,  22};
    int budget = 100;

    int num = numberOfBooks(budget, bundleSize, bundleCost, bundleCount);
    COUT(to_string(num).data());

    return 0;
}

int numberOfBooks(int budget, int *bundleSize, int *bundleCost, int bundleCount) {
    // Define bestAttainableValue as the most number of books per bundle cost such that cost <= budget
    double value, bestAttainableValue;
    int indexBestAttainableValue, bundle_Cost;

    bestAttainableValue = 0;
    indexBestAttainableValue = -1;

    string budgetPrint = "Remaining Budget = $" + to_string(budget);
    COUT(budgetPrint.data());

    for (int i = 0; i < bundleCount; i++) {
        if (bundleCost[i] <= budget) {
            value = bundleSize[i] / (double) bundleCost[i];

            if (value > bestAttainableValue) {
                bestAttainableValue = value;
                indexBestAttainableValue = i;
            }
            COUT(to_string(value).data())
        }
    }

    if (indexBestAttainableValue > -1) {
        bundle_Cost = bundleCost[indexBestAttainableValue];

        return budget / bundle_Cost * bundleSize[indexBestAttainableValue] +
               numberOfBooks(budget - (budget / bundle_Cost) * bundle_Cost, bundleSize,
                             bundleCost, bundleCount);
    }
    else
        return 0;
}

