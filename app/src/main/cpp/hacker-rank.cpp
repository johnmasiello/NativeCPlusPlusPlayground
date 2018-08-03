//
// Created by john on 8/1/18.
//
#include "hacker-rank.h"
#include "util.h"
#include <string>
#include <vector>

using namespace std;

namespace sample_hacker_one {
    // Complete the findNumber function below.
    string findNumber(vector<int> arr, int k) {

        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == k)
                return "YES";
        }
        return "NO";
    }
}

namespace sample_hacker_two {
    // Complete the oddNumbers function below.
    vector<int> oddNumbers(int l, int r) {
        vector<int> odds(0);

        for (int i = l; i <= r; i++) {
            if (i % 2 == 1)
                odds.push_back(i);
        }
        return odds;
    }
}

namespace hacker_one {
// Complete the getUmbrellas function below.
    int getUmbrellas(int n, vector<int> p) {


    }
}

namespace hacker_two {

    struct myInt {
        int val;
        int count;
    };

// Complete the maxPoints function below.
    long maxPoints(vector<int> elements) {
        vector<myInt> uniqueElements(0);
        vector<myInt>::iterator it, itSmart, itRemoveStart;

        long countChosenElements = 0;
        long smartPoints, points;

        int element, count;
        myInt *dummy;

        for (int i = 0; i < elements.size(); i++) {
            if (elements[i] == -1)
                continue;

            element = elements[i];
            count = 1;

            for (int j = i + 1; j < elements.size(); j++) {
                if (elements[j] == element) {
                    count++;
                    elements[j] = -1; // Mark the element as consumed
                }
            }

            dummy = new myInt {element, count};

            for (it = uniqueElements.begin(); it < uniqueElements.end(); it++) {
                if (element < it->val) {
                    uniqueElements.insert(it, *dummy);
                    dummy = NULL;
                    break;
                }
            }
            if (dummy != NULL)
                uniqueElements.push_back(*dummy);
        }

        // Accumulate all elements that are distanced far enough from their neighbors to cause no loss of potential points
        it = uniqueElements.begin();
        while (it < uniqueElements.end()) {
            if ((prev(it) == uniqueElements.begin() || prev(it)->val + 1 < it->val) &&
                    (next(it) == uniqueElements.end() || next(it)->val > it->val + 1)) {

                countChosenElements += it->count * it->val;
                uniqueElements.erase(it);
            } else
                it++;
        }

        // Accumulate the rest of the points that are not as obvious
        while (!uniqueElements.empty()) {
            it = uniqueElements.begin();

            // Initialize smart points
            points = it->count * it->val;
            points -= (next(it) == uniqueElements.end() || next(it)->val > it->val + 1) ? 0 : next(it)->count * next(it)->val;
            smartPoints = points;
            itSmart = it;
            it++;

            while (it < uniqueElements.end()) {
                points = it->count * it->val;
                points -= (prev(it)->val + 1 < it->val) ? 0 : prev(it)->count * prev(it)->val;
                points -= (next(it) == uniqueElements.end() || next(it)->val > it->val + 1) ? 0 : next(it)->count * next(it)->val;

                if (points > smartPoints) {
                    smartPoints = points;
                    itSmart = it;
                }
                it++;
            }

            // Accumulate the smart choice, for most points according to the rules
            // COUT(to_string(itSmart->val).data()); // Debug
            countChosenElements += itSmart->count * itSmart->val;

            // Remove the chosen element and the adjacent elements, if any
            itRemoveStart = itSmart;

            if (prev(itSmart) != uniqueElements.begin() && prev(itSmart)->val + 1 == itSmart->val)
                itRemoveStart = prev(itSmart);
            if (next(itSmart) != uniqueElements.end() && next(itSmart)->val == itSmart->val + 1)
                itSmart = next(itSmart);

            uniqueElements.erase(itRemoveStart, itSmart + 1);
        }
        return countChosenElements;
    }

    void test() {
        const int NUMBER_OF_POINTS = 12;
        vector<int> numbers(NUMBER_OF_POINTS);
        int arrPoints[] = {
//                4, 4, 3,
//                3, 3, 1,
//                2, 2, 5,
//                6, 7, 5

            2, 2, 2,
            4, 6, 8,
            4, 8, 12,
            22, 18, 16
        };

        for (int i = 0; i < NUMBER_OF_POINTS; i++) {
            numbers[i] = arrPoints[i];
        }

        COUT(("Number of points scored = " + to_string(maxPoints(numbers))).data())

        /**
         * Number of points scored = 27
         */

        /**
         * Number of points scored = 104
         */
    }
}

namespace hacker_three {
// Complete the numberOfPairs function below.
    int numberOfPairs(vector<int> a, long k) {

    }


















}

namespace hacker_four {
// Complete the braces function below.
    vector<string> braces(vector<string> values) {


    }
















}

/* The main driver
 *
 *
 *
 *
 *
 *
 *
 *
 */

int main() {
//    COUT(to_string(sample_hacker_one::main()).data());
//    COUT(to_string(sample_hacker_two::main()).data());
    hacker_two::test();

    return 0;
}